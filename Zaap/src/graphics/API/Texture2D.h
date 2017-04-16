#pragma once

#include <Common.h>

#include "Texture.h"
#include "graphics/Format.h"

namespace zaap { namespace graphics { namespace API {

	// <Class>
	//      Texture2DCore
	//
	// <Description>
	//      This class is the base class for other @Texture2DCores.
	//
	// <Note>
	//      This is only a representational object for the API textures.
	//
	class ZAAP_API Texture2DCore : public TextureCore
	{
	protected:
		uint m_Width;
		uint m_Height;
		ZA_FORMAT m_Format;

		//TODO save ZA_TEX2D_DESC
		//TODO enable dynamic updating
	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructor //
		/* //////////////////////////////////////////////////////////////////////////////// */
		Texture2DCore(const String& textureName);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util // 
		/* //////////////////////////////////////////////////////////////////////////////// */

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
		virtual void bind(uint slot = 0) = 0;
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
		virtual void unbind(uint slot = 0) = 0;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Getters // 
		/* //////////////////////////////////////////////////////////////////////////////// */

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
		uint getWidth() const;
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
		uint getHeight() const;

		// <Method>
		//      getTextureType
		//
		// <Return>
		//      This method returns the texture type.
		//
		ZA_TEXTURE_TYPE getTextureType() const override;
	};

}}}
