#include "VertexBuffer.h"

#include "Device.h"
#include "../DebugHelper.h"

// https://msdn.microsoft.com/en-us/library/windows/desktop/ff476899(v=vs.85).aspx

VertexBuffer::VertexBuffer(IDevice& device, UI32 bufferSize, void* data)
{
	D3D11_BUFFER_DESC bufferDesc;

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = bufferSize; // typeof(vertex) * n vertices
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;

	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	HRESULT hr = dev->CreateBuffer(&bufferDesc, data != nullptr ? &initData : nullptr, &m_Buffer);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create vertex buffer!\n");
	}
}

VertexBuffer::~VertexBuffer()
{
	m_Buffer->Release();
}