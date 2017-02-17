#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11DepthStencilView;
struct ID3D11DepthStencilState;
struct ID3D11Texture2D;
struct ID3D11RasterizerState;

#include "Interfaces/IDeviceContext.h"

class DeviceContext : public IDeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	virtual void SetRenderTarget(IRenderTarget& renderTarget);
	virtual void SetViewPort(UI32 width, UI32 height, float minDepth, float maxDepth, UI32 x, UI32 y);
	virtual void SetInputLayout(IInputLayout& inputLayout);
	virtual void SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE type);
	virtual void SetVertexBuffer(IBuffer& vertexBuffer, UI32 vertexSize);
	virtual void SetIndexBuffer(IBuffer& indexBuffer);
	virtual void VSSetConstantBuffer(IBuffer& constantBuffer);
	virtual void PSSetConstantBuffer(IBuffer& constantBuffer);
	virtual void SetVertexShader(IShader& shader);
	virtual void SetPixelShader(IShader& shader);

	virtual void ClearRenderTarget(IRenderTarget& renderTarget, ColorRGBA color);
	virtual void ClearDepthStencilBuffer();

	virtual void Draw(UI32 vertexCount, UI32 startVertexLocation);
	virtual void DrawIndexed(UI32 indexCount, UI32 startIndexLocation, int baseVertexLocation);

	ID3D11DeviceContext* GetPointer() const { return m_DeviceContext; };

private:
	friend class Device;
	void CreateDepthStencilBuffer(ID3D11Device* device, ID3D11Texture2D* depthStencilTexture);
	void CreateRasterizerState(ID3D11Device* device);

	ID3D11DeviceContext* m_DeviceContext;
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11DepthStencilState* m_DepthStencilState;
	ID3D11RasterizerState* m_RasterizerState;
};

#endif // !DEVICECONTEXT_H