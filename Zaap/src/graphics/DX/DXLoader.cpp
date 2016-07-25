#include "DXLoader.h" 

#include <graphics/API/DXContext.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace DX {

	Mesh DXLoader::loadMesh(VERTEX vertices[], uint vCount, uint indexBufferData[], uint indexCount)
	{
		/*
		Vertex Buffer
		*/

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		ID3D11Device *dev = DXContext::GetDevice();

		//Buffer desc
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

		bd.Usage			= D3D11_USAGE_DYNAMIC;
		bd.ByteWidth		= sizeof(VERTEX) * vCount;
		bd.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;

		//create Buffer
		ID3D11Buffer *pVBuffer;
		dev->CreateBuffer(&bd, NULL, &pVBuffer);
		m_Buffers.push_back(pVBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, vertices, sizeof(VERTEX) * vCount);
		devcon->Unmap(pVBuffer, NULL);

		/*
		IndexBuffer
		*/
		D3D11_BUFFER_DESC iBufferDesc;
		iBufferDesc.Usage			= D3D11_USAGE_DYNAMIC;
		iBufferDesc.ByteWidth		= sizeof(uint) * indexCount;
		iBufferDesc.BindFlags		= D3D11_BIND_INDEX_BUFFER;
		iBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
		iBufferDesc.MiscFlags		= 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem			= indexBufferData;
		initData.SysMemPitch		= 0;
		initData.SysMemSlicePitch	= 0;

		//
		ID3D11Buffer *indexBuffer;
		HRESULT hr = dev->CreateBuffer(&iBufferDesc, &initData, &indexBuffer);
		m_Buffers.push_back(indexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms2;
		devcon->Map(indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms2);
		memcpy(ms2.pData, indexBufferData, sizeof(uint) * indexCount);
		devcon->Unmap(indexBuffer, NULL);

		console::Println("Loaded Mesh");

		DXVertexBuffer* vBuffer = new DX::DXVertexBuffer(pVBuffer, indexBuffer, indexCount);
		m_VertexBuffers.push_back(vBuffer);
		return Mesh(vBuffer);
	}

	void DXLoader::cleanup() const
	{
		uint i;
		for (i = 0; i < m_Buffers.size(); i++)
		{
			DXRELEASE_(m_Buffers[i]);
		}

		for (i = 0; i < m_VertexBuffers.size(); i++)
		{
			delete m_VertexBuffers[i];
		}
		ZAAP_CLEANUP_LOG("DXLoader");
	}

}}}
