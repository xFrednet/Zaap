#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Mat4.h>
#include <graphics/Color.h>
#include <graphics/shader/Shader.h>

namespace zaap { 
	class Event;

namespace graphics {
	
	class ZAAP_API FontShader2D : public Shader
	{
	protected:
		
		// Shader Buffers
		Mat4 m_TransformationMatrix;
		virtual void loadMatrixBuffer() const  = 0;

		Color m_TextColor;
		virtual void loadTextColor() const = 0;

		Mat4 m_BaseTransformationMatrix;
		void calculateBaseMatrix(uint width, uint height);

	public:
		FontShader2D();
		virtual ~FontShader2D()
		{
		}

		void setSize(float size);
		void setColor(Color color);

		void windowCallback(const Event& windowEvent);

	};

}}
