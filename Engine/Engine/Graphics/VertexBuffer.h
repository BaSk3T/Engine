#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class IDevice;

#include "Buffer.h"
#include "../Types.h"

class VertexBuffer : public Buffer
{
public:
	VertexBuffer(IDevice& device, UI32 vertexCount, UI32 vertexSize, void* data);
	~VertexBuffer();

	ID3D11Buffer* GetPointer() const { return m_Buffer; };
};

#endif // !VERTEXBUFFER_H
