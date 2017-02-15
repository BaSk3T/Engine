#ifndef MESH_H
#define MESH_H

class IDevice;
class IDeviceContext;
class IndexBuffer;
class VertexBuffer;

#include "../Types.h"

class Mesh
{
public:
	Mesh(IDevice& device, char* path);
	~Mesh();

	void SetBuffers(IDeviceContext& deviceContext);
	UI32 GetNumberOfIndices() const { return m_NumberOfIndices; };

private:
	IndexBuffer* m_IndexBuffer;
	VertexBuffer* m_VertexBuffer;

	UI32 m_NumberOfIndices;
};

#endif // !MESH_H
