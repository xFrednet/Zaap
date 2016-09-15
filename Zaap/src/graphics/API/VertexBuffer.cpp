#include "VertexBuffer.h"

#include <graphics/DX/DXVertexBuffer.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace API {

	std::vector<VertexBuffer*> VertexBuffer::s_VertexBuffers;

	uint VertexBuffer::s_TotalDrawCount = 0;

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

	//
	// Total Draw Count
	//
	uint VertexBuffer::getTotalDrawCount()
	{
		return s_TotalDrawCount;
	}
	void VertexBuffer::clearTotalDrawCount()
	{
		s_TotalDrawCount = 0;
	}

	//
	// Class methods
	//
	uint VertexBuffer::getVertexCount(void) const
	{
		return m_VertexCount;
	}

}}}
