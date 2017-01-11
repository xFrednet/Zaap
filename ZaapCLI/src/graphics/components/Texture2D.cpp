#include "Texture2D.h"

namespace ZaapCLI
{
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructors //
	/* //////////////////////////////////////////////////////////////////////////////// */
	
	Texture2D::Texture2D(System::String^ name, System::String^ filePath, bool addToTextureManager)
		: Texture(zaap::graphics::API::Texture::CreateTexture2D(to_CPP_String(name), to_CPP_String(filePath), addToTextureManager))
	{
	}

	Texture2D::Texture2D(System::String^ name, Bitmap bitmap, bool addToTextureManager)
		: Texture(zaap::graphics::API::Texture::CreateTexture2D(to_CPP_String(name), *bitmap.getHandle(), addToTextureManager))
	{
	}

	Texture2D::Texture2D(zaap::graphics::API::Texture2D* instance)
		: Texture(instance)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	void Texture2D::bind(uint slot)
	{
		getHandle()->bind(slot);
	}

	void Texture2D::unbind(uint slot)
	{
		getHandle()->unbind(slot);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	uint Texture2D::getWidth()
	{
		return getHandle()->getWidth();
	}

	uint Texture2D::getHeight()
	{
		return getHandle()->getHeight();
	}

	zaap::graphics::API::Texture2D* Texture2D::getHandle()
	{
		return (zaap::graphics::API::Texture2D*)m_Instance;
	}
}
