#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

class IRenderTarget;

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "Interfaces\IDeviceContext.h"
#include "../Types.h"

class DeviceContext : public IDeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	void SetRenderTarget(IRenderTarget& renderTarget);
	void SetViewPort(UI32 width, UI32 height, float minDepth, float maxDepth, UI32 x, UI32 y);

private:
	ID3D11DeviceContext* m_DeviceContext;
};

#endif // !DEVICECONTEXT_H
