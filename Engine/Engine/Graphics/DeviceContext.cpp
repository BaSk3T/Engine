#include "DeviceContext.h"

#include "RenderTarget.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext)
	: m_DeviceContext(deviceContext)
{
}

DeviceContext::~DeviceContext()
{
	m_DeviceContext->Release();
}

void DeviceContext::SetRenderTarget(IRenderTarget& renderTarget)
{
	RenderTarget& rendTarget = static_cast<RenderTarget&>(renderTarget);
	ID3D11RenderTargetView* renderTargetView = rendTarget.GetPointer();

	m_DeviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);
}

void DeviceContext::SetViewPort(UI32 width, UI32 height, float minDepth, float maxDepth, UI32 x, UI32 y)
{
	D3D11_VIEWPORT vp;
	vp.Width	= (float)width;
	vp.Height	= (float)height;
	vp.MinDepth = minDepth;
	vp.MaxDepth = maxDepth;
	vp.TopLeftX = (float)x;
	vp.TopLeftY = (float)y;
	
	m_DeviceContext->RSSetViewports(1, &vp);
}
