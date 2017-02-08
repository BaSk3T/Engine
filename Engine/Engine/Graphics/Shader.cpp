#include "Shader.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include "Device.h"

#include "../DebugHelper.h"

template <class ShaderType>
Shader<ShaderType>::Shader(IDevice& device, wchar_t* path, char* entryPoint, char* shaderTarget)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	HRESULT hr = D3DCompileFromFile(
		path,
		NULL,
		NULL,/*set to D3D_COMPILE_STANDARD_FILE_INCLUDE if there are going to be #includes in shader*/
		entryPoint,
		shaderTarget,
		D3DCOMPILE_DEBUG,
		NULL,
		&m_Blob,
		NULL);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to compile vertex shader!\n");
	}

	CreateShader(device);
}

template <class ShaderType>
Shader<ShaderType>::~Shader()
{
	m_Blob->Release();
}

template <class ShaderType>
void Shader<ShaderType>::CreateShader(IDevice& device)
{
}

template <>
void Shader<VertexShader>::CreateShader(IDevice& device)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	HRESULT hr = dev->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), NULL, &m_Shader.m_Pointer);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create vertex shader!\n");
	}
}