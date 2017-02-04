#include "DefaultShader.h"

namespace zaap { namespace graphics {
	
	/* ##################################### */
	// # Matrix buffer #
	/* ##################################### */

	void DefaultShader::setTransformationMatrix(const Mat4& transformationMatrix)
	{
		m_MatrixBufferStruct.TransformationMatrix = transformationMatrix;

		loadMatrixBuffer();
	}

	void DefaultShader::setViewMatrix(const Mat4& viewMatrix)
	{
		m_MatrixBufferStruct.ViewMatrix = viewMatrix;

		loadMatrixBuffer();
	}

	void DefaultShader::setProjectionMatrix(const Mat4& projectionMatrix)
	{
		m_MatrixBufferStruct.ProjectionMatrix = projectionMatrix;

		loadMatrixBuffer();
	}

	void DefaultShader::setMatrixBuffer(ZA_VS_MATRIX_BUFFER matrixBuffer)
	{
		m_MatrixBufferStruct = matrixBuffer;

		loadMatrixBuffer();
	}

	ZA_VS_MATRIX_BUFFER DefaultShader::getMatrixBuffer() const
	{
		return m_MatrixBufferStruct;
	}

	/* ##################################### */
	// # Scene buffer #
	/* ##################################### */

	void DefaultShader::setCameraPosition(const Vec3& position)
	{
		m_SceneBufferStruct.CameraPosition = position;

		loadSceneBuffer();
	}

	void DefaultShader::loadScene(const Scene* scene)
	{
		m_SceneBufferStruct.CameraPosition = scene->getCamera()->getPosition();

		loadSceneBuffer();
	}

	/* ##################################### */
	// # Light buffers #
	/* ##################################### */

	void DefaultShader::loadLightSetup(const LightSetup& lightSetup)
	{
		m_PSLightBufferStruct.AmbientLight = lightSetup.getAmbientColor().getRGB();

		if (lightSetup.getSize() < ZA_SHADER_LIGHT_COUNT)
		{
			for (uint i = 0; i < lightSetup.getSize(); i++)
			{
				Light const* light = lightSetup.getConstLight(i);
				
				m_VSLightBufferStruct.LightPositions[i] = light->getPosition();
				m_PSLightBufferStruct.LightColors[i] = light->getColor();
			}
		} else
		{
			//TODO lightSetup.getSize() >= ZA_SHADER_LIGHT_COUNT

			for (uint i = 0; i < ZA_SHADER_LIGHT_COUNT; i++)
			{
				Light const* light = lightSetup.getConstLight(i);

				m_VSLightBufferStruct.LightPositions[i] = light->getPosition();
				m_PSLightBufferStruct.LightColors[i] = light->getColor();
			}
		}

		loadLightBuffers();
	}

	ZA_VS_LIGHT_BUFFER DefaultShader::getVSLightBuffer() const
	{
		return m_VSLightBufferStruct;
	}

	ZA_PS_LIGHT_BUFFER DefaultShader::getPSLightBuffer() const
	{
		return m_PSLightBufferStruct;
	}

	/* ##################################### */
	// # Material buffer #
	/* ##################################### */

	void DefaultShader::loadMaterials(const Material* materials, uint count)
	{
		if (count >= ZA_SHADER_MATERIAL_COUNT)
			count = ZA_SHADER_MATERIAL_COUNT - 1;

		memcpy(&m_MaterialBufferStruct.Materials[0], &materials[0], sizeof(Material) * count);

		loadMaterialBuffer();
	}

	ZA_PS_MATERIAL_BUFFER DefaultShader::getMaterialBuffer() const
	{
		return m_MaterialBufferStruct;
	}

	ZA_SHADER_TYPE DefaultShader::getShaderType() const
	{
		return ZA_SHADER_DEFAULT_SHADER;
	}
		
}}
