#include "Buffer.h"

#include <d3d11.h>

#include "DeviceContext.h"
#include "FormatConverter.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
	m_Buffer->Release();
}

void* Buffer::Map(IDeviceContext* deviceContext, MAP_TYPE map)
{
	ID3D11DeviceContext* devContext = static_cast<DeviceContext*>(deviceContext)->GetPointer();

	D3D11_MAPPED_SUBRESOURCE ms;
	devContext->Map(m_Buffer, 0, ConvertMapType(map), 0, &ms);

	return ms.pData;
}

void Buffer::Unmap(IDeviceContext* deviceContext)
{
	ID3D11DeviceContext* devContext = static_cast<DeviceContext*>(deviceContext)->GetPointer();
	devContext->Unmap(m_Buffer, 0);
}
