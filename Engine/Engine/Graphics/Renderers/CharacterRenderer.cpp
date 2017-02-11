#include "CharacterRenderer.h"

#include <DirectXMath.h>

#include "../Device.h"
#include "../DeviceContext.h"
#include "../InputLayout.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../ConstantBuffer.h"
#include "../Formats.h"

struct Vector3
{
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	float x, y, z;
};

struct Vertex
{
	Vector3 m_Position;
	Vector3 m_Color;
};

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
	m_VertexShader = new Shader<VertexShader>(*m_Device, L"Graphics/Shaders/PhongVertexShader.hlsl", "main", "vs_5_0");
	m_PixelShader = new Shader<PixelShader>(*m_Device, L"Graphics/Shaders/PhongPixelShader.hlsl", "main", "ps_5_0");

	std::vector<InputElement> vec;
	vec.push_back({ "POSITION"	, 0, RESOURCE_DATA_FORMAT_R32G32B32_FLOAT, 0, 0 });
	vec.push_back({ "COLOR"		, 0, RESOURCE_DATA_FORMAT_R32G32B32_FLOAT, 0, 12 });

	m_InputLayout = new InputLayout(*m_Device, *m_VertexShader, vec);

	// cube indices
	UI32 indices[] = {0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1 };
	Vertex cubeVertices[] = {
		{Vector3( -1.0f, -1.0f,  1.0f ), Vector3( 1.0f, 0.0f, 0.0f )},
		{Vector3(  1.0f, -1.0f,  1.0f ), Vector3( 0.0f, 0.7f, 0.7f )},
		{Vector3( -1.0f,  1.0f,  1.0f ), Vector3( 0.0f, 0.0f, 1.0f )},
		{Vector3(  1.0f,  1.0f,  1.0f ), Vector3( 0.0f, 0.0f, 1.0f )},
		{Vector3( -1.0f, -1.0f, -1.0f ), Vector3( 0.0f, 0.7f, 0.7f)},
		{Vector3(  1.0f, -1.0f, -1.0f ), Vector3( 1.0f, 0.0f, 0.0f )},
		{Vector3( -1.0f,  1.0f, -1.0f ), Vector3( 1.0f, 0.0f, 0.0f )},
		{Vector3(  1.0f,  1.0f, -1.0f ), Vector3( 0.0f, 0.7f, 0.7f)}
	};

	m_IndexBuffer = new IndexBuffer(*m_Device, 14, RESOURCE_DATA_FORMAT_R32_UINT, &indices[0]);
	m_VertexBuffer = new VertexBuffer(*m_Device, 8, sizeof(Vertex), &cubeVertices[0]);
	m_ConstantBuffer = new ConstantBuffer(*m_Device, sizeof(ConstantBufferMatrices), nullptr);

	m_DeviceContext->SetViewPort(m_Width, m_Height, 0.0f, 1.0f, 0, 0);
}
CharacterRenderer::~CharacterRenderer()
{
	delete m_InputLayout;
	delete m_ConstantBuffer;
	delete m_IndexBuffer;
	delete m_VertexBuffer;
	delete m_PixelShader;
	delete m_VertexShader;
}

void CharacterRenderer::RenderFrame()
{
	ColorRGBA clearColor = { 0, 1, 0, 0 };
	IRenderTarget* renderTarget = m_Device->GetMainRenderTarget();

	DirectX::XMVECTOR camera = { 3.5f, 3.5f, 3.5f, 0 };
	float aspectRatio = float(m_Width) / m_Height;

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(0, 0, 0);
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtRH(camera, { 0, 0, 0, 1 }, { 0, 1, 0, 0 });
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(90), aspectRatio, 0.1f, 10000.0f);

	ConstantBufferMatrices cbm;
	cbm.m_WorldViewProjection = world * view * projection;

	void* data = m_ConstantBuffer->Map(m_DeviceContext, MAP_WRITE_DISCARD);
	memcpy(data, &cbm, sizeof(ConstantBufferMatrices));
	m_ConstantBuffer->Unmap(m_DeviceContext);

	m_DeviceContext->SetVertexShader(*m_VertexShader);
	m_DeviceContext->SetPixelShader(*m_PixelShader);

	m_DeviceContext->SetInputLayout(*m_InputLayout);
	m_DeviceContext->SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE_TRIANGLESTRIP);

	m_DeviceContext->SetVertexBuffer(*m_VertexBuffer, sizeof(Vertex));
	m_DeviceContext->SetIndexBuffer(*m_IndexBuffer);
	m_DeviceContext->SetConstantBuffer(*m_ConstantBuffer);

	m_DeviceContext->SetRenderTarget(*renderTarget);
	m_DeviceContext->ClearRenderTarget(*renderTarget, clearColor);
	m_DeviceContext->ClearDepthStencilBuffer();
	
	m_DeviceContext->DrawIndexed(14, 0, 0);
	m_Device->Present();
}
