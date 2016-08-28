#include "TextureManager.h"

#include <graphics/DX/DXTexture2D.h>
#include <util/Console.h>

namespace zaap { namespace graphics {
	
	std::vector<API::Texture*> TextureManager::s_Textures;

	API::Texture* TextureManager::AddTexture(API::Texture* texture)
	{
		s_Textures.push_back(texture);
		return texture;
	}

	API::Texture* TextureManager::GetTexture(String textureName)
	{
		for (API::Texture* texture : s_Textures)
		{
			if (texture->getTextureName() == textureName)
				return texture;
		}
		return nullptr;
	}

	API::Texture2D* TextureManager::LoadTexture2D(String textureName, char const* texturePath)
	{
		return LoadTexture2D(textureName, String(texturePath));
	}

	API::Texture2D* TextureManager::LoadTexture2D(String textureName, String texturePath)
	{
		API::Texture2D* texture;
		texture = new DX::DXTexture2D(textureName, texturePath);
		
		AddTexture(texture);
		
		return texture;
	}

	API::Texture2D* TextureManager::LoadTexture2D(String textureName, Image image)
	{
		API::Texture2D* texture;
		texture = new DX::DXTexture2D(textureName, image);

		AddTexture(texture);

		return texture;
	}

	bool TextureManager::Contains(String textureName)
	{
		return (GetTexture(textureName) == nullptr);
	}

	void TextureManager::Cleanup()
	{
		for (API::Texture* texture : s_Textures)
		{
			texture->cleanup();
			delete texture;
		}
		ZAAP_CLEANUP_LOG("TextureManager");
	}
}}
