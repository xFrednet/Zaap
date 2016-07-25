#pragma once

#include <Common.h>
#include <Types.h>

#include "Texture.h"

namespace zaap { namespace graphics {
		
	class ZAAP_API Texture2D : public Texture
	{
	protected:
		uint m_Width;
		uint m_Height;
		uint m_BitsPerPixel;
	public:
		Texture2D(String &textureName, String &filePath);

		uint getWidth(void) const;
		uint getHeight(void) const;

		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		bool operator==(Texture2D& texture2D) const;

	};

}}
