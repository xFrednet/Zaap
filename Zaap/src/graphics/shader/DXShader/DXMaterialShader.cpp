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
				DXNAME(m_MatrixBuffer, "DXMaterialShader::m_MatrixBuffer");
			} else
			{
				ZAAP_ERROR("DXMaterialShader: failed to create the m_MatrixBuffer");
			}
		}

		//
		// Scene Buffer
		//
		{
			if (CreateConstBuffer(m_SceneBuffer, sizeof(VS_SCENE_BUFFER), &m_SceneStruct))
			{
				DXNAME(m_SceneBuffer, "DXMaterialShader::m_SceneBuffer");
			} else
			{
				ZAAP_ERROR("DXMaterialShader: failed to create the m_SceneBuffer");
			}
		}

		//
		// LightPosition buffer
		//
		{
			if (CreateConstBuffer(m_VSLightBuffer, sizeof(VS_LIGHT_BUFFER), &m_VSLightStruct))
			{
				DXNAME(m_VSLightBuffer, "DXMaterialShader::m_LightPositionBuffer");
			} else
			{
				ZAAP_ERROR("DXMaterialShader: failed to create the m_LightPositionBuffer");
			}
		}

		//
		// LightColor buffer
		//
		{
			if (CreateConstBuffer(m_PSLightBuffer, sizeof(PS_LIGHT_BUFFER), &m_PSLightStruct))
			{
				DXNAME(m_PSLightBuffer, "DXMaterialShader::m_LightColorBuffer");
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
	void DXMaterialShader::loadTransformationMatrix(math::Mat4 matrix)
	{
		m_MatrixStruct.TransformationMatrix = matrix;

		loadMatrixBuffer();
	}
	void DXMaterialShader::loadProjectionMatrix(math::Mat4 matrix)
	{
		m_MatrixStruct.ProjectionMatrix = matrix;

		loadMatrixBuffer();
	}
	void DXMaterialShader::loadViewMatrix(math::Mat4 matrix)
	{
		m_MatrixStruct.ViewMatrix = matrix;

		loadMatrixBuffer();
	}
	void DXMaterialShader::loadMatrixBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;

		DXContext::GetDevContext()->Map(m_MatrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_MatrixStruct, sizeof(VS_MATRIX_BUFFER));
		DXContext::GetDevContext()->Unmap(m_MatrixBuffer, NULL);
	}

	//
	// Scene Buffer
	//
	void DXMaterialShader::loadCamera(Camera* camera)
	{
		loadViewMatrix(camera->getViewMatrix());

		m_SceneStruct.CameraPosition = camera->getPosition();

		loadSceneBuffer();
	}
	void DXMaterialShader::loadSceneBuffer() const
	{
		D3D11_MAPPED_SUBRESOURCE ms;

		DXContext::GetDevContext()->Map(m_SceneBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &m_SceneStruct, sizeof(VS_SCENE_BUFFER));
		DXContext::GetDevContext()->Unmap(m_SceneBuffer, NULL);
	}

	//
	// Light buffer
	//
	void DXMaterialShader::loadLightSetup(const LightSetup const* lightSetup)
	{
		uint count = lightSetup->getSize();
		if (count >= SUPPORTET_LIGHT_COUNT)
		{
			ZAAP_ALERT("DXMaterialShader: The submitted LightSetup has to many lights. " + std::to_string(count) + "/" + std::to_string(SUPPORTET_LIGHT_COUNT));
			count = SUPPORTET_LIGHT_COUNT;
		}

		Light const *light;
		for (uint i = 0; i < count; i++)
		{
			light = lightSetup->getConstLight(i);

			m_VSLightStruct.Position[i] = math::Vec4(light->getPosition());
			m_VSLightStruct.LightCount = count;

			m_PSLightStruct.LightColor[i] = light->getColor();
			m_PSLightStruct.LightCount = count;
		}

		m_PSLightStruct.AmbientLightColor = lightSetup->getAmbientColor();

		loadLightBuffers();
	}


	void DXMaterialShader::loadLightBuffers() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		D3D11_MAPPED_SUBRESOURCE ms;

		//Light position
		{
			devcon->Map(m_VSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_VSLightStruct, sizeof(VS_LIGHT_BUFFER));
			devcon->Unmap(m_VSLightBuffer, NULL);
		}

		//Light color
		{
			devcon->Map(m_PSLightBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &m_PSLightStruct, sizeof(PS_LIGHT_BUFFER));
			devcon->Unmap(m_PSLightBuffer, NULL);
		}
	}

	//
	// Material buffer
	//
	void DXMaterialShader::loadMaterials(Material const* materials, uint count)
	{
		if (count > 8)
		{
			ZAAP_ALERT("DXMaterialShader: Too many materials! This shader only supports 8 materials");
			count = 8;
		}

		for (uint i = 0; i < count; i++)
		{
			m_MaterialStruct.Materials[i].Color = materials[i].Color.getRGB();
			m_MaterialStruct.Materials[i].Reflectivity = materials[i].Reflectivity;
		}

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
		devcon->VSSetConstantBuffers(1, 1, &m_VSLightBuffer);
		devcon->VSSetConstantBuffers(2, 1, &m_SceneBuffer);

		devcon->PSSetConstantBuffers(0, 1, &m_PSLightBuffer);
		devcon->PSSetConstantBuffers(1, 1, &m_MaterialBuffer);

		loadMatrixBuffer();
		loadSceneBuffer();
		loadLightBuffers();
		loadMaterialBuffer();
	}

	void DXMaterialShader::cleanup()
	{

		//Vertex shader buffer
		DXRELEASE(m_MatrixBuffer);
		DXRELEASE(m_VSLightBuffer);
		DXRELEASE(m_SceneBuffer);

		//Pixel shader buffer
		DXRELEASE(m_PSLightBuffer);
		DXRELEASE(m_MaterialBuffer);
		
		cleanDXShader();

		ZAAP_CLEANUP_LOG("DXMaterialShader");
	}
}}}