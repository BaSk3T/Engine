#include "Shader.h"

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include "Device.h"

#include "../DebugHelper.h"

template <class ShaderType>
Shader<ShaderType>::Shader(IDevice& device, char* path, char* entryPoint, char* shaderTarget)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	size_t newsize = strlen(path) + 1;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, path, _TRUNCATE);

	HRESULT hr = D3DCompileFromFile(
		wcstring,
		NULL,
		NULL,/*set to D3D_COMPILE_STANDARD_FILE_INCLUDE if there are going to be #includes in shader*/
		entryPoint,
		shaderTarget,
		D3DCOMPILE_DEBUG,
		NULL,
		&m_Blob,
		NULL);

	free(wcstring);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to compile shader!\n");
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

template <>
void Shader<PixelShader>::CreateShader(IDevice& device)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	HRESULT hr = dev->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), NULL, &m_Shader.m_Pointer);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create pixel shader!\n");
	}
}

template class Shader<VertexShader>;
template class Shader<PixelShader>;