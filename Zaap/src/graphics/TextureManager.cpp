#include "TextureManager.h"

#include <graphics/DX/DXTexture2D.h>
#include <util/Console.h>

namespace zaap { namespace graphics {
	
	std::vector<Texture*> TextureManager::s_Textures;

	Texture* TextureManager::AddTexture(Texture* texture)
	{
		s_Textures.push_back(texture);
		return texture;
	}

	Texture* TextureManager::GetTexture(String textureName)
	{
		for (Texture* texture : s_Textures)
		{
			if (texture->getTextureName() == textureName)
				return texture;
		}
		return nullptr;
	}

	Texture2D* TextureManager::LoadTexture2D(String textureName, char const* texturePath)
	{
		return LoadTexture2D(textureName, String(texturePath));
	}
	Texture2D* TextureManager::LoadTexture2D(String textureName, String texturePath)
	{
		Texture2D* texture;
		texture = new DX::DXTexture2D(textureName, texturePath);
		
		AddTexture(texture);
		
		return texture;
	}
	Texture2D* TextureManager::LoadTexture2D(String textureName, Image image)
	{
		Texture2D* texture;
		texture = new DX::DXTexture2D(textureName, image);

		AddTexture(texture);

		return texture;
	}

	void TextureManager::Cleanup()
	{
		for (Texture* texture : s_Textures)
		{
			texture->cleanup();
			delete texture;
		}
		ZAAP_CLEANUP_LOG("TextureManager");
	}
}}
