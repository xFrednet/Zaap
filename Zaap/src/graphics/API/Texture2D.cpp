#include "Texture2D.h"

namespace zaap { namespace graphics { namespace API {
	Texture2DCore::Texture2DCore(const String& textureName)
		: TextureCore(textureName), 
		m_Width(0),
		m_Height(0),
		m_Format(ZA_FORMAT_UNKNOWN)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	uint Texture2DCore::getWidth() const
	{
		return m_Width;
	}
	uint Texture2DCore::getHeight() const
	{
		return m_Height;
	}

	ZA_TEXTURE_TYPE Texture2DCore::getTextureType() const
	{
		return ZA_TEXTURE_TYPE_TEXTURE_2D;
	}
}}}
