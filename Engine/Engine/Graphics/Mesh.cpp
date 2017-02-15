#include "Mesh.h"

#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Device.h"
#include "DeviceContext.h"

// later should be moved in another file
struct Vector3
{
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	float x, y, z;
};

// later should be moved in another file
struct Vertex
{
	Vector3 m_Position;
	Vector3 m_Color;
};

Mesh::Mesh(IDevice& device, char* path)
{
	Assimp::Importer importer;
	const aiScene* modelLoaded = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

	std::vector<UI32> indices;
	std::vector<Vertex> vertices;

	for (UI32 i = 0; i < modelLoaded->mNumMeshes; i++)
	{
		aiMesh* mesh = modelLoaded->mMeshes[i];

		for (UI32 k = 0; k < mesh->mNumFaces; k++)
		{
			int vert0Index = mesh->mFaces[k].mIndices[0];
			int vert1Index = mesh->mFaces[k].mIndices[1];
			int vert2Index = mesh->mFaces[k].mIndices[2];

			indices.push_back(vert0Index);
			indices.push_back(vert1Index);
			indices.push_back(vert2Index);
		}

		for (UI32 k = 0; k < mesh->mNumVertices; k++)
		{
			aiVector3D vertex = mesh->mVertices[k];
			vertices.push_back({ Vector3(vertex.x, vertex.y, vertex.z), Vector3(0, 0, 0) });
		}
	}

	m_NumberOfIndices = indices.size();

	m_IndexBuffer = new IndexBuffer(device, indices.size(), RESOURCE_DATA_FORMAT_R32_UINT, &indices[0]);
	m_VertexBuffer = new VertexBuffer(device, vertices.size(), sizeof(Vertex), &vertices[0]);
}

Mesh::~Mesh()
{
	delete m_IndexBuffer;
	delete m_VertexBuffer;
}

void Mesh::SetBuffers(IDeviceContext& deviceContext)
{
	deviceContext.SetVertexBuffer(*m_VertexBuffer, sizeof(Vertex));
	deviceContext.SetIndexBuffer(*m_IndexBuffer);
}
