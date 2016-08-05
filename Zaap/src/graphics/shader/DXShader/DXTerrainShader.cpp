#include "DXTerrainShader.h"

#include <graphics/API/DXContext.h>

namespace zaap { namespace graphics { namespace DX {
	
	D3D11_INPUT_ELEMENT_DESC terrainShader_IED[] {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 6	, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	void DXTerrainShader::loadMatrixBuffer()
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		DXContext::GetDevContext()->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixStruct, sizeof(VS_MATRIX_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MatrixBuffer, NULL);
	}

	void DXTerrainShader::loadLightBuffers()
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
		if (loadShaders("DXTerrainShader.shader", "DXTerrainShader.shader", terrainShader_IED, 3))
		{
			
		}
	}

	//
	// Matrix Loader
	//
	void DXTerrainShader::loadTransformationMatrix(math::Mat4 matrix)
	{
	}
	void DXTerrainShader::loadProjectionMatrix(math::Mat4 matrix)
	{
	}
	void DXTerrainShader::loadViewMatrix(math::Mat4 matrix)
	{
	}

	void DXTerrainShader::loadLightSetup(const LightSetup* lightSetup)
	{
	}

	void DXTerrainShader::start() const
	{
	}

	void DXTerrainShader::cleanup()
	{
	}
}}}
