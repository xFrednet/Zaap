#include "DXTerrainShader.h"

#include <graphics/API/DXContext.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace DX {
	
	D3D11_INPUT_ELEMENT_DESC terrainShader_IED[] {
		{"POSITION"		, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"		, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXMAPCOLOR"	, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 6	, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD"		, 0, DXGI_FORMAT_R32G32_FLOAT		, 0, sizeof(float) * 9	, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	void DXTerrainShader::loadMatrixBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		DXContext::GetDevContext()->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixStruct, sizeof(VS_MATRIX_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MatrixBuffer, NULL);
	}

	void DXTerrainShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		//VSLightBuffer
		devcon->Map(m_VSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_VSLightStruct, sizeof(VS_LIGHT_BUFFER));
		devcon->Unmap(m_VSLightBuffer, NULL);

		//PSLightBuffer
		devcon->Map(m_PSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_PSLightStruct, sizeof(PS_LIGHT_BUFFER));
		devcon->Unmap(m_PSLightBuffer, NULL);
	}

	DXTerrainShader::DXTerrainShader()
	{
		if (loadShaders("DXTerrainShader.shader", "DXTerrainShader.shader", terrainShader_IED, 4))
		{
			ZAAP_INFO("DXTerrainShader: compiled successfully");
		} else
		{
			ZAAP_ALERT("DXTerrainShader: compiling failed");
			system("pause"); //TODO remove Debugcode
		}
		
		//
		// Matrix Buffer
		//
		if (CreateConstBuffer(m_MatrixBuffer, sizeof(VS_MATRIX_BUFFER), &m_MatrixStruct))
		{
			DXNAME(m_MatrixBuffer, "DXTerrainShader::m_MatrixBuffer");
		} else
		{
			ZAAP_ERROR("DXTerrainShader: could not create m_MatrixBuffer");
		}

		//
		// VSLightBuffer
		//
		if (CreateConstBuffer(m_VSLightBuffer, sizeof(VS_LIGHT_BUFFER), &m_VSLightStruct))
		{
			DXNAME(m_VSLightBuffer, "DXTerrainShader::m_VSLightStruct");
		} else
		{
			ZAAP_ERROR("DXTerrainShader: could not create m_VSLightStruct");
		}

		//
		// PSLightBuffer
		//
		if (CreateConstBuffer(m_PSLightBuffer, sizeof(PS_LIGHT_BUFFER), &m_PSLightBuffer))
		{
			DXNAME(m_PSLightBuffer, "DXTerrainShader::m_PSLightBuffer");
		} else
		{
			ZAAP_ERROR("DXTerrainShader: could not create m_PSLightBuffer");
		}
	}

	//
	// Matrix Loader
	//
	void DXTerrainShader::loadTransformationMatrix(math::Mat4 matrix)
	{
		m_MatrixStruct.TransformationMatrix = matrix;
		loadMatrixBuffer();
	}
	void DXTerrainShader::loadProjectionMatrix(math::Mat4 matrix)
	{
		m_MatrixStruct.ProjectionMatrix = matrix;
		loadMatrixBuffer();
	}
	void DXTerrainShader::loadViewMatrix(math::Mat4 matrix)
	{
		m_MatrixStruct.ViewMatrix = matrix;
		loadMatrixBuffer();
	}

	//
	//LightSetup loader
	//
	void DXTerrainShader::loadLightSetup(const LightSetup const *lightSetup)
	{
		uint count = lightSetup->getSize();
		if (count > SUPPORTET_LIGHT_COUNT)
		{
			ZAAP_ALERT("DXTerrainShader: The submitted LightSetup has to many lights. " + std::to_string(count) + "/" + std::to_string(SUPPORTET_LIGHT_COUNT));
			count = SUPPORTET_LIGHT_COUNT;
		}

		m_VSLightStruct.LightCount = count;
		m_PSLightStruct.LightCount = count;

		Light const *light;
		for (uint i = 0; i < count; i++)
		{
			light = lightSetup->getConstLight((int)i);
			m_VSLightStruct.Position[i] = light->getPosition();
			m_PSLightStruct.LightColor[i] = light->getColor();
		}

		loadLightBuffers();
	}

	void DXTerrainShader::start() const
	{
		DXShader::start();

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		devcon->VSSetConstantBuffers(1, 1, &m_VSLightBuffer);

		devcon->PSSetConstantBuffers(0, 1, &m_PSLightBuffer);

		loadMatrixBuffer();
		loadLightBuffers();
	}

	void DXTerrainShader::cleanup()
	{
		DXRELEASE(m_MatrixBuffer);
		DXRELEASE(m_VSLightBuffer);
		DXRELEASE(m_PSLightBuffer);
		
		cleanDXShader();

		ZAAP_CLEANUP_LOG("DXTerrainShader");
	}
}}}
