#include "Mesh.h"

using namespace zaap;
using namespace graphics;

namespace zaap { namespace graphics {
	
	Mesh::Mesh(String name, API::VertexBuffer* vertexBuffer)
		: m_Name(name),
		m_VertexBuffer(vertexBuffer)
	{}

	Mesh::Mesh()
		: m_Name("NULL"),
		m_VertexBuffer(nullptr)
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
}}