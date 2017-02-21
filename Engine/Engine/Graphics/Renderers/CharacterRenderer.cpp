#include "CharacterRenderer.h"

#include "../Device.h"
#include "../DeviceContext.h"
#include "../InputLayout.h"
#include "../ConstantBuffer.h"
#include "../Formats.h"
#include "../Camera.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../Sampler.h"

struct ConstantBufferMatrices
{
	DirectX::XMMATRIX m_WorldViewProjection;
	DirectX::XMMATRIX m_World;
};

struct ConstantBufferMaterials
{
	Vector4 m_MaterialAmbient;
	Vector4 m_MaterialDiffuse;
	Vector4 m_MaterialSpecular;
};

struct ConstantBufferScene
{
	Vector4 m_LightDirection;
	Vector4 m_CameraPosition;
};

CharacterRenderer::CharacterRenderer(IDevice* device, Camera* camera, UI32 width, UI32 height)
	: m_DeviceContext(device->GetImmediateContext()),
	m_Device(device),
	m_Camera(camera),
	m_Width(width),
	m_Height(height),
	m_World(DirectX::XMMatrixTranslation(0, 0, 0))
{
	m_Mesh = new Mesh(*m_Device, "Models/dragon.obj");

	m_VertexShader = new Shader<VertexShader>(*m_Device, L"Graphics/Shaders/PhongVertexShader.hlsl", "main", "vs_5_0");
	m_PixelShader = new Shader<PixelShader>(*m_Device, L"Graphics/Shaders/PhongPixelShader.hlsl", "main", "ps_5_0");

	std::vector<InputElement> inputElements;
	inputElements.push_back({ "POSITION", 0, RESOURCE_DATA_FORMAT_R32G32B32A32_FLOAT, 0, 0 });
	inputElements.push_back({ "NORMAL"  , 0, RESOURCE_DATA_FORMAT_R32G32B32A32_FLOAT, 0, 16 });
	inputElements.push_back({ "TEXCOORD", 0, RESOURCE_DATA_FORMAT_R32G32_FLOAT,		0, 32 });

	ConstantBufferMaterials cbMaterials;
	cbMaterials.m_MaterialAmbient = m_Mesh->m_MaterialAmbient;
	cbMaterials.m_MaterialDiffuse = m_Mesh->m_MaterialDiffuse;
	cbMaterials.m_MaterialSpecular = m_Mesh->m_MaterialSpecular;

	m_InputLayout = new InputLayout(*m_Device, *m_VertexShader, inputElements);
	m_ConstantBufferMatrices = new ConstantBuffer(*m_Device, sizeof(ConstantBufferMatrices), nullptr);
	m_ConstantBufferMaterials = new ConstantBuffer(*m_Device, sizeof(ConstantBufferMaterials), &cbMaterials);
	m_ConstantBufferScene = new ConstantBuffer(*m_Device, sizeof(ConstantBufferScene), nullptr);

	m_DeviceContext->SetViewPort(m_Width, m_Height, 0.0f, 1.0f, 0, 0);

	m_Sampler = new Sampler(*m_Device);
	m_DeviceContext->PSSetSampler(*m_Sampler, 0);
}
CharacterRenderer::~CharacterRenderer()
{
	delete m_Sampler;
	delete m_Mesh;
	delete m_InputLayout;
	delete m_ConstantBufferMatrices;
	delete m_ConstantBufferMaterials;
	delete m_ConstantBufferScene;
	delete m_PixelShader;
	delete m_VertexShader;
}

void CharacterRenderer::RenderFrame()
{
	ColorRGBA clearColor = { 0.3f, 0, 1, 0 };
	IRenderTarget* renderTarget = m_Device->GetMainRenderTarget();

	float aspectRatio = float(m_Width) / m_Height;

	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(45), aspectRatio, 1.0f, 100.0f);

	float* cameraPosition = m_Camera->GetPosition().m128_f32;

	ConstantBufferMatrices cbMatrices;
	cbMatrices.m_WorldViewProjection = m_World * m_Camera->GetViewMatrix() * projection;
	cbMatrices.m_World = m_World;

	ConstantBufferScene cbScene;
	cbScene.m_LightDirection = Vector4(0, 0, 1, 0);
	cbScene.m_CameraPosition = Vector4(cameraPosition[0], cameraPosition[1], cameraPosition[2], 0);

	void* dataMatrices = m_ConstantBufferMatrices->Map(m_DeviceContext, MAP_WRITE_DISCARD);
	memcpy(dataMatrices, &cbMatrices, sizeof(ConstantBufferMatrices));
	m_ConstantBufferMatrices->Unmap(m_DeviceContext);

	void* dataScene = m_ConstantBufferScene->Map(m_DeviceContext, MAP_WRITE_DISCARD);
	memcpy(dataScene, &cbScene, sizeof(ConstantBufferScene));
	m_ConstantBufferScene->Unmap(m_DeviceContext);

	m_DeviceContext->SetVertexShader(*m_VertexShader);
	m_DeviceContext->SetPixelShader(*m_PixelShader);

	m_DeviceContext->SetInputLayout(*m_InputLayout);
	m_DeviceContext->SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TYPE_TRIANGLELIST);

	m_Mesh->SetBuffers(*m_DeviceContext);

	m_DeviceContext->VSSetConstantBuffer(*m_ConstantBufferMatrices, 0);
	m_DeviceContext->VSSetConstantBuffer(*m_ConstantBufferScene, 1);

	m_DeviceContext->PSSetConstantBuffer(*m_ConstantBufferMaterials, 0);
	m_DeviceContext->PSSetConstantBuffer(*m_ConstantBufferScene, 1);

	m_DeviceContext->SetRenderTarget(*renderTarget);
	m_DeviceContext->ClearRenderTarget(*renderTarget, clearColor);
	m_DeviceContext->ClearDepthStencilBuffer();
	
	m_DeviceContext->DrawIndexed(m_Mesh->GetNumberOfIndices(), 0, 0);
	m_Device->Present();
}

void CharacterRenderer::Translate(float x, float y, float z, float w)
{
	DirectX::XMVECTOR vec = { x, y, z, w };
	DirectX::XMMATRIX translated = DirectX::XMMatrixTranslationFromVector(vec);
	m_World *= translated;
}
