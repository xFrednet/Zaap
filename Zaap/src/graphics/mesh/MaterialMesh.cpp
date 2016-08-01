#include "MaterialMesh.h"

namespace zaap { namespace graphics {
	
	MaterialMesh::MaterialMesh()
		: Mesh(),
		m_Materials(nullptr),
		m_MaterialCount(0)
	{
	}
	MaterialMesh::MaterialMesh(String name, API::VertexBuffer* vertexBuffer, Material* materials, uint materialCount)
		: Mesh(name, vertexBuffer, MeshType::MATERIAL_MESH),
		m_Materials(materials),
		m_MaterialCount(materialCount)
	{
	}

	//
	// Getters
	//
	Material* MaterialMesh::getMaterials() const
	{
		return m_Materials;
	}
	uint MaterialMesh::getMaterialCount() const
	{
		return m_MaterialCount;
	}
}}
