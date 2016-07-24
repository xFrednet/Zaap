#include "Texture.h"

namespace zaap { namespace graphics {
	
	Texture::Texture(String &textureName, String &filePath)
	{
		m_TextureName = textureName;
		m_FilePath = filePath;
	}

	String Texture::getFilePath() const
	{
		return m_FilePath;
	}

	String Texture::getTextureName() const
	{
		return m_TextureName;
	}

}}