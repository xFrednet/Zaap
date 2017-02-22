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
		//      DiffuseReflectivity
		//
		// <Description>
		//      This holds the reflectivity information for the 
		//      red, green and blue color channel.;;
		//
		// <Note>
		//    - It is set to white by default.
		//    - This is a Vec3 to make the size of this struct dividable by
		//      16 this is a requirement from DirectX.
		//
		Vec3 DiffuseReflectivity;

		// <Value>
		//      SpectralReflectivity
		//
		// <Description>
		//      This value is used to calculate the reflectivity
		//      of the spectral lighting.
		//
		// <Note>
		//      It is set to 0 by default.
		//      
		float SpectralReflectivity;

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
		Material(Color color, float reflectivity);

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