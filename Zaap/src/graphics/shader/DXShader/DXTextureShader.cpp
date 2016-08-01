#include "DXTextureShader.h"

#include <maths/Maths.h>
#include <graphics/API/DXContext.h>
#include <util/Console.h>
#include <entity/BasicEntity.h>

D3D11_INPUT_ELEMENT_DESC ied2[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, 0					, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, sizeof(float) * 3	, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(float) * 6	, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

namespace zaap { namespace graphics { namespace DX {

	DXTextureShader::DXTextureShader()
		: DXShader()
	{
		if (loadShaders("DXTextureShader.shader", "DXTextureShader.shader", ied2, 3))
		{
			ZAAP_INFO("DXTextureShader: compiled successfully");
		} else
		{
			ZAAP_ALERT("DXTextureShader: compiling failed");
			system("pause"); //TODO remove Debugcode
		}

		//
		// Matrix Buffer
		//
		{
			if (CreateConstBuffer(m_MatrixBuffer, sizeof(VS_MATRIX_BUFFER), &m_MatrixBufferStruct))
			{
				DXNAME(m_MatrixBuffer, "DXTextureShader::m_MatrixBuffer")
			} else
			{
				ZAAP_ERROR("DXTextureShader: Could not create m_MarixBuffer");
			}
		}

		//
		// Light Buffer
		//
		{
			if (CreateConstBuffer(m_LightBuffer, sizeof(VS_LIGHT_BUFFER), &m_LightBufferStruct))
			{
				DXNAME(m_LightBuffer, "DXTextureShader::m_LightBuffer");
			} else
			{
				ZAAP_ERROR("DXTextureShader: Could not create m_LightBuffer");
			}
		}

		//
		// Lightcolor Buffer
		//
		{
			if (CreateConstBuffer(m_LightColorBuffer, sizeof(PS_LIGHTCOLOR_BUFFER), &m_LightColorStruct))
			{
				DXNAME(m_LightColorBuffer, "DXTextureShader::m_LightColorBuffer");
			} else
			{
				ZAAP_ERROR("DXTextureShader: Could not create m_LightColorBuffer");
			}

		}
	}

	//
	// Matrix loader
	//
	void DXTextureShader::loadTransformationMatrix(math::Mat4& matrix)
	{
		m_MatrixBufferStruct.TransformationMatrix = matrix;

		loadMarixBuffer();
	}
	void DXTextureShader::loadProjectionMatrix(math::Mat4& matrix)
	{
		m_MatrixBufferStruct.ProjectionMatrix = matrix;

		loadMarixBuffer();
	}
	void DXTextureShader::loadViewMatrix(math::Mat4& matrix)
	{
		m_MatrixBufferStruct.ViewMatrix = matrix;

		loadMarixBuffer();
	}
	
	void DXTextureShader::loadMarixBuffer() const
	{
		if (!m_MatrixBuffer) return;
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		devcon->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixBufferStruct, sizeof(VS_MATRIX_BUFFER));
		devcon->Unmap(m_MatrixBuffer, NULL);
	}

	//
	// Light loader
	//
	void DXTextureShader::loadLight(const Light* light)
	{
		m_LightBufferStruct.LightPosition = light->getPosition();
		m_LightColorStruct.lightColor = light->getColor();
		
		loadLightBuffers();
	}
	void DXTextureShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;
		{
			devcon->Map(m_LightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_LightBufferStruct, sizeof(VS_LIGHT_BUFFER));
			devcon->Unmap(m_LightBuffer, NULL);
		}
		//
		// Light color
		//
		{
			devcon->Map(m_LightColorBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_LightColorStruct, sizeof(PS_LIGHTCOLOR_BUFFER));
			devcon->Unmap(m_LightColorBuffer, NULL);
		}
	}

	void DXTextureShader::start() const
	{
		DXShader::start();

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		devcon->VSSetConstantBuffers(1, 1, &m_LightBuffer);
		devcon->PSSetConstantBuffers(0, 1, &m_LightColorBuffer);

		loadMarixBuffer();
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