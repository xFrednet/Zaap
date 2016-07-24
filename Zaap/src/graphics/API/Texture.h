#pragma once

#include "Types.h"
#include "Common.h"

#pragma warning( disable : 4251)

namespace zaap { namespace graphics {
	
	/*This class is a Polymorphic class for the Representation in the Graphics Ram.
	For direct Texture Representation and the ability to read Image parts use graphics::BITMAP
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