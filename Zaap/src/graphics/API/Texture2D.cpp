#include "Texture2D.h"

namespace zaap { namespace graphics { namespace API {
	
	Texture2D::Texture2D(const String& textureName)
		: Texture(textureName, ZA_TEXTURE_TYPE_TEXTURE_2D)
	{
		m_Width = 0;
		m_Height = 0;
		m_Format = ZA_FORMAT_UNKNOWN;
	}

	uint Texture2D::getWidth() const
	{
		return m_Width;
	}
	uint Texture2D::getHeight() const
	{
		return m_Height;
	}
}}}