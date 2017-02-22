#include "System.h"

#include <fstream>

#include "DebugHelper.h"

#include "Graphics\Device.h"
#include "Graphics\DeviceContext.h"
#include "Graphics\Renderers\CharacterRenderer.h"
#include "TaskScheduler\TaskScheduler.h"
#include "Input\WindowsGamepadHandler.h"
#include "Graphics\Camera.h"

#include "dirent.h"
#include "rapidxml.hpp"

System::System()
{
	TaskScheduler& ts = TaskScheduler::GetInstance();
	ts.AddThreads(8);
	ts.SetTasksPerThread(5);
}

System::~System()
{
	TaskScheduler& ts = TaskScheduler::GetInstance();
	ts.SyncWorkerThreads();

	delete m_Device;
	delete m_GamepadHandler;
	delete m_Camera;

	for (auto renderer : m_Renderers)
	{
		delete renderer;
	}
}

UI32 System::Run()
{
	MSG msg = { 0 };

	m_Device = new Device(m_hWnd, m_WindowWidth, m_WindowHeight);
	m_GamepadHandler = new WindowsGamepadHandler();
	m_Camera = new Camera(0, 0, 15.0f);
	LoadActors();

	IDeviceContext* devContext = m_Device->GetImmediateContext();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_GamepadHandler->HandleInput();
		Gamepad& gamepad = m_GamepadHandler->GetGamepad();

		m_Camera->HandleInput(gamepad.m_LeftStickMagnitudeX, gamepad.m_LeftStickMagnitudeY, gamepad.m_RightStickMagnitudeX, gamepad.m_RightStickMagnitudeY);
		m_Camera->CalculateViewMatrix();

		ColorRGBA clearColor = { 0.3f, 0, 1, 0 };
		IRenderTarget* renderTarget = m_Device->GetMainRenderTarget();

		devContext->SetRenderTarget(*renderTarget);
		devContext->ClearRenderTarget(*renderTarget, clearColor);
		devContext->ClearDepthStencilBuffer();

		for (auto renderer : m_Renderers)
		{
			renderer->RenderFrame();
		}

		m_Device->Present();
	}

	return msg.message;
}

void System::InitializeWindow(UI32 width, UI32 height, HINSTANCE hInstance, int nCmdShow)
{
	m_WindowWidth = width;
	m_WindowHeight = height;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	RegisterClassEx(&wc);

	m_hWnd = CreateWindowEx(NULL, wc.lpszClassName, "Engine", WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hInstance, NULL);

	if (!m_hWnd)
	{
		OUTPUT_DEBUG("Couldn't initialize window!/n");
	}

	ShowWindow(m_hWnd, nCmdShow);
}

void System::LoadActors()
{
	char* directory = "./Actors";
	std::vector<std::string> fileNames;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directory)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (32768 == ent->d_type)
			{
				fileNames.push_back(ent->d_name);
			}

		}
		closedir(dir);
	}
	else {
		OUTPUT_DEBUG("Failed to open directory Actors!\n");
		return;
	}

	for (auto fileName : fileNames)
	{
		rapidxml::xml_document<> doc;

		std::ifstream stream;
		stream.open("./Actors/" + fileName);

		std::string content((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));

		stream.close();

		doc.parse<0>(&content[0]);

		rapidxml::xml_node<>* actor = doc.first_node("Actor");
		rapidxml::xml_node<>* vertexShader = actor->first_node("VertexShader");
		rapidxml::xml_node<>* pixelShader = actor->first_node("PixelShader");
		rapidxml::xml_node<>* model = actor->first_node("Model");
		rapidxml::xml_node<>* texture = actor->first_node("Texture");
		rapidxml::xml_node<>* worldPosition = actor->first_node("WorldPosition");

		std::string actorName = actor->first_attribute("name")->value();
		std::string pixelShaderName = pixelShader->first_attribute("name")->value();
		std::string vertexShaderName = vertexShader->first_attribute("name")->value();
		std::string modelName = model->first_attribute("name")->value();
		std::string textureName = texture->first_attribute("name")->value();

		float x = std::stof(worldPosition->first_attribute("x")->value());
		float y = std::stof(worldPosition->first_attribute("y")->value());
		float z = std::stof(worldPosition->first_attribute("z")->value());

		CharacterRenderer* renderer = new CharacterRenderer(m_Device, m_Camera, m_WindowWidth, m_WindowHeight);
		renderer->SetName(actorName);
		renderer->SetVertexShader(vertexShaderName);
		renderer->SetPixelShader(pixelShaderName);
		renderer->SetModel(modelName);
		renderer->SetTexture(textureName);
		renderer->SetInputLayout();
		renderer->Translate(x, y, z, 1);

		m_Renderers.push_back(renderer);
	}
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}