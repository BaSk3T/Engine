#ifndef DEVICE_H
#define DEVICE_H

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "Interfaces\IDevice.h"
#include "../Types.h"

class Device : public IDevice
{
public:
	Device(HWND hwnd, UI32 width, UI32 height);
	~Device();

	ID3D11Device* GetDevice() { return m_Device; };

private:
	ID3D11Device* m_Device;
	IDXGISwapChain* m_Swapchain;
};

#endif // !DEVICE_H
