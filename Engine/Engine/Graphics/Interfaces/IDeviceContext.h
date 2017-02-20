#ifndef IDEVICECONTEXT_H
#define IDEVICECONTEXT_H

class IRenderTarget;
class IInputLayout;
class IBuffer;
class IShader;
class ITexture;
class ISampler;

#include "../../Types.h"
#include "../Formats.h"

union ColorRGBA
{
	struct { float r; float g; float b; float a; };

	float rgba[4];
};

class IDeviceContext
{
public:
	IDeviceContext() {};
	virtual ~IDeviceContext() {};

	virtual void SetRenderTarget(IRenderTarget& renderTarget) = 0;
	virtual void SetViewPort(UI32 width, UI32 height, float minDepth, float maxDepth, UI32 x, UI32 y) = 0;
	virtual void SetInputLayout(IInputLayout& inputLayout) = 0;
	virtual void SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE type) = 0;
	virtual void SetVertexBuffer(IBuffer& vertexBuffer, UI32 vertexSize) = 0;
	virtual void SetIndexBuffer(IBuffer& indexBuffer) = 0;
	virtual void VSSetConstantBuffer(IBuffer& constantBuffer, UI32 slot) = 0;
	virtual void PSSetConstantBuffer(IBuffer& constantBuffer, UI32 slot) = 0;
	virtual void SetVertexShader(IShader& shader) = 0;
	virtual void SetPixelShader(IShader& shader) = 0;
	virtual void PSSetTexture(ITexture& texture, UI32 slot) = 0;
	virtual void PSSetSampler(ISampler& sampler, UI32 slot) = 0;

	virtual void ClearRenderTarget(IRenderTarget& renderTarget, ColorRGBA color) = 0;
	virtual void ClearDepthStencilBuffer() = 0;

	virtual void Draw(UI32 vertexCount, UI32 startVertexLocation) = 0;
	virtual void DrawIndexed(UI32 indexCount, UI32 startIndexLocation, int baseVertexLocation) = 0;
};

#endif // !IDEVICECONTEXT_H
