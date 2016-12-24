#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Bitmap.h>
#include <graphics/API/Texture2D.h>
#include <graphics/API/DX/DXContext.h>
#include <graphics/Format.h>

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
		DXTexture2D(String name, Bitmap image);

		// <Constructor>
		//      DXTexture2D
		//
		// <Description>
		//      This method creates a DXTexture2D from a given 
		//      direct X texture2D. 
		//      The second parameter indicates if the other stuff 
		//      should be created or not.
		//      
		// <Input>
		//      texture           : The texture object from DirectX.
		//      
		//      createShaderStuff : Indicates if the other stuff 
		//                          should be created.
		DXTexture2D(ID3D11Texture2D *texture, bool createShaderStuff = true);

	protected:
		ZA_RESULT init(byte const *byte, ZA_FORMAT format);

	public:
		ZA_RESULT bind(uint slot = 0) override;
		void unbind(uint slot = 0) override;

		void cleanup() override;
	};
}}}
