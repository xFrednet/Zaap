#pragma once

#include <Common.h>
#include "Shader.h"

#include <maths/Mat4.h>

namespace zaap { namespace graphics {


	class ZAAP_API GUIShader : public Shader
	{
	protected:

		/* ##################################### */
		// # Matrix buffer #
		/* ##################################### */
		Mat4 m_TransformationMatrix;
		virtual void loadTransformationMatrix() const = 0;

		/* ##################################### */
		// # Color buffer #
		/* ##################################### */
		ZA_PS_GUI_COLOR_BUFFER m_ColorBufferStruct;
		virtual void loadColorBuffer() const = 0;

		GUIShader();

	public:
		virtual ~GUIShader() {}
		
		// <Function>
		//		init
		//
		// <Description>
		//		This function internalizes this class by compiling
		//		the shader source code and creating the buffers.
		//
		// <Return>
		//		The return value is a @ZA_MULTI_RESULT that contains the
		//		combined results of the shader creation.
		//
		virtual ZA_MULTI_RESULT init() = 0;
		ZA_SHADER_TYPE getShaderType() const override;

		void setTargetSize(const uint& width, const uint& height);

		void setTextColor(const Color& textColor);

		/* ********************************************************* */
		// * Texture slots *
		/* ********************************************************* */
		inline uint getTextureSlot() const;
		inline uint getCharSheetSlot() const;
		
	};

}}
