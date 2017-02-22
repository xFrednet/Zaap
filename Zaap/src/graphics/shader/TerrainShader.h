﻿#pragma once

#include <Common.h>

#include <graphics/shader/Shader.h>
#include <entity/light/LightSetup.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API TerrainShader : public Shader
	{
	protected:
		//Matrix Buffer
		ZA_VS_MATRIX_BUFFER m_MatrixBufferStruct;
		virtual void loadMatrixBuffer() const = 0; 

		//Light buffers
		ZA_VS_LIGHT_BUFFER m_VSLightBufferStruct;
		ZA_PS_LIGHT_BUFFER m_PSLightBufferStruct;
		virtual void loadLightBuffers() const = 0;
	public:
		//Matrix buffer
		void setMatrixBuffer(ZA_VS_MATRIX_BUFFER matrixBuffer);
		void setProjectionMatrix(Mat4 projectionMatrix);
		void setTransformationMatrix(Mat4 transformationMatrix);
		void setViewMatrix(Mat4 iewMatrix);

		//Light buffer
		void loadLightSetup(LightSetup const* lightSetup);

		ZA_SHADER_TYPE getShaderType() const override;
	};
		
}}
