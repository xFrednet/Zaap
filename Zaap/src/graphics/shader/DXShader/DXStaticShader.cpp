#include "DXStaticShader.h"
#include "maths/Maths.h"
#include "graphics/API/DXContext.h"
#include <util/Console.h>

D3D11_INPUT_ELEMENT_DESC ied[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 5	, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

namespace zaap { namespace graphics { namespace DX {

	DXStaticShader::DXStaticShader(void)
		: DXShader()
	{
		if (loadShaders("DXStaticVShader.shader", "DXStaticPShader.shader", ied, 3))
		{
			ZAAP_INFO("DXStaticShader: compiled successfully");
		} else
		{
			ZAAP_ALERT("DXStaticShader: compiling failed");
			system("pause"); //TODO remove Debugcode
		}

		D3D11_BUFFER_DESC bDesc;
		bDesc.ByteWidth				= sizeof(VS_CONSTANT_BUFFER);
		bDesc.Usage					= D3D11_USAGE_DYNAMIC;
		bDesc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
		bDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
		bDesc.MiscFlags				= 0;
		bDesc.StructureByteStride	= 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem			= &m_Buffer;
		initData.SysMemPitch		= 0;
		initData.SysMemSlicePitch	= 0;

		HRESULT result = DXContext::GetDevice()->CreateBuffer(&bDesc, &initData, &m_CBuffer);

		if (FAILED(result))
			ZAAP_ERROR("DXStaticShader: Could not create cBuffer");

		DXContext::GetDevContext()->VSSetConstantBuffers(0, 1, &m_CBuffer);

	}

	//
	// Matrix loader
	//
	void DXStaticShader::loadTransformationMatrix(math::Mat4& matrix)
	{
		m_Buffer.TransformationMatrix = matrix;

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_CBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_Buffer, sizeof(VS_CONSTANT_BUFFER));
		devcon->Unmap(m_CBuffer, NULL);

		devcon = nullptr;
	}
	void DXStaticShader::loadProjectionMatrix(math::Mat4& matrix)
	{
		m_Buffer.ProjectionMatrix = matrix;

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_CBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_Buffer, sizeof(VS_CONSTANT_BUFFER));
		devcon->Unmap(m_CBuffer, NULL);

		devcon = nullptr;
	}
	void DXStaticShader::loadViewMatrix(math::Mat4& matrix)
	{
		//matrix.m41 = -1;
		m_Buffer.ViewMatrix = matrix;

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_CBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_Buffer, sizeof(VS_CONSTANT_BUFFER));
		devcon->Unmap(m_CBuffer, NULL);
	}

	void DXStaticShader::cleanup()
	{
		DXRELEASE(m_CBuffer);
		cleanDXShader();
		ZAAP_CLEANUP_LOG("DXStaticShader");
	}
}}}