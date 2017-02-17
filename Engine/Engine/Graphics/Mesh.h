#ifndef MESH_H
#define MESH_H

class IDevice;
class IDeviceContext;
class IndexBuffer;
class VertexBuffer;

#include "../Types.h"

// later should be moved in another file
struct Vector3
{
	Vector3() : x(0), y(0), z(0) {};
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	float x, y, z;
};

class Mesh
{
public:
	Mesh(IDevice& device, char* path);
	~Mesh();

	void SetBuffers(IDeviceContext& deviceContext);
	UI32 GetNumberOfIndices() const { return m_NumberOfIndices; };

	Vector3 m_MaterialAmbient;
	Vector3 m_MaterialDiffuse;
	Vector3 m_MaterialSpecular;

private:
	IndexBuffer* m_IndexBuffer;
	VertexBuffer* m_VertexBuffer;

	UI32 m_NumberOfIndices;
};

#endif // !MESH_H
