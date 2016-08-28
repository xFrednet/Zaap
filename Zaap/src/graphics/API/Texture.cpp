#include "Texture.h"

namespace zaap { namespace graphics { namespace API {

	Texture::Texture(String &textureName)
		: m_TextureName(textureName)
	{
	}

	String Texture::getTextureName() const
	{
		return m_TextureName;
	}

}}}