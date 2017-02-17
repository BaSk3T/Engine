#ifndef MESH_H
#define MESH_H

class IDevice;
class IDeviceContext;
class IndexBuffer;
class VertexBuffer;

#include "../Types.h"

// later should be moved in another file
struct Vector4
{
	Vector4() : x(0), y(0), z(0), w(0) {};
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	float x, y, z, w;
};

class Mesh
{
public:
	Mesh(IDevice& device, char* path);
	~Mesh();

	void SetBuffers(IDeviceContext& deviceContext);
	UI32 GetNumberOfIndices() const { return m_NumberOfIndices; };

	Vector4 m_MaterialAmbient;
	Vector4 m_MaterialDiffuse;
	Vector4 m_MaterialSpecular;

private:
	IndexBuffer* m_IndexBuffer;
	VertexBuffer* m_VertexBuffer;

	UI32 m_NumberOfIndices;
};

#endif // !MESH_H
