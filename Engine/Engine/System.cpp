#include "System.h"

#include "DebugHelper.h"

#include "Graphics\Renderer.h"
#include "TaskScheduler\TaskScheduler.h"

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
}

UI32 System::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		for (auto renderer : m_Renderers)
		{
			renderer->RenderFrame();
		}
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