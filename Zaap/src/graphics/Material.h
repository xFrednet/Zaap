#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Color.h>

namespace zaap { namespace graphics {
	
	struct ZAAP_API Material
	{
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Values //
		/* //////////////////////////////////////////////////////////////////////////////// */

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
		Color Color;

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
		float Reflectivity;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructor //
		/* //////////////////////////////////////////////////////////////////////////////// */
		
		// <Constructor>
		//      Material
		//
		// <Descripton>
		//      This creates a new instance of the @Material struct.
		//
		Material();

		// <Constructor>
		//      Material
		//
		// <Descripton>
		//      This creates a new instance of the @Material struct.
		//
		// <Input>
		//      color:
		//          The @Color of this @Material. It is used by some
		//          shaders.
		//      reflectivity:
		//          The reflectivity of this @Material. It is used by some
		//          shaders.
		//
		Material(graphics::Color color, float reflectivity);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Function>
		//      toString
		//
		// <Description>
		//      This combines the values of this @Material into a string.
		//
		// <Example>
		//      "Material(Color(R 1.0, G 1.0, B 1.0, A 1.0), Reflectivity: 0.0)"
		//
		// <Return>
		//      The String containing the information from this instance.
		//
		String toString() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Operators // 
		/* //////////////////////////////////////////////////////////////////////////////// */

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
		inline bool operator==(const Material& other) const;

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
		inline bool operator!=(const Material& other) const;

	};

	// <Function>
	//      Equal
	//      
	// <Description>
	//      This tests if the given @Materials are the same.
	//      
	// <Input>
	//      a:
	//          The first object for comparison.
	//      b:
	//          The second object for comparison.
	//
	// <Return>
	//      This returns the test result in form of a boolean.
	//      
	ZAAP_API bool Equal(const Material& a, const Material& b);

}}