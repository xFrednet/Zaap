#include "DXGUIShader.h"
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {
	
	D3D11_INPUT_ELEMENT_DESC DXGUIShaderIED[]{
		{"POSITION"	, 0, DXGI_FORMAT_R32G32_FLOAT		, 0, 0						, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TYPE"		, 0, DXGI_FORMAT_R32_UINT			, 0, sizeof(float) * 2		, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TYPEINFO"	, 0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 0, sizeof(float) * 2 + 8	, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	
	void DXGUIShader::loadTransformationMatrix() const
	{
		LoadResource(m_MatrixBuffer, &m_TransformationMatrix, sizeof(Mat4));
	}

	DXGUIShader::DXGUIShader()
		: m_MatrixBuffer(nullptr)
	{
	}

	DXGUIShader::~DXGUIShader()
	{
		ZA_DXRELEASE(m_MatrixBuffer);
	}

	ZA_MULTI_RESULT DXGUIShader::init()
	{
		ZA_MULTI_RESULT results;

		results += createShaderFromString(dxDefaultShaderSrc, DXGUIShaderIED, 4);
		if (ZA_FAILED(results))
		{
			ZA_ASSERT(false);
			return results;
		}
	}

	void DXGUIShader::start() const
	{
		startDXShader();

		DXContext::GetDevContext()->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);

		loadTransformationMatrix();
	}

	void DXGUIShader::stop() const
	{
	}
}}}
