#include "DXVertexBuffer.h"

#include <graphics/API/DXContext.h>

namespace zaap { namespace graphics { namespace DX {
	
	DXVertexBuffer::DXVertexBuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount)
		: VertexBuffer(indexCount)
	{
		/*
		Vertex Buffer
		*/

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		ID3D11Device *dev = DXContext::GetDevice();

		//Buffer desc
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = vertexSize * vCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		//create Buffer
		ID3D11Buffer *pVBuffer;
		dev->CreateBuffer(&bd, NULL, &pVBuffer);
		DXNAME(pVBuffer, "DXLoader::loadVBuffer::pVBuffer")

			D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, vertices, vertexSize * vCount);
		devcon->Unmap(pVBuffer, NULL);

		/*
		IndexBuffer
		*/
		D3D11_BUFFER_DESC iBufferDesc;
		iBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		iBufferDesc.ByteWidth = sizeof(uint) * indexCount;
		iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		iBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		iBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = indices;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		//
		ID3D11Buffer *indexBuffer;
		dev->CreateBuffer(&iBufferDesc, &initData, &indexBuffer);
		DXNAME(pVBuffer, "DXLoader::loadVBuffer::indexBuffer")

		D3D11_MAPPED_SUBRESOURCE ms2;
		devcon->Map(indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms2);
		memcpy(ms2.pData, indices, sizeof(uint) * indexCount);
		devcon->Unmap(indexBuffer, NULL);

		m_VBuffer = pVBuffer;
		m_IndexBuffer = indexBuffer;
		m_Stride = vertexSize;
		
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
		DXContext::GetDevContext()->IASetVertexBuffers(0, 1, &m_VBuffer, &m_Stride, &offset);
	}

	void DXVertexBuffer::unbind(uint slot)
	{
	}

	void DXVertexBuffer::cleanup()
	{
		DXRELEASE(m_VBuffer);
		DXRELEASE(m_IndexBuffer);
	}
}}}


