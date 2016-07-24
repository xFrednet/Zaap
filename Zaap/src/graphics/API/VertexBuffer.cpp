#include "VertexBuffer.h"

namespace zaap { namespace graphics { namespace API {

	VertexBuffer::VertexBuffer(uint vertexCount)
		: m_VertexCount(vertexCount)
	{
	}

	uint VertexBuffer::getVertexCount(void) const
	{
		return m_VertexCount;
	}

}}}