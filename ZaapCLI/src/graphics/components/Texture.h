#pragma once

#include <ZaapCLI.h>

#include <graphics\API\Texture.h>
#include "..\..\util\UUID.h"

namespace ZaapCLI
{
	
	public enum ZA_TEXTURE_TYPE {
		ZA_TEXTURE_TYPE_UNKNOWN = zaap::graphics::API::ZA_TEXTURE_TYPE_UNKNOWN,
		ZA_TEXTURE_TYPE_TEXTURE_1D = zaap::graphics::API::ZA_TEXTURE_TYPE_TEXTURE_1D,
		ZA_TEXTURE_TYPE_TEXTURE_2D = zaap::graphics::API::ZA_TEXTURE_TYPE_TEXTURE_2D,
		ZA_TEXTURE_TYPE_TEXTURE_3D = zaap::graphics::API::ZA_TEXTURE_TYPE_TEXTURE_3D
	};

	static zaap::graphics::API::ZA_TEXTURE_TYPE to_CPP_TextureType(ZA_TEXTURE_TYPE format)
	{
		return static_cast<zaap::graphics::API::ZA_TEXTURE_TYPE>(format);
	}
	static ZA_TEXTURE_TYPE to_CLI_TextureType(zaap::graphics::API::ZA_TEXTURE_TYPE format)
	{
		return static_cast<ZA_TEXTURE_TYPE>(format);
	}

	// <Class>
	//      Texture
	//
	// <Description>
	//      This class is the base class for all the other textures.
	//
	// <Note>
	//      This is only a representational object for the API textures.
	//      
	public ref class Texture : public ManagedClass<zaap::graphics::API::Texture> {
		
		////////////////////////////////////////////////////////////////////////////////
		// Constructor //
		////////////////////////////////////////////////////////////////////////////////
		
		// <Constructor>
		//      Texture
		//
		// <Description>
		//      This creates a new CLI class from the given
		//      pointer instance.
		//
		// <Note> 
		//      This is only used for ZaapCLI intern stuff.
		//      
		Texture(zaap::graphics::API::Texture* instance);
		
		////////////////////////////////////////////////////////////////////////////////
		// Getters // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      getTextureName
		//
		// <Return>
		//      This method returns the name of the texture stored in 
		//      m_TextureName
		// 
		System::String^ getTextureName();

		// <Function>
		//      getTextureType
		//
		// <Return>
		//      This method returns the texture type stored in 
		//      m_TextureType
		// 
		ZA_TEXTURE_TYPE getTextureType();

		// <Function>
		//      getUUID
		//
		// <Return>
		//      This method returns the UUID of this texture stored in 
		//      m_UUID
		// 
		UUID^ getUUID();
	};

}
