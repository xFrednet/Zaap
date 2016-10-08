#include "FontShader2D.h"

namespace zaap { namespace graphics {
	
	void FontShader2D::setTransformationMatrix(ZA_VS_MATRIX_BUFFER matrix)
	{
		m_TransformationMatrix = matrix;

		loadMatrixBuffer();
	}

	void FontShader2D::setColor(Color color)
	{
		m_TextColor = color;

		loadTextColor();
	}

}}