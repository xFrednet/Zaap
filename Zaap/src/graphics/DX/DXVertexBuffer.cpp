#include "DXVertexBuffer.h"

#include <graphics/API/DXContext.h>

namespace zaap { namespace graphics { namespace DX {
	
	DXVertexBuffer::DXVertexBuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount)
		: VertexBuffer(indexCount),
		m_VBuffer(nullptr),
		m_IndexBuffer(nullptr),
		m_Stride(vertexSize)
	{
		/*
		Vertex Buffer
		*/

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		ID3D11Device *dev = DXContext::GetDevice();

		//
		// VertexBuffer
		//
		{
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = vertexSize * vCount;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0;

			//create Buffer
			dev->CreateBuffer(&bd, NULL, &m_VBuffer);
			DXNAME(m_VBuffer, "DXLoader::loadVBuffer::pVBuffer")
			
			//Fill Buffer because D3D11_SUBRESOURDE_DATA doesn't work for me.
			D3D11_MAPPED_SUBRESOURCE ms;
			devcon->Map(m_VBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, vertices, vertexSize * vCount);
			devcon->Unmap(m_VBuffer, NULL);
		}
		//
		// IndexBuffer
		//
		{
			D3D11_BUFFER_DESC iBufferDesc;
			iBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			iBufferDesc.ByteWidth = sizeof(uint) * indexCount;
			iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			iBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			iBufferDesc.MiscFlags = 0;

			//create Buffer
			dev->CreateBuffer(&iBufferDesc, NULL, &m_IndexBuffer);
			DXNAME(m_IndexBuffer, "DXLoader::loadVBuffer::indexBuffer")

			//Fill Buffer because D3D11_SUBRESOURDE_DATA doesn't work for me.
			D3D11_MAPPED_SUBRESOURCE ms;
			devcon->Map(m_IndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, indices, sizeof(uint) * indexCount);
			devcon->Unmap(m_IndexBuffer, NULL);
		}
	}

	DXVertexBuffer::DXVertexBuffer(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, uint vertexCount, uint stride)
		: VertexBuffer(vertexCount),
		m_VBuffer(vertexBuffer),
		m_IndexBuffer(indexBuffer),
		m_Stride(stride)
	{

	}

	ID3D11Buffer* const* DXVertexBuffer::getVBuffer() const
	{ return &m_VBuffer; }

	ID3D11Buffer* DXVertexBuffer::getIBuffer() const
	{ return m_IndexBuffer; }

	void DXVertexBuffer::bind(uint slot)
	{
		DXContext::GetDevContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		
		UINT offset = 0;
		DXContext::GetDevContext()->IASetVertexBuffers(slot, 1, &m_VBuffer, &m_Stride, &offset);
	}

	void DXVertexBuffer::unbind(uint slot)
	{
	}

	void DXVertexBuffer::draw()
	{
		bind(0);

		DXContext::GetDevContext()->DrawIndexed(m_VertexCount, 0, 0);

		s_TotalDrawCount += m_VertexCount;
	}

	void DXVertexBuffer::cleanup()
	{
		DXRELEASE(m_VBuffer);
		DXRELEASE(m_IndexBuffer);
	}
}}}


