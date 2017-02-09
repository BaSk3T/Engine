#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

struct ID3D11DeviceContext;

#include "Interfaces/IDeviceContext.h"

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
	virtual void SetConstantBuffer(IBuffer& constantBuffer);
	virtual void SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE type);
	virtual void ClearRenderTarget(IRenderTarget& renderTarget, ColorRGBA color);
	virtual void Draw(UI32 vertexCount, UI32 startVertexLocation);
	virtual void DrawIndexed(UI32 indexCount, UI32 startIndexLocation, int baseVertexLocation);

	virtual void SetVertexShader(IShader& shader);
	virtual void SetPixelShader(IShader& shader);

private:
	ID3D11DeviceContext* m_DeviceContext;
};

#endif // !DEVICECONTEXT_H