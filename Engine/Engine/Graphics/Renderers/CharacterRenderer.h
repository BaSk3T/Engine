#ifndef CHARACTERRENDERER_H
#define CHARACTERRENDERER_H

class IDevice;
class IDeviceContext;
class IBuffer;
class InputLayout;
class Camera;
class Mesh;
class ISampler;

#include <DirectXMath.h>

#include "../../Types.h"
#include "../Renderer.h"
#include "../Shader.h"
#include "../../AlignedAllocationPolicy.h"

class CharacterRenderer : public Renderer, public AlignedAllocationPoilicy<16>
{
public:
	CharacterRenderer(IDevice* device, Camera* camera, UI32 width, UI32 height);
	~CharacterRenderer();

	virtual void RenderFrame();
	virtual void Translate (float x, float y, float z, float w);

private:
	UI32 m_Width;
	UI32 m_Height;

	IDevice* m_Device;
	IDeviceContext* m_DeviceContext;

	Shader<VertexShader>* m_VertexShader;
	Shader<PixelShader>* m_PixelShader;

	IBuffer* m_ConstantBufferMatrices;
	IBuffer* m_ConstantBufferMaterials;
	IBuffer* m_ConstantBufferScene;
	InputLayout* m_InputLayout;

	Mesh* m_Mesh;
	ISampler* m_Sampler;
	Camera* m_Camera;

	DirectX::XMMATRIX m_World;
};

#endif // !CHARACTERRENDERER_H
