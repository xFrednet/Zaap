#include "Mesh.h"

using namespace zaap;
using namespace graphics;

namespace zaap { namespace graphics {
	
	//////////////////////////////////////////////////////////////////////////////
	// TEXTURE_VERTEX  // TEXTURE_VERTEX  // TEXTURE_VERTEX  // TEXTURE_VERTEX  //
	//////////////////////////////////////////////////////////////////////////////
	TEXTURE_VERTEX::TEXTURE_VERTEX()
	{
	}

	TEXTURE_VERTEX::TEXTURE_VERTEX(math::Vec3 vertex, math::Vec3 normal, math::Vec2 texCoords)
		: Position(vertex),
		Normal(normal),
		TexCoord(texCoords)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	// MATERIAL_VERTEX  // MATERIAL_VERTEX  // MATERIAL_VERTEX  // MATERIAL_VERTEX  //
	//////////////////////////////////////////////////////////////////////////////////
	MATERIAL_VERTEX::MATERIAL_VERTEX(math::Vec3 position, math::Vec3 normal, uint material)
		: Position(position),
		Normal(normal),
		Material(material)
	{
	}

	MATERIAL_VERTEX::MATERIAL_VERTEX()
		: Position(),
		Normal(),
		Material(0)
	{
	}

	//////////////////////////////////////////////////////////
	// Mesh // Mesh // Mesh // Mesh // Mesh // Mesh // Mesh //
	//////////////////////////////////////////////////////////
	Mesh::Mesh(String name, API::VertexBuffer* vertexBuffer, MeshType type)
		: m_Name(name),
		m_VertexBuffer(vertexBuffer),
		m_TYPE(type)
	{}

	Mesh::Mesh()
		: m_Name("NULL"),
		m_VertexBuffer(nullptr),
		m_TYPE(MeshType::NONE)
	{}

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

	MeshType Mesh::getType() const
	{
		return m_TYPE;
	}
}}