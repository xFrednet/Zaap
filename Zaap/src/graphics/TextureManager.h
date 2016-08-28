#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>

namespace zaap { namespace graphics {
	class Image;

	class ZAAP_API TextureManager
	{
	private:
		static std::vector<API::Texture*> s_Textures;
	public:
		static API::Texture* AddTexture(API::Texture* texture);
		static API::Texture* GetTexture(String textureName);

		static API::Texture2D* LoadTexture2D(String textureName, char const *texturePath);
		static API::Texture2D* LoadTexture2D(String textureName, String texturePath);
		static API::Texture2D* LoadTexture2D(String textureName, Image image);
		
		static bool Contains(String textureName);

		static void Cleanup();
	};

}}
