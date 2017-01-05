#include "Texture.h"

namespace ZaapCLI
{
	
	Texture::Texture(zaap::graphics::API::Texture* instance)
		: ManagedClass(instance)
	{
		
	}

	System::String^ Texture::getTextureName()
	{
		return to_CLI_String(m_Instance->getTextureName());
	}

	ZA_TEXTURE_TYPE Texture::getTextureType()
	{
		return to_CLI_TextureType(m_Instance->getTextureType());
	}

	UUID^ Texture::getUUID()
	{
		return gcnew UUID(&m_Instance->getUUID());
	}
}
