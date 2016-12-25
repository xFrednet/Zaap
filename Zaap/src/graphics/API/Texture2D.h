#pragma once

#include <Common.h>
#include <Types.h>

#include "Texture.h"

namespace zaap { namespace graphics { namespace API {

	class ZAAP_API Texture2D : public Texture
	{
	protected:
		uint m_Width;
		uint m_Height;
		uint m_BitsPerPixel;
	public:
		Texture2D(const String& textureName);

		uint getWidth(void) const;
		uint getHeight(void) const;

		virtual ZA_RESULT bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		bool operator==(Texture2D& texture2D) const;

	};

}}}
