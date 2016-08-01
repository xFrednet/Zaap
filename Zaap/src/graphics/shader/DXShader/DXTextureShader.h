#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/DXShader/DXShader.h>
#include <graphics/API/DXCommon.h>
#include <maths/Mat4.h>
#include <graphics/light/Light.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXTextureShader : public DXShader
	{
		struct VS_LIGHT_BUFFER
		{
			math::Vec3 LightPosition;
		private:
			float filler = 0;
		};

		struct  PS_LIGHTCOLOR_BUFFER
		{
			Color lightColor;
		};

	protected:
		ID3D11Buffer *m_MatrixBuffer;
		VS_MATRIX_BUFFER m_MatrixBufferStruct;
		void loadMarixBuffer() const;

		ID3D11Buffer *m_LightBuffer;
		VS_LIGHT_BUFFER m_LightBufferStruct;

		ID3D11Buffer *m_LightColorBuffer;
		PS_LIGHTCOLOR_BUFFER m_LightColorStruct;
		void loadLightBuffers() const;
	public:
		DXTextureShader(void);

		//matrix loader
		void loadTransformationMatrix(math::Mat4 &matrix);
		void loadProjectionMatrix(math::Mat4 &matrix);
		void loadViewMatrix(math::Mat4 &matrix);

		//light loader
		void loadLight(const Light* light);

		void start() const override;
		void cleanup() override;
	};

}}}
