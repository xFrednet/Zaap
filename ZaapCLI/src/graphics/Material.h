#pragma once

#include <ZaapCLI.h>

#include <graphics\Material.h>
#include "Color.h"

namespace ZaapCLI
{
	
	public ref class Material : public ManagedClass<zaap::graphics::Material> {

	public:
		// <Value>
		//      Color
		//
		// <Description>
		//      This value stores the @Color of this @Material. The @Color
		//      is used by some @Shaders for rendering.
		//
		// <Note>
		//      It is set to white by default.
		//      
		property Color^ Color_ {
			Color^ get()
			{
				return gcnew Color(&m_Instance->Color);
			}
			
			void set(Color^ color)
			{
				m_Instance->Color = *color->getHandle();
			}
		}

		// <Value>
		//      Reflectivity
		//
		// <Description>
		//      This value stores the reflectivity of this @Material. The 
		//      reflectivity is used by some @Shaders for rendering.
		//
		// <Note>
		//      It is set to 0 by default.
		//      
		ZA_CLI_VALUE(float, Reflectivity, reflectivity);

		////////////////////////////////////////////////////////////////////////////////
		// Constructor //
		////////////////////////////////////////////////////////////////////////////////
		
		// <Constructor>
		//      Material
		//
		// <Descripton>
		//      This creates a new instance of the @Material class.
		//
		Material();

		// <Constructor>
		//      Material
		//
		// <Descripton>
		//      This creates a new instance of the @Material class.
		//
		// <Input>
		//      color:
		//          The @Color of this @Material. It is used by some
		//          shaders.
		//      reflectivity:
		//          The reflectivity of this @Material. It is used by some
		//          shaders.
		//
		Material(Color^ color, float reflectivity);

		// <Constructor>
		//      Material
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
		Material(zaap::graphics::Material* instance);

		////////////////////////////////////////////////////////////////////////////////
		// Operators // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      operator==
		//
		// <Description>
		//      This method compares this and the given @Material.
		//
		// <Input>
		//      other:
		//          The second object for comparison.
		//
		// <Return>
		//      This returns the test result in form of a boolean.
		//
		bool operator==(Material^ other);

		// <Function>
		//      operator!=
		//
		// <Description>
		//      This method compares this and the given @Material.
		//
		// <Input>
		//      other:
		//          The second object for comparison.
		//
		// <Return>
		//      This returns the test result in form of a boolean.
		//    
		bool operator!=(Material^ other);

	};

}