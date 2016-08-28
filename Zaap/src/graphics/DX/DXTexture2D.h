#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>
#include <graphics/API/DXContext.h>
#include <graphics/Image.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXTexture2D : public API::Texture2D
	{
	protected:
		D3D11_TEXTURE2D_DESC m_TextureDesc;
		ID3D11Texture2D *m_Texture;

		ID3D11ShaderResourceView *m_TextureView;
		
		D3D11_SAMPLER_DESC m_SamplerDesc;
		ID3D11SamplerState *m_SamplerState;

	public:
		DXTexture2D(String name, String filePath);
		DXTexture2D(String name, Image image);

	protected:
		void init(byte const *byte);

	public:
		void bind(uint slot = 0) override;
		void unbind(uint slot = 0) override;

		void cleanup() override;
	};
}}}