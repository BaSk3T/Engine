#include "DeviceContext.h"

#include "Device.h"

#include "RenderTarget.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "FormatConverter.h"
#include "Shader.h"

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

	UI32 offset = 0;

	m_DeviceContext->IASetVertexBuffers(0, 1, &buffer, &vertexSize, &offset);
}

void DeviceContext::SetIndexBuffer(IBuffer& indexBuffer)
{
	IndexBuffer& indexBuff = static_cast<IndexBuffer&>(indexBuffer);
	RESOURCE_DATA_FORMAT dataFormat = indexBuff.GetFormat();

	ID3D11Buffer* buffer = indexBuff.GetPointer();

	m_DeviceContext->IASetIndexBuffer(buffer, ConvertResourceDataFormat(dataFormat), 0);
}

void DeviceContext::SetConstantBuffer(IBuffer& constantBuffer)
{
	ID3D11Buffer* buffer = static_cast<ConstantBuffer&>(constantBuffer).GetPointer();

	m_DeviceContext->VSSetConstantBuffers(0, 1, &buffer);
}

void DeviceContext::SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE type)
{
	m_DeviceContext->IASetPrimitiveTopology(ConvertPrimitive(type));
}

void DeviceContext::ClearRenderTarget(IRenderTarget& renderTarget, ColorRGBA color)
{
	RenderTarget& rendTarget = static_cast<RenderTarget&>(renderTarget);
	ID3D11RenderTargetView* renderTargetView = rendTarget.GetPointer();

	m_DeviceContext->ClearRenderTargetView(renderTargetView, color.rgba);
}

void DeviceContext::Draw(UI32 vertexCount, UI32 startVertexLocation)
{
	m_DeviceContext->Draw(vertexCount, startVertexLocation);
}

void DeviceContext::DrawIndexed(UI32 indexCount, UI32 startIndexLocation, int baseVertexLocation)
{
	m_DeviceContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void DeviceContext::SetVertexShader(IShader& shader)
{
	Shader<VertexShader>& vertexShader = static_cast<Shader<VertexShader>&>(shader);

	m_DeviceContext->VSSetShader(vertexShader.GetShader().m_Pointer, NULL, 0);
}

void DeviceContext::SetPixelShader(IShader& shader)
{
	Shader<PixelShader>& pixelShader = static_cast<Shader<PixelShader>&>(shader);

	m_DeviceContext->PSSetShader(pixelShader.GetShader().m_Pointer, NULL, 0);
}