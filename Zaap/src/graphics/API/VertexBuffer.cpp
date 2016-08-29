#include "VertexBuffer.h"

#include <graphics/DX/DXVertexBuffer.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace API {

	std::vector<VertexBuffer*> VertexBuffer::s_VertexBuffers;

	VertexBuffer::VertexBuffer(uint vertexCount)
		: m_VertexCount(vertexCount)
	{
	}

	VertexBuffer* VertexBuffer::CreateVertexbuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount)
	{
		VertexBuffer* vBuffer = new DX::DXVertexBuffer(vertices, vertexSize, vCount, indices, indexCount);

		s_VertexBuffers.push_back(vBuffer);

		return vBuffer;
	}

	void VertexBuffer::Cleanup()
	{
		for (VertexBuffer* vBuffer : s_VertexBuffers)
		{
			vBuffer->cleanup();
			delete vBuffer;
		}

		ZAAP_CLEANUP_LOG("VertexBuffer");
	}

	uint VertexBuffer::getVertexCount(void) const
	{
		return m_VertexCount;
	}

}}}
