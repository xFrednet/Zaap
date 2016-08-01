#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Mat4.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Shader
	{
	protected:
		struct VS_MATRIX_BUFFER
		{
			math::Mat4 ProjectionMatrix;
			math::Mat4 TransformationMatrix;
			math::Mat4 ViewMatrix;
		};
	public:
		virtual void start() const = 0;
		virtual void stop() const = 0;

		virtual void cleanup() = 0;
	};

}}
