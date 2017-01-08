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
		////////////////////////////////////////////////////////////////////////////////
		// Constructors / Deconstructor // 
		////////////////////////////////////////////////////////////////////////////////
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

		// <Deconstructor>
		//      DXTexture2D
		//
		// <Description>
		//      The deconstructor releases the created DirectX objects.
		//
		~DXTexture2D();

	protected:
		ZA_RESULT init(byte const *byte, ZA_FORMAT format);

	public:
		////////////////////////////////////////////////////////////////////////////////
		// Abstract members // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      bind
		//
		// <Description>
		//      This method binds the @Texture2D to the given slot.
		//
		// <Note>
		//      This method is overridden by the API classes so it could
		//      also do some other stuff. 
		//
		// <Input>
		//      slot:
		//          The slot that the @Texture should be bound to.
		//
		void bind(uint slot = 0) override;
		
		// <Function>
		//      unbind
		//
		// <Description>
		//      This method unbinds the @Texture2D from the given slot.
		//
		// <Note>
		//      This method is overridden by the API classes so it could
		//      also do some other stuff. 
		//
		// <Input>
		//      slot:
		//          The slot that the @Texture should be unbound from.
		//
		void unbind(uint slot = 0) override;
	};
}}}
