#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IDevice;

#include "Buffer.h"
#include "../Types.h"
#include "Formats.h"

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(IDevice& device, UI32 bufferSize, RESOURCE_DATA_FORMAT dataFormat, void* data);
	~IndexBuffer();

	ID3D11Buffer* GetPointer() const { return m_Buffer; };
	RESOURCE_DATA_FORMAT GetFormat() const { return m_DataFormat;  }

private:
	RESOURCE_DATA_FORMAT m_DataFormat;
};

#endif // !INDEXBUFFER_H
