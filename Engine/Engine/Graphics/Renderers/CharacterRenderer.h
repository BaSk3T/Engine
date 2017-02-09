#ifndef CHARACTERRENDERER_H
#define CHARACTERRENDERER_H

class IDevice;
class IDeviceContext;
class IBuffer;

#include "../Renderer.h"
#include "../Shader.h"

class CharacterRenderer : public Renderer
{
public:
	CharacterRenderer(IDevice* device);
	~CharacterRenderer();

	virtual void RenderFrame();

private:
	IDevice* m_Device;
	IDeviceContext* m_DeviceContext;

	Shader<VertexShader>* m_VertexShader;
	Shader<PixelShader>* m_PixelShader;

	IBuffer* m_IndexBuffer;
	IBuffer* m_VertexBuffer;
	IBuffer* m_ConstantBuffer;
};

#endif // !CHARACTERRENDERER_H
