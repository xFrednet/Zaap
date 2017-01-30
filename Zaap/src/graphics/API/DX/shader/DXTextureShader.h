#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/DX/shader/DXShader.h>
#include <graphics/shader/types/TextureShader.h>


namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXTextureShader : public TextureShader, public DXShader
	{
	protected:
		ID3D11Buffer *m_MatrixBuffer;
		void loadMatrixBuffer() const override;

		ID3D11Buffer *m_LightBuffer;
		ID3D11Buffer *m_LightColorBuffer;
		void loadLightBuffers() const override;
	public:
		DXTextureShader();

		void stop() const override;
		void start() const override;
		void cleanup() override;
	};

}}}
