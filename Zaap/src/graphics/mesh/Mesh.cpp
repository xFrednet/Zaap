#include "Mesh.h"

#include "MeshManager.h"
#include "util/Loader.h"

namespace zaap { namespace graphics {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_TEXTURE_VERTEX //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_TEXTURE_VERTEX::ZA_TEXTURE_VERTEX()
	{
	}

	ZA_TEXTURE_VERTEX::ZA_TEXTURE_VERTEX(Vec3 vertex, Vec3 normal, Vec2 texCoords)
		: Position(vertex),
		Normal(normal),
		TexCoord(texCoords)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MATERIAL_VERTEX //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_MATERIAL_VERTEX::ZA_MATERIAL_VERTEX(Vec3 position, Vec3 normal, uint material)
		: Position(position),
		Normal(normal),
		Material(material)
	{
	}

	ZA_MATERIAL_VERTEX::ZA_MATERIAL_VERTEX()
		: Position(),
		Normal(),
		Material(0)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_TERRAIN_VERTEX //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_TERRAIN_VERTEX::ZA_TERRAIN_VERTEX(Vec3 position, Vec3 normal, Vec3 texMapColor, Vec2 texCoord)
		: Position(position),
		Normal(normal),
		TexMapColor(texMapColor),
		TexCoord(texCoord)
	{
	}

	ZA_TERRAIN_VERTEX::ZA_TERRAIN_VERTEX()
		: Position(),
		Normal(),
		TexMapColor(),
		TexCoord()
	{
	}

	Mesh* Mesh::GetOrLoad(const String& file, bool isTexturedMesh)
	{
		if (MeshManager::Contains(file))
			return MeshManager::Get(file);

		return Loader::LoadOBJFile(file, isTexturedMesh);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Mesh //
	/* //////////////////////////////////////////////////////////////////////////////// */
	Mesh::Mesh(String name, API::VertexBuffer* vertexBuffer, ZA_MESH_TYPE type)
		: m_Name(name),
		m_VertexBuffer(vertexBuffer),
		m_TYPE(type)
	{
		MeshManager::Add(this);
	}

	//
	// VertexBuffer
	//
	API::VertexBuffer* Mesh::getVertexBuffer(void) const
	{
		return m_VertexBuffer;
	}
	uint Mesh::getVertexCount() const
	{
		return m_VertexBuffer->getVertexCount();
	}

	String Mesh::getName() const
	{
		return m_Name;
	}

	ZA_MESH_TYPE Mesh::getType() const
	{
		return m_TYPE;
	}

	ZA_SHADER_TYPE Mesh::getTargetShader() const
	{
		switch (m_TYPE)
		{
			case ZA_MESH_TYPE_TEXTURED:
				return ZA_SHADER_TEXTURE_SHADER;

			case ZA_MESH_TYPE_MATERIAL:
				return ZA_SHADER_MATERIAL_SHADER;
			
			case ZA_MESH_TYPE_UNKNOWN:
			default:
				return ZA_SHADER_UNKNOWN;
		}
	}
}}