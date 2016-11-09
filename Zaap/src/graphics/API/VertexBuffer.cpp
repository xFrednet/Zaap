#include "VertexBuffer.h"

#include <graphics/API/DX/DXVertexBuffer.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace API {

	std::vector<VertexBuffer*> VertexBuffer::s_VertexBuffers;

	uint VertexBuffer::s_TotalDrawCount = 0;
	
	//
	// Static methods
	//
	VertexBuffer* VertexBuffer::CreateVertexbuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount, ZA_SHADER_TYPE targetShader)
	{
		VertexBuffer* vBuffer = new DX::DXVertexBuffer(vertices, vertexSize, vCount, indices, indexCount, targetShader);

		s_VertexBuffers.push_back(vBuffer);

		return vBuffer;
	}
	void VertexBuffer::Delete(VertexBuffer* vertexbuffer)
	{
		Delete(vertexbuffer->getUUID());
	}
	void VertexBuffer::Delete(UUID uuid)
	{
		for (uint i = 0; i < s_VertexBuffers.size(); i++)
		{
			if (s_VertexBuffers[i]->getUUID() == uuid)
			{
				VertexBuffer* vb = s_VertexBuffers[i];
				vb->cleanup();
				s_VertexBuffers.erase(s_VertexBuffers.begin() + i);
				delete vb;
			}
		}
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
	VertexBuffer::VertexBuffer(uint vertexCount, ZA_SHADER_TYPE targetShader)
		: m_VertexCount(vertexCount),
		m_TargetShader(targetShader)
	{
		RandomUUID(&m_uuid);
	}

	uint VertexBuffer::getVertexCount(void) const
	{
		return m_VertexCount;
	}
	UUID VertexBuffer::getUUID() const
	{
		return m_uuid;
	}
}}}
