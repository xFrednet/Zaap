#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/DXShader/DXShader.h>
#include <graphics/API/DXCommon.h>
#include <maths/Mat4.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXStaticShader : public DXShader
	{
		struct VS_CONSTANT_BUFFER
		{
			math::Mat4 ProjectionMatrix;
			math::Mat4 TransformationMatrix;
			math::Mat4 ViewMatrix;
		};

	protected:
		ID3D11Buffer *m_CBuffer;
		VS_CONSTANT_BUFFER m_Buffer;
	public:
		DXStaticShader(void);

		// Matrix loader
		void loadTransformationMatrix(math::Mat4 &matrix);
		void loadProjectionMatrix(math::Mat4 &matrix);
		void loadViewMatrix(math::Mat4 &matrix);

		void cleanup() override;
	};

}}}
