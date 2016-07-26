#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/DXShader/DXShader.h>
#include <graphics/API/DXCommon.h>
#include <maths/Mat4.h>

namespace zaap {namespace graphics {
	class Light;
}
}

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXStaticShader : public DXShader
	{
		struct VS_MATRIX_BUFFER
		{
			math::Mat4 ProjectionMatrix;
			math::Mat4 TransformationMatrix;
			math::Mat4 ViewMatrix;
		};

		struct VS_LIGHT_BUFFER
		{
			math::Vec3 LightPosition;
		private:
			float filler = 0;
		};

	protected:
		ID3D11Buffer *m_MarixBuffer;
		VS_MATRIX_BUFFER m_MatrixBufferStruct;
		void loadMarixBuffer() const;

		ID3D11Buffer *m_LightBuffer;
		VS_LIGHT_BUFFER m_LightBufferStruct;
	public:
		DXStaticShader(void);

		//matrix loader
		void loadTransformationMatrix(math::Mat4 &matrix);
		void loadProjectionMatrix(math::Mat4 &matrix);
		void loadViewMatrix(math::Mat4 &matrix);


		//light loader
		void loadLight(const Light* light);

		void cleanup() override;
	};

}}}
