#include "Device.h"

#include <Windows.h>

#include "DeviceContext.h"
#include "RenderTarget.h"
#include "../DebugHelper.h"

Device::Device(HWND hwnd, UI32 width, UI32 height)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	UINT numLevelsRequested = 1;
	D3D_FEATURE_LEVEL featureLevelsSupported;
	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1;

	ID3D11DeviceContext* deviceContext;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		&featureLevels,
		numLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&m_Swapchain,
		&m_Device,
		&featureLevelsSupported,
		&deviceContext);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to initialize device!\n");
	}

	m_ImmediateContext = new DeviceContext(deviceContext);

	ID3D11Texture2D* backBuffer;
	m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	m_MainRenderTarget = new RenderTarget(*this, backBuffer);
}

Device::~Device()
{
	delete m_MainRenderTarget;
	delete m_ImmediateContext;
	m_Swapchain->Release();
	m_Device->Release();
}
