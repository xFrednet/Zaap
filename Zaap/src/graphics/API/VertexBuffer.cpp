#include "VertexBuffer.h"

#include <graphics/API/DX/DXVertexBuffer.h>
#include <util/Log.h>

namespace zaap { namespace graphics { 

////////////////
// Management //
////////////////
namespace API {

	std::vector<VertexBuffer*> VertexBuffer::s_VertexBuffers;


	VertexBuffer* VertexBuffer::CreateVertexbuffer(uint vertexSize, uint vertexCount, uint indexCount, void* vertices, uint* indices)
	{
		VertexBuffer* vBuffer = new DX::DXVertexBuffer(vertexSize, vertexCount, indexCount, vertices, indices);

		s_VertexBuffers.push_back(vBuffer);

		return vBuffer;
	}

	void VertexBuffer::Eraise(const UUID& uuid)
	{
		for (uint i = 0; i < s_VertexBuffers.size(); i++)
		{
			if (s_VertexBuffers[i]->getUUID() == uuid)
			{
				s_VertexBuffers.erase(s_VertexBuffers.begin() + i);
			}
		}
	}

	void VertexBuffer::Cleanup()
	{
		while (!s_VertexBuffers.empty())
		{
			delete s_VertexBuffers[0];
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
	VertexBuffer::VertexBuffer(const uint& vertexCount, const uint& indexCount)
		: m_IndexCount(indexCount),
		m_VertexCount(vertexCount),
		m_IsDynamic(false)
	{
		RandomUUID(&m_uuid);
	}

	VertexBuffer::~VertexBuffer()
	{
		Eraise(m_uuid);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Getters //
	/* //////////////////////////////////////////////////////////////////////////////// */
	uint VertexBuffer::getVertexCount(void) const
	{
		return m_VertexCount;
	}
	uint VertexBuffer::getIndexCount() const
	{
		return m_IndexCount;
	}
	bool VertexBuffer::isDynamic() const
	{
		return m_IsDynamic;
	}

	UUID VertexBuffer::getUUID() const
	{
		return m_uuid;
	}

}}}
