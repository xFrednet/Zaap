#include "Texture.h"

#include <graphics/Bitmap.h>
#include <graphics/TextureManager.h>
#include <graphics/API/DX/DXTexture2D.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace API {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Static texture management // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	std::map<UUID, Texture*> Texture::s_Textures;
	bool Texture::s_IsCleanup = false;

	void Texture::AddTexture(Texture* texture)
	{
		s_Textures[texture->getUUID()] = texture;
	}
	
	void Texture::RemoveTexture(Texture* texture)
	{
		//calls the RemoveTexture method with the UUID
		RemoveTexture(texture->getUUID());
	}
	void Texture::RemoveTexture(UUID textureUUID)
	{
		if (s_IsCleanup) 
			return;
		
		std::map<UUID, Texture*>::iterator it = s_Textures.find(textureUUID);
		
		if (it != s_Textures.end()) // != means it's a member
			s_Textures.erase(it);

		// else has nothing to do (sorry)
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Texture creation // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	/* ********************************************************* */
	// * Texture2D *
	/* ********************************************************* */
	Texture2D* Texture::CreateTexture2D(char const* name, char const* filePath, bool addToTextureManager)
	{
		return CreateTexture2D(String(name), String(filePath), addToTextureManager);
	}
	Texture2D* Texture::CreateTexture2D(String name, String filePath, bool addToTextureManager)
	{
		Texture2D* texture = new DX::DXTexture2D(name, filePath);
		
		if (addToTextureManager)
			TextureManager::AddTexture(texture);

		return texture;
	}
	Texture2D* Texture::CreateTexture2D(String name, Bitmap image, bool addToTextureManager)
	{
		Texture2D* texture = new DX::DXTexture2D(name, image);

		if (addToTextureManager)
			TextureManager::AddTexture(texture);

		return texture;
	}

	void Texture::Cleanup()
	{
		s_IsCleanup = true;

		TextureManager::ClearTextures();

		std::map<UUID, Texture*>::iterator it;
		for (it = s_Textures.begin(); it != s_Textures.end(); it++)
		{
			delete it->second;
		}

		s_Textures.clear();

		s_IsCleanup = false;
		ZAAP_CLEANUP_INFO();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Texture Class // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	Texture::Texture(const String &textureName, ZA_TEXTURE_TYPE textureType)
		: m_TextureName(textureName),
		m_TextureType(textureType)
	{
		RandomUUID(&m_UUID);

		AddTexture(this);
	}
	Texture::~Texture()
	{
		RemoveTexture(m_UUID);
	}

	void Texture::destroy()
	{
		delete this;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	bool Texture::operator==(Texture const* other) const
	{
		return Equal(this, other);
	}
	bool Texture::operator!=(Texture const* other) const
	{
		return !Equal(this, other);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	String Texture::getTextureName() const
	{
		return m_TextureName;
	}
	ZA_TEXTURE_TYPE Texture::getTextureType() const
	{
		return m_TextureType;
	}
	UUID Texture::getUUID() const
	{
		return m_UUID;
	}



	bool Equal(Texture const* a, const Texture* b)
	{
		return Equal(a->getUUID(), b->getUUID());
	}
}}}
