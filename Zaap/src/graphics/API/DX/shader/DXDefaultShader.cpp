#include "DXDefaultShader.h"
#include <util/Console.h>

namespace zaap { namespace graphics { namespace DX {
	
	D3D11_INPUT_ELEMENT_DESC DXDefaultShaderIED[]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 6	, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "MATERIAL", 0, DXGI_FORMAT_R32_UINT		, 0, sizeof(float) * 8	, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//I like errors so I left it in... No not really!
	//This works fine during compilation
	String dxDefaultShaderSrc=
#include "DXDefaultShader.shader"
		;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Buffers //
	/* //////////////////////////////////////////////////////////////////////////////// */

	void DXDefaultShader::loadMatrixBuffer()
	{
		LoadResource(m_MatrixBuffer, &m_MatrixBufferStruct, sizeof(ZA_VS_MATRIX_BUFFER));
	}

	void DXDefaultShader::loadSceneBuffer()
	{
		LoadResource(m_SceneBuffer, &m_SceneBufferStruct, sizeof(ZA_VS_SCENE_BUFFER));
	}

	void DXDefaultShader::loadLightBuffers()
	{
		LoadResource(m_VSLightBuffer, &m_VSLightBufferStruct, sizeof(ZA_VS_LIGHT_BUFFER));
		LoadResource(m_PSLightBuffer, &m_PSLightBufferStruct, sizeof(ZA_PS_LIGHT_BUFFER));
	}

	void DXDefaultShader::loadMaterialBuffer()
	{
		LoadResource(m_MaterialBuffer, &m_MaterialBufferStruct, sizeof(ZA_PS_MATERIAL_BUFFER));
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Initialization //
	/* //////////////////////////////////////////////////////////////////////////////// */


	DXDefaultShader::DXDefaultShader()
		: DefaultShader(),
		DXShader(),
		m_MatrixBuffer(nullptr),
		m_SceneBuffer(nullptr),
		m_VSLightBuffer(nullptr),
		m_PSLightBuffer(nullptr),
		m_MaterialBuffer(nullptr)
	{
	}

	DXDefaultShader::~DXDefaultShader()
	{
		ZAAP_DXRELEASE(m_MatrixBuffer);
		ZAAP_DXRELEASE(m_SceneBuffer);
		ZAAP_DXRELEASE(m_VSLightBuffer);
		ZAAP_DXRELEASE(m_PSLightBuffer);
		ZAAP_DXRELEASE(m_MaterialBuffer);
	}

	ZA_MULTI_RESULT DXDefaultShader::init()
	{
		ZA_MULTI_RESULT results;

		results += createShaderFromString(dxDefaultShaderSrc, DXDefaultShaderIED, 4);
		if (ZA_FAILED(results))
		{
			system("pause"); //TODO remove Debug code
			return results;
		}

		/* ##################################### */
		// # Matrix buffer #
		/* ##################################### */
		results += CreateConstBuffer(&m_MatrixBuffer, sizeof(ZA_VS_MATRIX_BUFFER), &m_MatrixBufferStruct);
		if (ZA_FAILED(results))
			return results;

		/* ##################################### */
		// # Scene buffer #
		/* ##################################### */
		results += CreateConstBuffer(&m_SceneBuffer, sizeof(ZA_VS_SCENE_BUFFER), &m_SceneBufferStruct);
		if (ZA_FAILED(results))
			return results;

		/* ##################################### */
		// # Light buffers #
		/* ##################################### */
		results += CreateConstBuffer(&m_VSLightBuffer, sizeof(ZA_VS_LIGHT_BUFFER), &m_VSLightBufferStruct);
		if (ZA_FAILED(results))
			return results;

		results += CreateConstBuffer(&m_PSLightBuffer, sizeof(ZA_PS_LIGHT_BUFFER), &m_PSLightBufferStruct);
		if (ZA_FAILED(results))
			return results;

		/* ##################################### */
		// # Material buffer #
		/* ##################################### */
		results += CreateConstBuffer(&m_MaterialBuffer, sizeof(ZA_PS_MATERIAL_BUFFER), &m_MaterialBufferStruct);
		if (ZA_FAILED(results))
			return results;

		ZAAP_INFO("init finished successfully! :D");

		return results;
	}
}}}
