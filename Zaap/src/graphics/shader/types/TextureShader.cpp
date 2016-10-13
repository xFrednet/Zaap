#include "TextureShader.h"

namespace zaap { namespace graphics {
	
	//
	// Matrix buffer
	//
	void TextureShader::setMatrixBuffer(ZA_VS_MATRIX_BUFFER matrixBuffer)
	{
		m_MatrixBufferStruct = matrixBuffer;

		loadMatrixBuffer();
	}
	void TextureShader::setProjectionMatrix(Mat4 projectionMatrix)
	{
		m_MatrixBufferStruct.ProjectionMatrix = projectionMatrix;

		loadMatrixBuffer();
	}
	void TextureShader::setTransformationMatrix(Mat4 transformationMatrix)
	{
		m_MatrixBufferStruct.TransformationMatrix = transformationMatrix;

		loadMatrixBuffer();
	}
	void TextureShader::setViewMatrix(Mat4 viewMatrix)
	{
		m_MatrixBufferStruct.ViewMatrix = viewMatrix;

		loadMatrixBuffer();
	}

	//
	// Light buffer
	//
	void TextureShader::loadLightSetup(const LightSetup* lightSetup)
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

		//loading the buffers
		loadLightBuffers();
	}
}}