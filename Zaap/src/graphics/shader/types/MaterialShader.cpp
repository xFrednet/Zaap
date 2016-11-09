#include "MaterialShader.h"

#include <graphics/mesh/MaterialMesh.h>

namespace zaap { namespace graphics {
	
	//
	//Matrix buffers
	//
	void MaterialShader::setMatrixBuffer(ZA_VS_MATRIX_BUFFER matrixBuffer)
	{
		m_MatrixBufferStruct = matrixBuffer;

		loadMatrixBuffer();
	}
	void MaterialShader::setProjectionMatrix(Mat4 projectionMatrix)
	{
		m_MatrixBufferStruct.ProjectionMatrix = projectionMatrix;

		loadMatrixBuffer();
	}
	void MaterialShader::setTransformationMatrix(Mat4 transformationMatrix)
	{
		m_MatrixBufferStruct.TransformationMatrix = transformationMatrix;

		loadMatrixBuffer();
	}
	void MaterialShader::setViewMatrix(Mat4 viewMatrix)
	{
		m_MatrixBufferStruct.ViewMatrix = viewMatrix;

		loadMatrixBuffer();
	}

	//
	//Scene buffer
	//
	void MaterialShader::setCameraPosition(Vec3 cameraPosition)
	{
		m_SceneBufferStruct.CameraPosition = cameraPosition;

		loadSceneBuffer();
	}

	//
	//Light buffer
	//
	void MaterialShader::loadLightSetup(const LightSetup* lightSetup)
	{
		//lightCount
		uint lightCount = ZAAP_SHADER_LIGHT_COUNT;
		if (lightSetup->getSize() < lightCount)
			lightCount = lightSetup->getSize();

		m_VSLightBufferStruct.VSLightCount = lightCount;
		m_PSLightBufferStruct.PSLightCount = lightCount;

		//setting single lights
		Light const* light;
		for (uint i = 0; i < lightCount; i++)
		{
			light = lightSetup->getConstLight(i);
			m_VSLightBufferStruct.LightPositions[i] = light->getPosition();
			m_PSLightBufferStruct.LightColors[i] = light->getColor();
		}

		//Ambient light color
		m_PSLightBufferStruct.AmbientLight = lightSetup->getAmbientColor().getRGB();
	}

	//
	//Material buffer
	//
	void MaterialShader::loadMaterials(const MaterialMesh const* mesh)
	{
		loadMaterials(mesh->getMaterials(), mesh->getMaterialCount());
	}
	void MaterialShader::loadMaterials(const Material* materials, uint materialCount)
	{
		for (uint i = 0; i < materialCount; i++)
		{
			m_MaterialBufferStruct.Materials[i].Color = materials[i].Color.getRGB();
			m_MaterialBufferStruct.Materials[i].Reflectivity = materials[i].Reflectivity;
		}

		loadMaterialBuffer();
	}

	ZA_SHADER_TYPE MaterialShader::getShaderType() const
	{
		return ZA_SHADER_MATERIAL_SHADER;
	}
}}