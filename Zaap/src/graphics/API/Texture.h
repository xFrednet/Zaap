#pragma once

#include <Common.h>
#include <Types.h>

#pragma warning( disable : 4251)

namespace zaap { namespace graphics {
	
	/*This class is a Polymorphic class for the Representation in Graphic Ram.
	For direct Texture Representation and the ability to read Image parts use zaap::graphics::BITMAP
	*/
	class ZAAP_API Texture
	{
	protected:
		String m_FilePath;
		String m_TextureName;
	public:
		Texture(String &textureName, String &filePath);

		String getFilePath() const;
		String getTextureName() const;

		/*This Method must be called to free up memory that may be used by a subclass*/
		virtual void cleanup() = 0;
	};

}}