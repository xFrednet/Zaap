#include "DXVertexBuffer.h"

#include <graphics/API/DXContext.h>

namespace zaap { namespace graphics { namespace DX {
	
	DXVertexBuffer::DXVertexBuffer(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, uint vertexCount)
		: VertexBuffer(vertexCount),
		m_VBuffer(vertexBuffer),
		m_IndexBuffer(indexBuffer)
	{

	}

	ID3D11Buffer* const* DXVertexBuffer::getVBuffer() const
	{ return &m_VBuffer; }

	ID3D11Buffer* DXVertexBuffer::getIBuffer() const
	{ return m_IndexBuffer; }

	void DXVertexBuffer::bind(uint slot)
	{
		DXContext::GetDevContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		DXContext::GetDevContext()->IASetVertexBuffers(0, 1, &m_VBuffer, &stride, &offset);
	}

	void DXVertexBuffer::unbind(uint slot)
	{
	}
}}}


