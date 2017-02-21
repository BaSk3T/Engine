#include "ConstantBuffer.h"

#include "Device.h"
#include "../DebugHelper.h"

ConstantBuffer::ConstantBuffer(IDevice& device, UI32 bufferSize, void* data)
{
	D3D11_BUFFER_DESC bufferDesc;

	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = bufferSize;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;

	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	HRESULT hr = dev->CreateBuffer(&bufferDesc, data != nullptr ? &initData : nullptr, &m_Buffer);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create constant buffer!\n");
	}
}

ConstantBuffer::~ConstantBuffer()
{
}