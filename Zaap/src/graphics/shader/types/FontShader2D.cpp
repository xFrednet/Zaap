#include "FontShader2D.h"
#include <events/Input.h>

namespace zaap { namespace graphics {
	FontShader2D::FontShader2D()
	{
		Input::AddWindowCallback(METHOD_1(&FontShader2D::windowCallback));
	}

	void FontShader2D::setTransformationMatrix(Mat4 matrix)
	{
		m_TransformationMatrix = matrix;

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
	}
}}
