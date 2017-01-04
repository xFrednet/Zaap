#include "Texture2D.h"

namespace zaap { namespace graphics { namespace API {
	
	Texture2D::Texture2D(const String& textureName)
		: Texture(textureName, ZA_TEXTURE_TYPE_TEXTURE_2D)
	{
		m_Width = 0;
		m_Height = 0;
		m_BitsPerPixel = 0;
	}

	uint Texture2D::getWidth() const
	{
		return m_Width;
	}
	uint Texture2D::getHeight() const
	{
		return m_Height;
	}

	bool Texture2D::operator==(Texture2D& texture2D) const
	{
		return (m_TextureName == texture2D.m_TextureName) &&
			(m_Width == texture2D.m_Width) && 
			(m_Height == texture2D.m_Height);
		//m_BitsPerPixel are not tested
	}
}}}