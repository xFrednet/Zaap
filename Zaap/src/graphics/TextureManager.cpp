#include "TextureManager.h"

namespace zaap { namespace graphics {
	
	std::vector<API::Texture> TextureManager::s_Textures;

	API::Texture TextureManager::AddTexture(API::Texture texture)
	{
		s_Textures.push_back(texture);
		return texture;
	}

	API::Texture TextureManager::GetTexture(String textureName)
	{
		for (API::Texture texture : s_Textures)
		{
			if (texture->getTextureName() == textureName)
				return texture;
		}
		return nullptr;
	}

	void TextureManager::RemoveTexture(API::Texture texture)
	{
		for (uint i = 0; i < s_Textures.size(); i++)
		{
			if (texture.get() == s_Textures[i].get())
				s_Textures.erase(s_Textures.begin() + i);
		}
	}

	void TextureManager::RemoveTexture(String textureName)
	{
		for (uint i = 0; i < s_Textures.size(); i++)
		{
			if (textureName == s_Textures[i]->getTextureName())
				s_Textures.erase(s_Textures.begin() + i);
		}
	}

	void TextureManager::ClearTextures()
	{
		s_Textures.clear();
	}

	bool TextureManager::Contains(String textureName)
	{
		return (GetTexture(textureName) != nullptr);
	}
}}
