#include "Mesh.h"

using namespace zaap;
using namespace graphics;

namespace zaap { namespace graphics {
	
	Mesh::Mesh(API::VertexBuffer* vertexBuffer)
		: m_VertexBuffer(vertexBuffer)
	{}

	Mesh::Mesh()
		: m_VertexBuffer(nullptr)
	{}

	API::VertexBuffer* Mesh::getVertexBuffer(void) const
	{
		return m_VertexBuffer;
	}
	uint Mesh::getVertexCount() const
	{
		return m_VertexBuffer->getVertexCount();
	}
}}