#include "RenderTarget.h"

#include "Device.h"

RenderTarget::RenderTarget(IDevice& device, ID3D11Texture2D* tex)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();
	dev->CreateRenderTargetView(tex, NULL, &m_RenderTarget);
}

RenderTarget::~RenderTarget()
{
	m_RenderTarget->Release();
}