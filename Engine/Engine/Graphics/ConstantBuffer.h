#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

class IDevice;

#include "Buffer.h"
#include "../Types.h"

class ConstantBuffer : public Buffer
{
public:
	ConstantBuffer(IDevice& device, UI32 bufferSize, void* data);
	~ConstantBuffer();

	ID3D11Buffer* GetPointer() const { return m_Buffer; };
};

#endif // !CONSTANTBUFFER_H
