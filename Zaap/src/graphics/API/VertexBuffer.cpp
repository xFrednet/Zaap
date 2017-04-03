#include "VertexBuffer.h"

#include <graphics/API/DX/DXVertexBufferCore.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace API {

	uint VertexBufferCore::s_TotalDrawCount = 0;
	ViewFrustum VertexBufferCore::s_ViewFrustum = ViewFrustum();

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Creation //
	/* //////////////////////////////////////////////////////////////////////////////// */
	VertexBufferCore* VertexBufferCore::CreateVertexBufferCore(uint vertexSize, const uint& vertexCount, const uint& indexCount, void* vertices, uint* indices)
	{
		return new DX::DXVertexBufferCore(vertexSize, vertexCount, indexCount, vertices, indices);
	}
	VertexBuffer VertexBufferCore::CreateVertexBuffer(uint vertexSize, const uint& vertexCount, const uint& indexCount, void* vertices, uint* indices)
	{
		return VertexBuffer(CreateVertexBufferCore(vertexSize, vertexCount, indexCount, vertices, indices));
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Rendering Info //
	/* //////////////////////////////////////////////////////////////////////////////// */
	uint VertexBufferCore::GetTotalDrawCount()
	{
		return s_TotalDrawCount;
	}
	void VertexBufferCore::ClearTotalDrawCount()
	{
		s_TotalDrawCount = 0;
	}

	void VertexBufferCore::SetViewFrustum(const ViewFrustum& view)
	{
		s_ViewFrustum = view;
	}
	ViewFrustum VertexBufferCore::GetViewFrustum()
	{
		return s_ViewFrustum;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Class //
	/* //////////////////////////////////////////////////////////////////////////////// */
	VertexBufferCore::VertexBufferCore(const uint& vertexCount, const uint& indexCount)
		: m_IndexCount(indexCount),
		m_VertexCount(vertexCount),
		m_IsDynamic(false)
	{
		RandomUUID(&m_UUID);
	}

}}}
