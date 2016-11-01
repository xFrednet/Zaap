#include "FontShader2D.h"
#include <events/Input.h>

namespace zaap { namespace graphics {
	void FontShader2D::calculateBaseMatrix(uint width, uint height)
	{
		float scaleH = (2.0f / height);
		float scaleW = (2.0f / width);

		m_BaseTransformationMatrix.identify(1.0f);
		m_BaseTransformationMatrix.scale(scaleW, scaleH, 1.0f);
	}

	FontShader2D::FontShader2D()
	{
		Input::AddWindowCallback(METHOD_1(FontShader2D::windowCallback));
	}

	void FontShader2D::setSize(float size)
	{
		m_TransformationMatrix = m_BaseTransformationMatrix;
		m_TransformationMatrix.scale(size, size, 1.0f);
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
}}
