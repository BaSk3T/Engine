#include "CharacterRenderer.h"

#include <DirectXMath.h>

#include "../Device.h"
#include "../DeviceContext.h"
#include "../InputLayout.h"
#include "../ConstantBuffer.h"
#include "../Formats.h"
#include "../Camera.h"
#include "../Mesh.h"

struct ConstantBufferMatrices
{
	DirectX::XMMATRIX m_WorldViewProjection;
};

CharacterRenderer::CharacterRenderer(IDevice* device, UI32 width, UI32 height)
	: m_DeviceContext(device->GetImmediateContext()),
	m_Device(device),
	m_Width(width),
	m_Height(height)
{
	m_Camera = new(_aligned_malloc(sizeof(Camera), 16)) Camera(0, 0, 15.0f);

	m_Mesh = new Mesh(*m_Device, "Models/dragon.obj");

	m_VertexShader = new Shader<VertexShader>(*m_Device, L"Graphics/Shaders/PhongVertexShader.hlsl", "main", "vs_5_0");
	m_PixelShader = new Shader<PixelShader>(*m_Device, L"Graphics/Shaders/PhongPixelShader.hlsl", "main", "ps_5_0");

	std::vector<InputElement> vec;
	vec.push_back({ "POSITION"	, 0, RESOURCE_DATA_FORMAT_R32G32B32_FLOAT, 0, 0 });
	vec.push_back({ "COLOR"		, 0, RESOURCE_DATA_FORMAT_R32G32B32_FLOAT, 0, 12 });

	m_InputLayout = new InputLayout(*m_Device, *m_VertexShader, vec);
	m_ConstantBuffer = new ConstantBuffer(*m_Device, sizeof(ConstantBufferMatrices), nullptr);

	m_DeviceContext->SetViewPort(m_Width, m_Height, 0.0f, 1.0f, 0, 0);
}
CharacterRenderer::~CharacterRenderer()
{
	_aligned_free(m_Camera);

	delete m_Mesh;
	delete m_InputLayout;
	delete m_ConstantBuffer;
	delete m_PixelShader;
	delete m_VertexShader;
}

void CharacterRenderer::RenderFrame()
{
	ColorRGBA clearColor = { 0, 1, 0, 0 };
	IRenderTarget* renderTarget = m_Device->GetMainRenderTarget();

	float aspectRatio = float(m_Width) / m_Height;

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(0, 0, 0);
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(45), aspectRatio, 1.0f, 100.0f);

	ConstantBufferMatrices cbm;
	cbm.m_WorldViewProjection = world * m_Camera->GetViewMatrix() * projection;

	void* data = m_ConstantBuffer->Map(m_DeviceContext, MAP_WRITE_DISCARD);
	memcpy(data, &cbm, sizeof(ConstantBufferMatrices));
	m_ConstantBuffer->Unmap(m_DeviceContext);

	m_DeviceContext->SetVertexShader(*m_VertexShader);
	m_DeviceContext->SetPixelShader(*m_PixelShader);

	m_DeviceContext->SetInputLayout(*m_InputLayout);
	m_DeviceContext->SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE_TRIANGLELIST);

	m_Mesh->SetBuffers(*m_DeviceContext);
	m_DeviceContext->SetConstantBuffer(*m_ConstantBuffer);

	m_DeviceContext->SetRenderTarget(*renderTarget);
	m_DeviceContext->ClearRenderTarget(*renderTarget, clearColor);
	m_DeviceContext->ClearDepthStencilBuffer();
	
	m_DeviceContext->DrawIndexed(m_Mesh->GetNumberOfIndices(), 0, 0);
	m_Device->Present();
}
