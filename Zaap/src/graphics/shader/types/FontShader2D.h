#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Mat4.h>
#include <graphics/Color.h>
#include <graphics/shader/Shader.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API FontShader2D : public Shader
	{
	protected:
		Mat4 m_TransformationMatrix;
		virtual void loadMatrixBuffer() const  = 0;

		Color m_TextColor;
		virtual void loadTextColor() const = 0;
	public:
		virtual ~FontShader2D()
		{
		}

		void setTransformationMatrix(Mat4 matrix);
		void setColor(Color color);
	};

}}
