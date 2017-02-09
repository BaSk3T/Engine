#ifndef IDEVICECONTEXT_H
#define IDEVICECONTEXT_H

class IRenderTarget;
class IInputLayout;
class IBuffer;

#include "../../Types.h"

class IDeviceContext
{
public:
	IDeviceContext() {};
	virtual ~IDeviceContext() {};

	virtual void SetRenderTarget(IRenderTarget& renderTarget) = 0;
	virtual void SetViewPort(UI32 width, UI32 height, float minDepth, float maxDepth, UI32 x, UI32 y) = 0;
	virtual void SetInputLayout(IInputLayout& inputLayout) = 0;
	virtual void SetVertexBuffer(IBuffer& vertexBuffer, UI32 vertexSize) = 0;
	virtual void SetIndexBuffer(IBuffer& indexBuffer) = 0;
};

#endif // !IDEVICECONTEXT_H
