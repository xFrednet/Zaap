﻿#include "FontShader2D.h"
#include <events/Input.h>

namespace zaap { namespace graphics {
	void FontShader2D::calculateBaseMatrix(uint width, uint height)
	{
		m_XPixel = (2.0f / width);
		m_YPixel = (2.0f / height);

		m_BaseTransformationMatrix.identify(1.0f);
		m_BaseTransformationMatrix.scale(m_XPixel, m_YPixel, 1.0f);
	}

	FontShader2D::FontShader2D()
	{
		Input::AddWindowCallback(METHOD_1(FontShader2D::windowCallback));
	}

	void FontShader2D::setSize(float size)
	{
		m_TransformationMatrix = Scale(m_BaseTransformationMatrix, size, size, 1.0f);
		loadMatrixBuffer();
	}
	void FontShader2D::setPixelCoords(const uint& x, const uint& y)
	{
		m_TransformationMatrix = Traslate(m_TransformationMatrix, -1 + m_XPixel * x, -1 + m_YPixel* y, 0.0f);
		loadMatrixBuffer();
	}
	void FontShader2D::setColor(Color color)
	{
		m_TextColor = color;

		loadTextColor();
	}

	void FontShader2D::windowCallback(const Event& windowEvent)
	{
		std::cout << windowEvent.toString() << std::endl; //TODO remove debug code
		if (windowEvent.getEventType() == WINDOW_RESIZE_EVENT)
		{
			uint width = ((WindowResizeEvent*)&windowEvent)->getWidth();
			uint height = ((WindowResizeEvent*)&windowEvent)->getHeight();
			
			calculateBaseMatrix(width, height);
		}
	}

	ZA_SHADER_TYPE FontShader2D::getShaderType() const
	{
		return ZA_SHADER_FONT_SHADER_2D;
	}
}}
