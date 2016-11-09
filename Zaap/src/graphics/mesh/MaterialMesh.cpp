#include "MaterialMesh.h"

namespace zaap { namespace graphics {
	
	MaterialMesh::MaterialMesh()
		: Mesh(),
		m_MaterialCount(0)
	{
	}
	MaterialMesh::MaterialMesh(String name, API::VertexBuffer* vertexBuffer, Material materials[8], uint materialCount)
		: Mesh(name, vertexBuffer, ZA_MESH_TYPE_MATERIAL),
		m_MaterialCount(materialCount)
	{
		memcpy(m_Materials, materials, sizeof(Material) * materialCount);
	}

	//
	// Getters
	//
	Material const* MaterialMesh::getMaterials() const
	{
		return &m_Materials[0];
	}
	uint MaterialMesh::getMaterialCount() const
	{
		return m_MaterialCount;
	}
}}
