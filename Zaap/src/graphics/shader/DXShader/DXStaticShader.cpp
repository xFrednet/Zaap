#include "DXStaticShader.h"

#include <maths/Maths.h>
#include <graphics/API/DXContext.h>
#include <util/Console.h>
#include <entity/BasicEntity.h>

D3D11_INPUT_ELEMENT_DESC ied[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 5	, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

namespace zaap { namespace graphics { namespace DX {

	DXStaticShader::DXStaticShader(void)
		: DXShader()
	{
		if (loadShaders("DXStaticShader.shader", "DXStaticShader.shader", ied, 3))
		{
			ZAAP_INFO("DXStaticShader: compiled successfully");
		} else
		{
			ZAAP_ALERT("DXStaticShader: compiling failed");
			system("pause"); //TODO remove Debugcode
		}

		HRESULT result;
		ID3D11Device *dev = DXContext::GetDevice();
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		//
		// Matrix Buffer
		//
		{
			D3D11_BUFFER_DESC bDesc;
			bDesc.ByteWidth				= sizeof(VS_MATRIX_BUFFER);
			bDesc.Usage					= D3D11_USAGE_DYNAMIC;
			bDesc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
			bDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags				= 0;
			bDesc.StructureByteStride	= 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem			= &m_MatrixBufferStruct;
			initData.SysMemPitch		= 0;
			initData.SysMemSlicePitch	= 0;

			result = dev->CreateBuffer(&bDesc, &initData, &m_MarixBuffer);
			DXNAME(m_MarixBuffer, "DXStaticShader::m_MarixBuffer")

			if (FAILED(result))
				ZAAP_ERROR("DXStaticShader: Could not create m_MarixBuffer");

			devcon->VSSetConstantBuffers(0, 1, &m_MarixBuffer);
		}

		//
		// Light Buffer
		//
		{
			D3D11_BUFFER_DESC bDesc;
			bDesc.ByteWidth				= sizeof(VS_LIGHT_BUFFER);
			bDesc.Usage					= D3D11_USAGE_DYNAMIC;
			bDesc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
			bDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags				= 0;
			bDesc.StructureByteStride	= 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem			= &m_LightBufferStruct;
			initData.SysMemPitch		= 0;
			initData.SysMemSlicePitch	= 0;

			result = dev->CreateBuffer(&bDesc, &initData, &m_LightBuffer);
			DXNAME(m_LightBuffer, "DXStaticShader::m_LightBuffer");

			if (FAILED(result))
				ZAAP_ERROR("DXStaticShader: Could not create m_LightBuffer");

			devcon->VSSetConstantBuffers(1, 1, &m_LightBuffer);
		}

		//
		// Lightcolor Buffer
		//
		{
			D3D11_BUFFER_DESC bDesc;
			ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));

			bDesc.ByteWidth				= sizeof(PS_LIGHTCOLOR_BUFFER);
			bDesc.Usage					= D3D11_USAGE_DYNAMIC;
			bDesc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
			bDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags				= 0;
			bDesc.StructureByteStride	= 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem			= &m_LightColorStruct;
			initData.SysMemPitch		= 0;
			initData.SysMemSlicePitch	= 0;

			dev->CreateBuffer(&bDesc, &initData, &m_LightColorBuffer);
			DXNAME(m_LightColorBuffer, "DXStaticShader::m_LightColorBuffer");

			devcon->PSSetConstantBuffers(0, 1, &m_LightColorBuffer);
		}
	}

	//
	// Matrix loader
	//
	void DXStaticShader::loadTransformationMatrix(math::Mat4& matrix)
	{
		m_MatrixBufferStruct.TransformationMatrix = matrix;

		loadMarixBuffer();
	}
	void DXStaticShader::loadProjectionMatrix(math::Mat4& matrix)
	{
		m_MatrixBufferStruct.ProjectionMatrix = matrix;

		loadMarixBuffer();
	}
	void DXStaticShader::loadViewMatrix(math::Mat4& matrix)
	{
		m_MatrixBufferStruct.ViewMatrix = matrix;

		loadMarixBuffer();
	}
	
	void DXStaticShader::loadMarixBuffer() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_MarixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixBufferStruct, sizeof(VS_MATRIX_BUFFER));
		devcon->Unmap(m_MarixBuffer, NULL);
	}

	//
	// Light loader
	//
	void DXStaticShader::loadLight(const Light* light)
	{
		//
		// Light position
		//
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		{
			m_LightBufferStruct.LightPosition = light->getPosition();

			D3D11_MAPPED_SUBRESOURCE ms;
			devcon->Map(m_LightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_LightBufferStruct, sizeof(VS_LIGHT_BUFFER));
			devcon->Unmap(m_LightBuffer, NULL);
		}
		//
		// Light color
		//
		{
			m_LightColorStruct.lightColor = light->getColor();

			D3D11_MAPPED_SUBRESOURCE ms;
			devcon->Map(m_LightColorBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_LightColorStruct, sizeof(PS_LIGHTCOLOR_BUFFER));
			devcon->Unmap(m_LightColorBuffer, NULL);
		}
	}

	void DXStaticShader::cleanup()
	{
		DXRELEASE(m_MarixBuffer);
		DXRELEASE(m_LightBuffer);
		cleanDXShader();
		ZAAP_CLEANUP_LOG("DXStaticShader");
	}
}}}