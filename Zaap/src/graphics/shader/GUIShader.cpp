#include "GUIShader.h"

namespace zaap { namespace graphics {
	GUIShader::GUIShader()
	{
	}
	ZA_SHADER_TYPE GUIShader::getShaderType() const
	{
		return ZA_SHADER_GUI_SHADER;
	}

	void GUIShader::setTargetSize(const uint& width, const uint& height)
	{
		if (width == 0 || height == 0)
			ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);

		m_TransformationMatrix.identify();

		m_TransformationMatrix.scale(2.0f / width, -(2.0f / height), 1);
		m_TransformationMatrix.translate(-(float)(width / 2), -(float)(height / 2), 0);

		loadTransformationMatrix();
	}
	void GUIShader::setTextColor(const Color& textColor)
	{
		m_ColorBufferStruct.TextColor = textColor;
		loadColorBuffer();
	}

	/* ********************************************************* */
	// * Texture slots *
	/* ********************************************************* */
	uint GUIShader::getTextureSlot() const
	{
		return 0;
	}
	uint GUIShader::getCharSheetSlot() const
	{
		return 1;
	}
}}
