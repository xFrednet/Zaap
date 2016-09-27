﻿#include "FontShader2D.h"

namespace zaap { namespace graphics {
	
	void FontShader2D::setTransformationMatrix(math::Mat4 matrix)
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