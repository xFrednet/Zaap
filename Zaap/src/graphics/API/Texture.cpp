#include "Texture.h"

#include <graphics/Bitmap.h>
#include <graphics/TextureManager.h>
#include <graphics/API/DX/DXTexture2DCore.h>

namespace zaap { namespace graphics { namespace API {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Texture creation // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	/* ********************************************************* */
	// * Texture2D *
	/* ********************************************************* */
	Texture2D TextureCore::CreateTexture2D(const String& filePath, const ZA_TEXTURE_FILTER& filterType, const bool& addToTextureManager)
	{
		//TODO add TextureManager
		return Texture2D(CreateTexture2DCore(filePath, filterType));
	}
	Texture2D TextureCore::CreateTexture2D(const Bitmap& bitmap, const String& name, const ZA_TEXTURE_FILTER& filterType, const bool& addToTextureManager)
	{
		//TODO add TextureManager
		return Texture2D(CreateTexture2DCore(bitmap, name, filterType));
	}

	Texture2DCore* TextureCore::CreateTexture2DCore(const String& filePath, const ZA_TEXTURE_FILTER& filterType)
	{
		return new DX::DXTexture2DCore(filePath, filterType);
	}
	Texture2DCore* TextureCore::CreateTexture2DCore(const Bitmap& bitmap, const String& name, const ZA_TEXTURE_FILTER& filterType)
	{
		return new DX::DXTexture2DCore(bitmap, name, filterType);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Texture Class // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	
	/* ********************************************************* */
	// * Constructor / Deconstructor *
	/* ********************************************************* */
	TextureCore::TextureCore(const String& textureName)
		: m_Name(textureName)
	{
		RandomUUID(&m_UUID);
	}
	TextureCore::~TextureCore()
	{
	}

	/* ********************************************************* */
	// * Operators *
	/* ********************************************************* */
	bool TextureCore::operator==(TextureCore const* other) const
	{
		return Equal(this, other);
	}
	bool TextureCore::operator!=(TextureCore const* other) const
	{
		return !Equal(this, other);
	}

	bool Equal(TextureCore const* a, TextureCore const* b)
	{
		return a->getUUID() == b->getUUID();
	}

}}}
