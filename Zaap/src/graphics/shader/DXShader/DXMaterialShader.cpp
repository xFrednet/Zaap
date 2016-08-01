#include "DXMaterialShader.h"
#include <util/Console.h>

D3D11_INPUT_ELEMENT_DESC ied[] {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0                , D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"MATERIAL", 0, DXGI_FORMAT_R32_UINT       , 0, sizeof(float) * 6, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

namespace zaap { namespace graphics { namespace DX {

	DXMaterialShader::DXMaterialShader()
	{
		if (loadShaders("DXMaterialShader.shader", "DXMaterialShader.shader", ied, 3))
		{
			ZAAP_INFO("DXMaterialShader: compiled successfully");
		} else
		{
			ZAAP_ERROR("DXMaterialShader: compile error");
			system("pause"); // TODO remove debug code
		}

		//
		// Matrix buffer
		//
		{
			if (CreateConstBuffer(m_MatrixBuffer, sizeof(VS_MATRIX_BUFFER), &m_MatrixStruct))
			{
				DXNAME(m_MaterialBuffer, "DXMaterialShader::m_MatrixBuffer");
			} else
			{
				ZAAP_ERROR("DXMaterialShader: failed to create the m_MatrixBuffer");
			}
		}

		//
		// LightPosition buffer
		//
		{
			if (CreateConstBuffer(m_LightPositionBuffer, sizeof(VS_LIGHTPOSITION_BUFFER), &m_LightPositionStruct))
			{
				DXNAME(m_LightPositionBuffer, "DXMaterialShader::m_LightPositionBuffer");
			} else
			{
				ZAAP_ERROR("DXMaterialShader: failed to create the m_LightPositionBuffer");
			}
		}

		//
		// LightColor buffer
		//
		{
			if (CreateConstBuffer(m_LightColorBuffer, sizeof(PS_LIGHTCOLOR_BUFFER), &m_LightColorStruct))
			{
				DXNAME(m_LightColorBuffer, "DXMaterialShader::m_LightColorBuffer");
			}else
			{
				ZAAP_ERROR("DXMaterialShader: failed to create the m_LightColorBuffer");
			}
		}

		//
		// Material buffer
		//
		{
			if (CreateConstBuffer(m_MaterialBuffer, sizeof(PS_MATERIAL_BUFFER), &m_MaterialStruct))
			{
				DXNAME(m_MaterialBuffer, "DXMaterialShader::m_MaterialBuffer");
			} else {
				ZAAP_ERROR("DXMaterialShader: failed to create the m_MaterialBuffer");
			}
		}

	}

	//
	// Matrix buffer
	//
	void DXMaterialShader::loadTransformationMatrix(math::Mat4& matrix)
	{
		m_MatrixStruct.TransformationMatrix = matrix;

		loadMatrixBuffer();
	}
	void DXMaterialShader::loadProjectionMatrix(math::Mat4& matrix)
	{
		m_MatrixStruct.ProjectionMatrix = matrix;

		loadMatrixBuffer();
	}
	void DXMaterialShader::loadViewMatrix(math::Mat4& matrix)
	{
		m_MatrixStruct.ViewMatrix = matrix;

		loadMatrixBuffer();
	}

	void DXMaterialShader::loadMatrixBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;

		DXContext::GetDevContext()->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixBuffer, sizeof(VS_MATRIX_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MatrixBuffer, NULL);
	}

	//
	// Light buffer
	//
	void DXMaterialShader::loadLight(const Light* light)
	{
		m_LightPositionStruct.Position = math::Vec4(light->getPosition());
		m_LightColorStruct.lightColor = light->getColor();

		loadLightBuffers();
	}
	void DXMaterialShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		//Light position
		{
			devcon->Map(m_LightPositionBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_LightPositionStruct, sizeof(VS_LIGHTPOSITION_BUFFER));
			devcon->Unmap(m_LightPositionBuffer, NULL);
		}

		//Light color
		{
			devcon->Map(m_LightColorBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_LightColorStruct, sizeof(PS_LIGHTCOLOR_BUFFER));
			devcon->Unmap(m_LightColorBuffer, NULL);
		}
	}

	//
	// Material buffer
	//
	void DXMaterialShader::loadMaterials(Material materials[], uint count)
	{
		if (count > MAX_MATERIAL_COUNT)
		{
			ZAAP_ALERT("DXMaterialShader: Too many materials! This shader only supports " + std::to_string(MAX_MATERIAL_COUNT) + " materials");
			count = MAX_MATERIAL_COUNT;
		}

		for (uint i = 0; i < count; i++)
		{
			m_MaterialStruct.Materials[i].Color = materials[i].Color.getRGB();
			m_MaterialStruct.Materials[i].Reflectivity = materials[i].Reflectivity;
		}

		m_MaterialStruct.Materials[0].Color.X = 1.0f;
		m_MaterialStruct.Materials[1].Color.Y = 1.0f;

		loadMaterialBuffer();

	}
	void DXMaterialShader::loadMaterialBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		DXContext::GetDevContext()->Map(m_MaterialBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MaterialStruct, sizeof(PS_MATERIAL_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MaterialBuffer, NULL);
	}

	void DXMaterialShader::start() const
	{
		DXShader::start();

		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		devcon->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
		devcon->VSSetConstantBuffers(1, 1, &m_LightPositionBuffer);

		devcon->PSSetConstantBuffers(0, 1, &m_LightColorBuffer);
		devcon->PSSetConstantBuffers(1, 1, &m_MaterialBuffer);

		loadMatrixBuffer();
		loadLightBuffers();
		loadMaterialBuffer();
	}

	void DXMaterialShader::cleanup()
	{
		cleanDXShader();

		//Vertex shader buffer
		DXRELEASE(m_MatrixBuffer);
		DXRELEASE(m_LightPositionBuffer);

		//Pixel shader buffer
		DXRELEASE(m_LightColorBuffer);
		DXRELEASE(m_MaterialBuffer);
	}
}}}