#ifndef MESH_H
#define MESH_H

class IDevice;
class IDeviceContext;
class IndexBuffer;
class IBuffer;

#include "../Types.h"

// later should be moved in another file
struct Vector4
{
	Vector4() : x(0), y(0), z(0), w(0) {};
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	float x, y, z, w;
};

struct ConstantBufferMaterials
{
	Vector4 m_MaterialAmbient;
	Vector4 m_MaterialDiffuse;
	Vector4 m_MaterialSpecular;
};

class Mesh
{
public:
	Mesh(IDevice& device, char* path);
	~Mesh();

	void SetBuffers(IDeviceContext& deviceContext);
	void SetMaterialsBuffer(IDeviceContext& deviceContext, UI32 slot);
	UI32 GetNumberOfIndices() const { return m_NumberOfIndices; };

	Vector4 m_MaterialAmbient;
	Vector4 m_MaterialDiffuse;
	Vector4 m_MaterialSpecular;

private:
	IBuffer* m_IndexBuffer;
	IBuffer* m_VertexBuffer;
	IBuffer* m_ConstantBufferMaterials;

	UI32 m_NumberOfIndices;
};

#endif // !MESH_H
