#include "DXDefaultShader.h"

namespace zaap { namespace graphics { namespace DX {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Buffers //
	/* //////////////////////////////////////////////////////////////////////////////// */


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
		// TODO  DXDefaultShader::init
		return ZA_MULTI_RESULT(ZA_ERROR_API_ERROR);
	}
}}}
