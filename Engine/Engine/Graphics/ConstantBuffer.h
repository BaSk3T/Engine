#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

class IDevice;
struct ID3D11Buffer;

#include "Interfaces/IBuffer.h"
#include "../Types.h"

class ConstantBuffer : public IBuffer
{
public:
	ConstantBuffer(IDevice& device, UI32 bufferSize, void* data);
	~ConstantBuffer();

	ID3D11Buffer* GetPointer() const { return m_Buffer; };

private:
	ID3D11Buffer* m_Buffer;
};

#endif // !CONSTANTBUFFER_H
