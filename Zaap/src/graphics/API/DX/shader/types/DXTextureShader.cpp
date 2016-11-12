#include "DXTextureShader.h"

#include <graphics/API/DX/DXContext.h>
#include <util/Console.h>


namespace zaap { namespace graphics { namespace DX {
	D3D11_INPUT_ELEMENT_DESC DXTextureShaderIED[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 6	, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	String DXTerrainShaderSrc = 
#include <graphics/API/DX/shader/types/DXTextureShader.shader>
		;

	DXTextureShader::DXTextureShader()
		: DXShader()
	{
		if (createShaderFromString(DXTerrainShaderSrc, DXTextureShaderIED, 3))
		{
			ZAAP_INFO("compiled successfully");
		} else
		{
			ZAAP_ALERT("compiling failed");
			system("pause"); //TODO remove DebugCode
		}

		//
		// Matrix Buffer
		//
		{
			if (CreateConstBuffer(m_MatrixBuffer, sizeof(ZA_VS_MATRIX_BUFFER), &m_MatrixBufferStruct))
			{
				DXNAME(m_MatrixBuffer, "DXTextureShader::m_MatrixBuffer");
			} else
			{
				ZAAP_ERROR("Could not create m_MarixBuffer");
			}
		}

		//
		// VS Light Buffer
		//
		{
			if (CreateConstBuffer(m_LightBuffer, sizeof(ZA_VS_LIGHT_BUFFER), &m_VSLightBufferStruct))
			{
				DXNAME(m_LightBuffer, "DXTextureShader::m_LightBuffer");
			} else
			{
				ZAAP_ERROR("Could not create m_LightBuffer");
			}
		}

		//
		// PS Light Buffer
		//
		{
			if (CreateConstBuffer(m_LightColorBuffer, sizeof(ZA_PS_LIGHT_BUFFER), &m_PSLightBufferStruct))
			{
				DXNAME(m_LightColorBuffer, "DXTextureShader::m_LightColorBuffer");
			} else
			{
				ZAAP_ERROR("Could not create m_LightColorBuffer");
			}

		}
	}

	void DXTextureShader::stop() const
	{
	}

	//
	// Matrix loader
	//
	void DXTextureShader::loadMatrixBuffer() const
	{
		if (!m_MatrixBuffer) return;
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixBufferStruct, sizeof(ZA_VS_MATRIX_BUFFER));
		devcon->Unmap(m_MatrixBuffer, NULL);
	}

	//
	// Light loader
	//
	void DXTextureShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;
		
		//
		// VS Light buffer
		//
		{
			devcon->Map(m_LightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_VSLightBufferStruct, sizeof(ZA_VS_LIGHT_BUFFER));
			devcon->Unmap(m_LightBuffer, NULL);
		}
		//
		// PS Light buffer
		//
		{
			devcon->Map(m_LightColorBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_PSLightBufferStruct, sizeof(ZA_PS_LIGHT_BUFFER));
			devcon->Unmap(m_LightColorBuffer, NULL);
		}
	}

	void DXTextureShader::start() const
	{
		startDXShader();

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		devcon->VSSetConstantBuffers(1, 1, &m_LightBuffer);

		devcon->PSSetConstantBuffers(0, 1, &m_LightColorBuffer);

		loadMatrixBuffer();
		loadLightBuffers();
	}

	void DXTextureShader::cleanup()
	{
		DXRELEASE(m_MatrixBuffer);
		DXRELEASE(m_LightBuffer);
		DXRELEASE(m_LightColorBuffer);
		
		cleanDXShader();

		ZAAP_CLEANUP_LOG("DXTextureShader");
	}
}}}