#include "DXFontShader2D.h"
#include <util/Console.h>
#include <graphics/API/DX/DXContext.h>


namespace zaap { namespace graphics { namespace DX {
	D3D11_INPUT_ELEMENT_DESC DXFontShaderIED[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	String DXFontShader2DSrc =
#include <graphics/API/DX/shader/types/DXFontShader2D.shader>
		;

	DXFontShader2D::DXFontShader2D()
		: DXShader()
	{
		if (createShaderFromString(DXFontShader2DSrc, DXFontShaderIED, 2))
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
			if (CreateConstBuffer(m_MatrixBuffer, sizeof(Mat4), &m_TransformationMatrix))
			{
				ZAAP_DXNAME(m_MatrixBuffer, "DXFontShader2D::m_MatrixBuffer");
			} else
			{
				ZAAP_ERROR("Could not create m_MatrixBuffer");
			}
		}

		//
		// Color Buffer
		//
		{
			if (CreateConstBuffer(m_ColorBuffer, sizeof(Color), &m_TextColor))
			{
				ZAAP_DXNAME(m_ColorBuffer, "DXFontShader2D::m_ColorBuffer");
			} else
			{
				ZAAP_ERROR("Could not create m_ColorBuffer");
			}
		}
	}

	//
	// Buffer loader 
	//
	void DXFontShader2D::loadMatrixBuffer() const
	{
		if (!m_MatrixBuffer) return;
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_TransformationMatrix, sizeof(Mat4));
		devcon->Unmap(m_MatrixBuffer, NULL);
	}
	void DXFontShader2D::loadTextColor() const
	{
		if (!m_ColorBuffer) return;
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_ColorBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_TextColor, sizeof(Color));
		devcon->Unmap(m_ColorBuffer, NULL);
	}


	void DXFontShader2D::cleanup()
	{
		ZAAP_DXRELEASE(m_MatrixBuffer);
		ZAAP_DXRELEASE(m_ColorBuffer);
		
		cleanDXShader();

		ZAAP_CLEANUP_INFO();
	}

	void DXFontShader2D::start() const
	{
		startDXShader();

		ID3D11DeviceContext* devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		
		devcon->PSSetConstantBuffers(0, 1, &m_ColorBuffer);

		loadMatrixBuffer();
		loadTextColor();
	}

	void DXFontShader2D::stop() const
	{
		stopDXShader();
	}
}}}
