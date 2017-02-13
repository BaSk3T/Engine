#ifndef CHARACTERRENDERER_H
#define CHARACTERRENDERER_H

class IDevice;
class IDeviceContext;
class IBuffer;
class InputLayout;

#include "../../Types.h"
#include "../Renderer.h"
#include "../Shader.h"
#include "../Camera.h"

class CharacterRenderer : public Renderer
{
public:
	CharacterRenderer(IDevice* device, UI32 width, UI32 height);
	~CharacterRenderer();

	virtual void RenderFrame();

	Camera* m_Camera;

private:
	UI32 m_Width;
	UI32 m_Height;

	IDevice* m_Device;
	IDeviceContext* m_DeviceContext;

	Shader<VertexShader>* m_VertexShader;
	Shader<PixelShader>* m_PixelShader;

	IBuffer* m_IndexBuffer;
	IBuffer* m_VertexBuffer;
	IBuffer* m_ConstantBuffer;
	InputLayout* m_InputLayout;
};

#endif // !CHARACTERRENDERER_H
