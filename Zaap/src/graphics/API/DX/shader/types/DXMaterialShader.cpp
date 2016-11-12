#include "DXMaterialShader.h"
#include <util/Console.h>


namespace zaap { namespace graphics { namespace DX {
	D3D11_INPUT_ELEMENT_DESC ied[] {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0                , D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"MATERIAL", 0, DXGI_FORMAT_R32_UINT       , 0, sizeof(float) * 6, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	String DXMaterialShaderSrc =
#include <graphics/API/DX/shader/types/DXMaterialShader.shader>
		;

	DXMaterialShader::DXMaterialShader()
	{
		if (createShaderFromString(DXMaterialShaderSrc, ied, 3))
		{
			ZAAP_INFO("compiled successfully");
		} else
		{
			ZAAP_ERROR("compile error");
			system("pause"); // TODO remove debug code
		}

		//
		// Matrix buffer
		//
		{
			if (CreateConstBuffer(m_MatrixBuffer, sizeof(ZA_VS_MATRIX_BUFFER), &m_MatrixBufferStruct))
			{
				DXNAME(m_MatrixBuffer, "DXMaterialShader::m_MatrixBuffer");
			} else
			{
				ZAAP_ERROR("failed to create the m_MatrixBuffer");
			}
		}

		//
		// Scene Buffer
		//
		{
			if (CreateConstBuffer(m_SceneBuffer, sizeof(ZA_VS_SCENE_BUFFER), &m_SceneBufferStruct))
			{
				DXNAME(m_SceneBuffer, "DXMaterialShader::m_SceneBuffer");
			} else
			{
				ZAAP_ERROR("failed to create the m_SceneBuffer");
			}
		}

		//
		// LightPosition buffer
		//
		{
			if (CreateConstBuffer(m_VSLightBuffer, sizeof(ZA_VS_LIGHT_BUFFER), &m_VSLightBufferStruct))
			{
				DXNAME(m_VSLightBuffer, "DXMaterialShader::m_LightPositionBuffer");
			} else
			{
				ZAAP_ERROR("failed to create the m_LightPositionBuffer");
			}
		}

		//
		// LightColor buffer
		//
		{
			if (CreateConstBuffer(m_PSLightBuffer, sizeof(ZA_PS_LIGHT_BUFFER), &m_PSLightBufferStruct))
			{
				DXNAME(m_PSLightBuffer, "DXMaterialShader::m_LightColorBuffer");
			}else
			{
				ZAAP_ERROR("failed to create the m_LightColorBuffer");
			}
		}

		//
		// Material buffer
		//
		{
			if (CreateConstBuffer(m_MaterialBuffer, sizeof(ZA_PS_MATERIAL_BUFFER), &m_MaterialBufferStruct))
			{
				DXNAME(m_MaterialBuffer, "DXMaterialShader::m_MaterialBuffer");
			} else {
				ZAAP_ERROR("failed to create the m_MaterialBuffer");
			}
		}

	}

	//
	// Matrix Buffer
	//
	void DXMaterialShader::loadMatrixBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;

		DXContext::GetDevContext()->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixBufferStruct, sizeof(ZA_VS_MATRIX_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MatrixBuffer, NULL);
	}

	//
	// Scene Buffer
	//
	void DXMaterialShader::loadSceneBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;

		DXContext::GetDevContext()->Map(m_SceneBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_SceneBufferStruct, sizeof(ZA_VS_SCENE_BUFFER));
		DXContext::GetDevContext()->Unmap(m_SceneBuffer, NULL);
	}

	//
	// Light buffer
	//
	void DXMaterialShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		//PS Light buffer
		{
			devcon->Map(m_VSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_VSLightBufferStruct, sizeof(ZA_VS_LIGHT_BUFFER));
			devcon->Unmap(m_VSLightBuffer, NULL);
		}

		//VS Light buffer
		{
			devcon->Map(m_PSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_PSLightBufferStruct, sizeof(ZA_PS_LIGHT_BUFFER));
			devcon->Unmap(m_PSLightBuffer, NULL);
		}
	}

	//
	// Material buffer
	//
	void DXMaterialShader::loadMaterialBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		DXContext::GetDevContext()->Map(m_MaterialBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MaterialBufferStruct, sizeof(ZA_PS_MATERIAL_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MaterialBuffer, NULL);
	}

	//
	// Util
	//
	void DXMaterialShader::start() const
	{
		startDXShader();

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		devcon->VSSetConstantBuffers(1, 1, &m_VSLightBuffer);
		devcon->VSSetConstantBuffers(2, 1, &m_SceneBuffer);

		devcon->PSSetConstantBuffers(0, 1, &m_PSLightBuffer);
		devcon->PSSetConstantBuffers(1, 1, &m_MaterialBuffer);

		loadMatrixBuffer();
		loadSceneBuffer();
		loadLightBuffers();
		loadMaterialBuffer();
	}
	void DXMaterialShader::stop() const
	{
	}
	void DXMaterialShader::cleanup()
	{

		//Vertex shader buffer
		DXRELEASE(m_MatrixBuffer);
		DXRELEASE(m_VSLightBuffer);
		DXRELEASE(m_SceneBuffer);

		//Pixel shader buffer
		DXRELEASE(m_PSLightBuffer);
		DXRELEASE(m_MaterialBuffer);
		
		cleanDXShader();

		ZAAP_CLEANUP_LOG("DXMaterialShader");
	}
}}}