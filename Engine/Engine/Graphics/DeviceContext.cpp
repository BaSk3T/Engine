#include "DeviceContext.h"

#include "../DebugHelper.h"

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
	m_RasterizerState->Release();
	m_DepthStencilView->Release();
	m_DepthStencilState->Release();
	m_DeviceContext->Release();
}

void DeviceContext::SetRenderTarget(IRenderTarget& renderTarget)
{
	RenderTarget& rendTarget = static_cast<RenderTarget&>(renderTarget);
	ID3D11RenderTargetView* renderTargetView = rendTarget.GetPointer();

	m_DeviceContext->OMSetRenderTargets(1, &renderTargetView, m_DepthStencilView);
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

void DeviceContext::VSSetConstantBuffer(IBuffer& constantBuffer, UI32 slot)
{
	ID3D11Buffer* buffer = static_cast<ConstantBuffer&>(constantBuffer).GetPointer();

	m_DeviceContext->VSSetConstantBuffers(slot, 1, &buffer);
}

void DeviceContext::PSSetConstantBuffer(IBuffer& constantBuffer, UI32 slot)
{
	ID3D11Buffer* buffer = static_cast<ConstantBuffer&>(constantBuffer).GetPointer();

	m_DeviceContext->PSSetConstantBuffers(slot, 1, &buffer);
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

void DeviceContext::ClearDepthStencilBuffer()
{
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
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

void DeviceContext::CreateDepthStencilBuffer(ID3D11Device* device, ID3D11Texture2D* depthStencilTexture)
{
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	HRESULT hr = device->CreateDepthStencilState(&dsDesc, &m_DepthStencilState);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create depth stencil state!\n");
	}

	// Bind depth stencil state
	m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	// Create the depth stencil view
	hr = device->CreateDepthStencilView(depthStencilTexture, // Depth stencil texture
		&descDSV, // Depth stencil desc
		&m_DepthStencilView);  // [out] Depth stencil view

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create depth stencil view!\n");
	}
}

void DeviceContext::CreateRasterizerState(ID3D11Device* device)
{
	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.CullMode = D3D11_CULL_BACK;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = false;

	device->CreateRasterizerState(&rasterizerState, &m_RasterizerState);

	m_DeviceContext->RSSetState(m_RasterizerState);
}
