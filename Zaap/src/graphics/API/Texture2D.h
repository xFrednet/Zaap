#pragma once

#include <Common.h>
#include <Types.h>

#include "Texture.h"
#include "graphics/Format.h"

namespace zaap { namespace graphics { namespace API {

	class ZAAP_API Texture2D : public Texture
	{
	protected:
		uint m_Width;
		uint m_Height;
		ZA_FORMAT m_Format;
	public:
		////////////////////////////////////////////////////////////////////////////////
		// Constructors //
		////////////////////////////////////////////////////////////////////////////////
		Texture2D(const String& textureName);

		////////////////////////////////////////////////////////////////////////////////
		// Util // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      bind
		//
		// <Description>
		//      This method binds the @Texture2D to the given slot.
		//
		// <Note>
		//      This method is overridden by the API classes so it could
		//      also do some other stuff. 
		//
		// <Input>
		//      slot:
		//          The slot that the @Texture should be bound to.
		//
		virtual void bind(uint slot) = 0;

		// <Function>
		//      unbind
		//
		// <Description>
		//      This method unbinds the @Texture2D from the given slot.
		//
		// <Note>
		//      This method is overridden by the API classes so it could
		//      also do some other stuff. 
		//
		// <Input>
		//      slot:
		//          The slot that the @Texture should be unbound from.
		//
		virtual void unbind(uint slot) = 0;

		////////////////////////////////////////////////////////////////////////////////
		// Getters // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      getWidth
		// 
		// <Description>
		//      This method returns the content of the m_Width value.
		//
		// <Note>
		//      The size of the @Texture2D isn't always set. m_Width is set 
		//      to 0 by default.
		//
		// <Return>
		//      This returns the value of m_Width.
		//
		uint getWidth(void) const;

		// <Function>
		//      getHeight
		// 
		// <Description>
		//      This method returns the content of the m_Height value.
		//
		// <Note>
		//      The size of the @Texture2D isn't always set. m_Height is set 
		//      to 0 by default.
		//
		// <Return>
		//      This returns the value of m_Height.
		//
		uint getHeight(void) const;
	};

}}}
