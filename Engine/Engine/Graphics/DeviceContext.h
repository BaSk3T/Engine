#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

struct ID3D11DeviceContext;

#include "Interfaces\IDeviceContext.h"

class DeviceContext : public IDeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	virtual void SetRenderTarget(IRenderTarget& renderTarget);
	virtual void SetViewPort(UI32 width, UI32 height, float minDepth, float maxDepth, UI32 x, UI32 y);
	virtual void SetInputLayout(IInputLayout& inputLayout);
	virtual void SetVertexBuffer(IBuffer& vertexBuffer, UI32 vertexSize);
	virtual void SetIndexBuffer(IBuffer& indexBuffer);

private:
	ID3D11DeviceContext* m_DeviceContext;
};

#endif // !DEVICECONTEXT_H
