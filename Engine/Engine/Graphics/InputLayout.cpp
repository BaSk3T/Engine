#include "InputLayout.h"

#include <d3d11.h>

#include "Device.h"
#include "Shader.h"
#include "FormatConverter.h"
#include "../DebugHelper.h"

InputLayout::InputLayout(IDevice& device, Shader<VertexShader>& vertexShader, std::vector<InputElement>& inputElements)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;

	for (auto element : inputElements)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = element.m_SemanticName;
		desc.SemanticIndex = element.m_SemanticIndex;
		desc.Format = ConvertResourceDataFormat(element.m_Format);
		desc.InputSlot = element.m_InputSlot;
		desc.AlignedByteOffset = element.m_AlignedByteOffset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
	}

	//D3D11_INPUT_ELEMENT_DESC layout[] =
	//{
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA	, 0 },
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};

	ID3DBlob* blob = vertexShader.GetBlob();
	

	HRESULT hr = dev->CreateInputLayout(&layout[0], layout.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &m_Layout);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create input layout!\n");
	}
}

InputLayout::~InputLayout()
{
	m_Layout->Release();
}