#include "VertexBuffer.h"

#include <graphics/API/DX/DXVertexBuffer.h>
#include <util/Log.h>

namespace zaap { namespace graphics { 

////////////////
// Management //
////////////////
namespace API {

	std::vector<VertexBuffer*> VertexBuffer::s_VertexBuffers;
	
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
	void VertexBuffer::Delete(const UUID&  uuid)
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

		ZA_LOG_CLEANUP();
	}
}

///////////////////////
// Rendering options //
///////////////////////
namespace API {
	uint VertexBuffer::s_TotalDrawCount = 0;
	ViewFrustum VertexBuffer::s_ViewFrustum = ViewFrustum();

	uint VertexBuffer::GetTotalDrawCount()
	{
		return s_TotalDrawCount;
	}
	void VertexBuffer::ClearTotalDrawCount()
	{
		s_TotalDrawCount = 0;
	}

	void VertexBuffer::SetViewFrustum(const ViewFrustum& view)
	{
		s_ViewFrustum = view;
	}
	ViewFrustum VertexBuffer::GetViewFrustum()
	{
		return s_ViewFrustum;
	}
}
namespace API {
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
