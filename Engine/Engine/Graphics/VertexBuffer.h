#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class IDevice;
struct ID3D11Buffer;

#include "Interfaces/IBuffer.h"
#include "../Types.h"

class VertexBuffer : public IBuffer
{
public:
	VertexBuffer(IDevice& device, UI32 bufferSize, void* data);
	~VertexBuffer();

	ID3D11Buffer* GetPointer() const { return m_Buffer; };

private:
	ID3D11Buffer* m_Buffer;
};

#endif // !VERTEXBUFFER_H
