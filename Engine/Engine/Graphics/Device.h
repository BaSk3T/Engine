#ifndef DEVICE_H
#define DEVICE_H

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "../Types.h"

class Device
{
public:
	Device(HWND hwnd, UI32 width, UI32 height);
	~Device();

private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	IDXGISwapChain* m_Swapchain;
};

#endif // !DEVICE_H
