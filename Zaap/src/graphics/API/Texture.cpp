#include "Texture.h"

#include <graphics/DX/DXTexture2D.h>
#include <graphics/Bitmap.h>
#include <graphics/TextureManager.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace API {
	
	std::vector<Texture*> Texture::s_Textures;

	Texture::Texture(String &textureName, TextureType textureType)
		: m_TextureName(textureName),
		m_TextureType(textureType)
	{
	}
	Texture::~Texture()
	{}

	//
	// Texture Creation
	//
	Texture2D* Texture::CreateTexture2D(char const* name, char const* filePath, bool addToTextureManager)
	{
		return CreateTexture2D(String(name), String(filePath), addToTextureManager);
	}
	Texture2D* Texture::CreateTexture2D(String name, String filePath, bool addToTextureManager)
	{
		Texture2D* texture = new DX::DXTexture2D(name, filePath);

		s_Textures.push_back(texture);
		
		if (addToTextureManager)
			TextureManager::AddTexture(texture);

		return texture;
	}
	Texture2D* Texture::CreateTexture2D(String name, Bitmap image, bool addToTextureManager)
	{
		Texture2D* texture = new DX::DXTexture2D(name, image);

		s_Textures.push_back(texture);

		if (addToTextureManager)
			TextureManager::AddTexture(texture);

		return texture;
	}

	void Texture::Cleanup()
	{
		TextureManager::ClearTextures();
		for (Texture* texture : s_Textures)
		{
			texture->cleanup();
			delete texture;
		}

		ZAAP_CLEANUP_LOG("Textures");
	}

	//
	// Getters
	//
	String Texture::getTextureName() const
	{
		return m_TextureName;
	}
	TextureType Texture::getTextureType() const
	{
		return m_TextureType;
	}
}}}
