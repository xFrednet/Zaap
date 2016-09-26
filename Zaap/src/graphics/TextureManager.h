#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>

namespace zaap { namespace graphics {
	class Bitmap;

	class ZAAP_API TextureManager
	{
	private:
		static std::vector<API::Texture*> s_Textures;

	public:
		static API::Texture* AddTexture(API::Texture* texture);
		static API::Texture* GetTexture(String textureName);
		
		static void RemoveTexture(API::Texture* texture);
		static void RemoveTexture(String textureName);

		static void ClearTextures();
		
		static bool Contains(String textureName);
	};

}}
