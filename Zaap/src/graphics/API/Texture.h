#pragma once

#include <Common.h>
#include <Types.h>

#pragma warning( disable : 4251)

namespace zaap { namespace graphics { 
	
	class Image;
	
	namespace API {

	class Texture2D;

	enum class ZAAP_API TextureType
	{
		Texture1D,
		Texture2D,
		Texture3D,
		UNKNOWN
	};

	/*This class is a Polymorphic class for the representation of a texture in Graphic Ram.
	For direct Texture Representation and the ability to read Image parts use zaap::graphics::Image
	*/
	class ZAAP_API Texture
	{
	private:
		static std::vector<Texture*> s_Textures;

	protected:
		String m_TextureName;

		TextureType m_TextureType;
	public:
		Texture(String &textureName, TextureType textureType);
		virtual ~Texture();

		// texture creation
		static Texture2D* CreateTexture2D(char const* name, char const* filePath, bool addToTextureManager = true);
		static Texture2D* CreateTexture2D(String name, String filePath, bool addToTextureManager = true);
		static Texture2D* CreateTexture2D(String name, Image image, bool addToTextureManager = true);
		
		static void Cleanup();

		// getters
		String getTextureName() const;
		TextureType getTextureType() const;

		/*This Method should be called before the texture is deleted*/
		virtual void cleanup() = 0;
	};

}}}
