#include "IndexBuffer.h"

#include <assert.h>

#include "Device.h"
#include "../DebugHelper.h"

IndexBuffer::IndexBuffer(IDevice& device, UI32 indicesCount, RESOURCE_DATA_FORMAT dataFormat, void* data)
	: m_DataFormat(dataFormat)
{
	assert(dataFormat == RESOURCE_DATA_FORMAT_R16_UINT || dataFormat == RESOURCE_DATA_FORMAT_R32_UINT);

	UI32 formatSize = 0;

	if (dataFormat == RESOURCE_DATA_FORMAT_R16_UINT)
		formatSize = 2;
	else // dataFormat == RESOURCE_DATA_FORMAT_R32_UINT
		formatSize = 4;

	D3D11_BUFFER_DESC bufferDesc;

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = indicesCount * formatSize;
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
		OUTPUT_DEBUG("Failed to create index buffer!\n");
	}
}

IndexBuffer::~IndexBuffer()
{
}