#include "DXVertexBufferCore.h"

#include <graphics/API/DX/DXContext.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {
	void LoadDXData(ID3D11Resource* target, void* data, uint size)
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		HRESULT hr = DXContext::GetDevContext()->Map(target, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, data, size);
		DXContext::GetDevContext()->Unmap(target, NULL);
	}
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructor and Destructor //
	/* //////////////////////////////////////////////////////////////////////////////// */
	DXVertexBufferCore::DXVertexBufferCore(uint vertexSize, uint vertexCount, uint indexCount, void* vertices, uint* indices)
		: VertexBufferCore(vertexCount, indexCount),
		m_VertexBuffer(nullptr),
		m_IndexBuffer(nullptr),
		m_Stride(vertexSize)
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		ID3D11Device *dev = DXContext::GetDevice();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Vertex buffer //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			D3D11_BUFFER_DESC bd;
			bd.Usage          = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth      = vertexSize * vertexCount;
			bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags      = 0;

			//create Buffer
			dev->CreateBuffer(&bd, NULL, &m_VertexBuffer);
			ZA_DXNAME(m_VertexBuffer, "DXVertexShader::m_VertexBuffer");
		}
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Index buffer //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			D3D11_BUFFER_DESC iBufferDesc;
			iBufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
			iBufferDesc.ByteWidth      = sizeof(uint) * indexCount;
			iBufferDesc.BindFlags      = D3D11_BIND_INDEX_BUFFER;
			iBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			iBufferDesc.MiscFlags      = 0;

			//create Buffer
			dev->CreateBuffer(&iBufferDesc, NULL, &m_IndexBuffer);
			ZA_DXNAME(m_IndexBuffer, "DXVertexShader::m_IndexBuffer");
		}
		ZA_ASSERT(m_VertexBuffer);
		ZA_ASSERT(m_IndexBuffer);
		m_IsDynamic = true;

		//TODO test and update this if possible
		//Fill Buffer because D3D11_SUBRESOURDE_DATA doesn't work for me.
		if (vertices)
			LoadDXData(m_VertexBuffer, vertices, vertexSize * vertexCount);
		if (indices)
			LoadDXData(m_IndexBuffer, indices, sizeof(uint) * indexCount);
	}

	DXVertexBufferCore::DXVertexBufferCore(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, uint stride, uint vertexCount, uint indexCount)
		: VertexBufferCore(vertexCount, indexCount),
		m_VertexBuffer(vertexBuffer),
		m_IndexBuffer(indexBuffer),
		m_Stride(stride)
	{
	}

	DXVertexBufferCore::~DXVertexBufferCore()
	{
		ZA_DXRELEASE(m_VertexBuffer);
		ZA_DXRELEASE(m_IndexBuffer);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Draw util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void DXVertexBufferCore::bind(uint slot)
	{
		DXContext::GetDevContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		
		UINT offset = 0;
		DXContext::GetDevContext()->IASetVertexBuffers(slot, 1, &m_VertexBuffer, &m_Stride, &offset);
	}
	void DXVertexBufferCore::unbind(uint slot)
	{
	}

	void DXVertexBufferCore::draw()
	{
		bind(0);

		DXContext::GetDevContext()->DrawIndexed(m_IndexCount, 0, 0);
	}
	void DXVertexBufferCore::draw(const uint& count)
	{
		bind(0);

		DXContext::GetDevContext()->DrawIndexed(count, 0, 0);
	}
	void DXVertexBufferCore::draw(const uint &start, const uint &count)
	{
		bind(0);

		DXContext::GetDevContext()->DrawIndexed(count, start, 0);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Getters //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ID3D11Buffer* DXVertexBufferCore::getVertexBuffer()
	{
		return m_VertexBuffer;
	}
	ID3D11Buffer const* DXVertexBufferCore::getVertexBuffer() const
	{
		return m_VertexBuffer;
	}
	ID3D11Buffer* DXVertexBufferCore::getIndexBuffer()
	{
		return m_IndexBuffer;
	}
	ID3D11Buffer const* DXVertexBufferCore::getIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Dynamic methods //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void DXVertexBufferCore::updateVertices(void* vertices, uint vertexCount)
	{
		ZA_ASSERT(vertexCount <= m_VertexCount);
		if (!m_IsDynamic || vertexCount > m_VertexCount)
			return;

		LoadDXData(m_VertexBuffer, vertices, m_Stride * vertexCount);
	}
	void DXVertexBufferCore::updateIndices(uint* indicies, uint indexCount)
	{
		ZA_ASSERT(indexCount <= m_IndexCount);
		if (!m_IsDynamic || indexCount > m_IndexCount)
			return;

		LoadDXData(m_IndexBuffer, indicies, sizeof(uint) * indexCount);
	}
}}}
