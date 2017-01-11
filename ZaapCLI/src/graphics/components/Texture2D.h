#pragma once

#include <ZaapCLI.h>
#include "Texture.h"

#include <graphics\API\Texture2D.h>
#include <graphics\API\Texture.h>
#include "..\Bitmap.h"

namespace ZaapCLI
{
	public ref class Texture2D : public Texture {

	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructors //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Constructor>
		//      Texture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API from the given file path.
		//
		// <Input>
		//      name:   
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.
		//      
		//      filePath:   
		//          The path for the image file.
		//      
		//      addToTextureManager :   
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.
		//      
		//      
		Texture2D(System::String^ name, System::String^ filePath, bool addToTextureManager);
		
		// <Constructor>
		//      Texture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API from the given @Bitmap.
		//
		// <Note>
		//      Loading a file to a @Bitmap can take some more time
		//      than just loading the bytes to the @Texture2D.
		//      So don't just use a @Bitmap to load a file for
		//      a @Texture.
		//
		// <Input>
		//      name:   
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.
		//      
		//      bitmap:   
		//          A Bitmap that is used to create a @Texture2D.
		//      
		//      addToTextureManager :   
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.
		//      
		Texture2D(System::String^ name, Bitmap bitmap, bool addToTextureManager);

		// <Constructor>
		//      Texture2D
		//
		// <Description>
		//      This creates a new CLI class from the given
		//      pointer instance.
		//
		// <Note> 
		//      This is only used for ZaapCLI intern stuff.
		//
		// <Input>
		//      instance:
		//          The existing instance of this class.
		//
		Texture2D(zaap::graphics::API::Texture2D* instance);

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
		void bind(uint slot);

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
		void unbind(uint slot);

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
		uint getWidth();

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
		uint getHeight();

		// <Function>
		//      getHandle
		//
		// <Description>
		//      This returns the handle casted to a pointer from a @Texture2D.
		//
		// <Return>
		//      This returns the handle to the c++ @Texture2D.
		//
		zaap::graphics::API::Texture2D* getHandle() new;
	};
}