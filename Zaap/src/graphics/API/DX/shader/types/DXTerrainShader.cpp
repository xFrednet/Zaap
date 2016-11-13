#include "DXTerrainShader.h"

#include <graphics/API/DX/DXContext.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace DX {
	
	D3D11_INPUT_ELEMENT_DESC DXTerrinShaderIED[] {
		{"POSITION"		, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"		, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXMAPCOLOR"	, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 6	, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD"		, 0, DXGI_FORMAT_R32G32_FLOAT		, 0, sizeof(float) * 9	, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	//This gives in error while the file is open in Visual Studio 
	//but it works fine when it gets compiled. 
	String terrainShaderSrc =
#include <graphics/API/DX/shader/types/DXTerrainShader.shader>
		;


	void DXTerrainShader::loadMatrixBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		DXContext::GetDevContext()->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixBufferStruct, sizeof(ZA_VS_MATRIX_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MatrixBuffer, NULL);
	}
	void DXTerrainShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		//VSLightBuffer
		devcon->Map(m_VSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_VSLightBufferStruct, sizeof(ZA_VS_LIGHT_BUFFER));
		devcon->Unmap(m_VSLightBuffer, NULL);

		//PSLightBuffer
		devcon->Map(m_PSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_PSLightBufferStruct, sizeof(ZA_PS_LIGHT_BUFFER));
		devcon->Unmap(m_PSLightBuffer, NULL);
	}

	DXTerrainShader::DXTerrainShader()
	{
		if (createShaderFromString(terrainShaderSrc, DXTerrinShaderIED, 4))
		{
			ZAAP_INFO("compiled successfully");
		} else
		{
			ZAAP_ALERT("compiling failed");
			system("pause"); //TODO remove Debugcode
		}
		
		//
		// Matrix Buffer
		//
		if (CreateConstBuffer(m_MatrixBuffer, sizeof(ZA_VS_MATRIX_BUFFER), &m_MatrixBufferStruct))
		{
			ZAAP_DXNAME(m_MatrixBuffer, "DXTerrainShader::m_MatrixBuffer");
		} else
		{
			ZAAP_ERROR("could not create m_MatrixBuffer");
		}

		//
		// VSLightBuffer
		//
		if (CreateConstBuffer(m_VSLightBuffer, sizeof(ZA_VS_LIGHT_BUFFER), &m_VSLightBufferStruct))
		{
			ZAAP_DXNAME(m_VSLightBuffer, "DXTerrainShader::m_VSLightStruct");
		} else
		{
			ZAAP_ERROR("could not create m_VSLightStruct");
		}

		//
		// PSLightBuffer
		//
		if (CreateConstBuffer(m_PSLightBuffer, sizeof(ZA_PS_LIGHT_BUFFER), &m_PSLightBuffer))
		{
			ZAAP_DXNAME(m_PSLightBuffer, "DXTerrainShader::m_PSLightBuffer");
		} else
		{
			ZAAP_ERROR("could not create m_PSLightBuffer");
		}
	}

	void DXTerrainShader::start() const
	{
		startDXShader();

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		devcon->VSSetConstantBuffers(1, 1, &m_VSLightBuffer);

		devcon->PSSetConstantBuffers(0, 1, &m_PSLightBuffer);

		loadMatrixBuffer();
		loadLightBuffers();
	}
	void DXTerrainShader::stop() const
	{
	}

	void DXTerrainShader::cleanup()
	{
		ZAAP_DXRELEASE(m_MatrixBuffer);
		ZAAP_DXRELEASE(m_VSLightBuffer);
		ZAAP_DXRELEASE(m_PSLightBuffer);
		
		cleanDXShader();

		ZAAP_CLEANUP_INFO();
	}
}}}
