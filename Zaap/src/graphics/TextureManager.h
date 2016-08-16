#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API TextureManager
	{
	private:
		static std::vector<Texture*> s_Textures;
	public:
		static Texture* AddTexture(Texture* texture);
		static Texture* GetTexture(String textureName);
		static Texture2D* LoadTexture2D(String textureName, char const *texturePath);
		static Texture2D* LoadTexture2D(String textureName, String texturePath);
		static Texture2D* LoadTexture2D(String textureName, Image image);

		static void Cleanup();
	};

}}
