#include "DeviceContext.h"

#include "Device.h"

#include "RenderTarget.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "FormatConverter.h"

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

void DeviceContext::SetInputLayout(IInputLayout& inputLayout)
{
	ID3D11InputLayout* inputLay = static_cast<InputLayout&>(inputLayout).GetPointer();

	m_DeviceContext->IASetInputLayout(inputLay);
}

void DeviceContext::SetVertexBuffer(IBuffer& vertexBuffer, UI32 vertexSize)
{
	ID3D11Buffer* buffer = static_cast<VertexBuffer&>(vertexBuffer).GetPointer();

	m_DeviceContext->IASetVertexBuffers(0, 1, &buffer, &vertexSize, 0);
}

void DeviceContext::SetIndexBuffer(IBuffer& indexBuffer)
{
	IndexBuffer& indexBuff = static_cast<IndexBuffer&>(indexBuffer);
	RESOURCE_DATA_FORMAT dataFormat = indexBuff.GetFormat();

	ID3D11Buffer* buffer = indexBuff.GetPointer();

	m_DeviceContext->IASetIndexBuffer(buffer, ConvertResourceDataFormat(dataFormat), 0);
}
