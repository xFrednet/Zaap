#pragma once

#include <Common.h>

namespace zaap
{
	struct Vec2;
}

namespace zaap { namespace gui {

	struct ZAAP_API Point
	{
		int X;
		int Y;

		// <Constructor>
		//		Point
		//
		// <Input>
		//		x::
		//			The X value.;;
		//		y::
		//			The Y value.;;
		//
		Point(int x = 0, int y = 0)
			: X(x), Y(y)
		{
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Setters and Getters // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//		setX
		//
		// <Input>
		//		x::
		//			The new value for X.;;
		//
		inline void setX(const float& x)
		{
			X = (int)floor(x + 0.5f);
		}

		// <Method>
		//		setY
		//
		// <Input>
		//		y::
		//			The new value for Y.;;
		//
		inline void setY(const float& y)
		{
			Y = (int)floor(y + 0.5f);
		}

		// <Method>
		//		setPos
		//
		// <Description>
		//		This sets the x and the y value.
		//
		// <Input>
		//		x::
		//			The new X value.;;
		//		y::
		//			The new Y value.;;
		//
		inline void setPos(const float& x, const float& y)
		{
			setX(x);
			setY(y);
		}

		Vec2 getVector() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Operators // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//      operator==
		//
		// <Description>
		//      This method compares this and the given @Point.
		//
		// <Note>
		//      This calls the Equal method for this class.
		//      
		// <Input>
		//      other::
		//          The second object for comparison.;;
		//
		// <Return>
		//      This returns the test result in form of a boolean.
		//
		inline bool operator==(const Point& other) const;
		// <Method>
		//      operator!=
		//
		// <Description>
		//      This method compares this and the given @Point.
		//
		// <Note>
		//      This calls the Equal method for this class.
		//  
		// <Input>
		//      other::
		//          The second object for comparison.;;
		//
		// <Return>
		//      This returns the test result in form of a boolean.
		//    
		inline bool operator!=(const Point& other) const;

		// <Method>
		//		operator+
		//
		// <Description>
		//		This adds the submitted @Point to this
		//		@Point and returns the result.
		//
		// <Input>
		//		other::
		//			The other point that should be added.;;
		//
		// <Return>
		//		The point that resulted from this operation.
		//
		inline Point operator+(const Point& other) const;
		// <Method>
		//		operator-
		//
		// <Description>
		//		This subtracts the this and the submitted
		//		@Point and returns the result.
		//
		// <Input>
		//		other::
		//			The other point that should be subtracted.;;
		//
		// <Return>
		//		The point that resulted from this operation.
		//
		inline Point operator-(const Point& other) const;
		
		// <Method>
		//		operator+=
		//
		// <Description>
		//		This adds the submitted @Point to this @Point
		//
		// <Input>
		//		other::
		//			The other point that should be added.;;
		//
		// <Return>
		//		This returns this @Point object.
		//
		inline Point& operator+=(const Point& other);
		// <Method>
		//		operator-=
		//
		// <Description>
		//		This subtracts the submitted @Point from this @Point.
		//
		// <Input>
		//		other::
		//			The other point that should be subtracted.;;
		//
		// <Return>
		//		This returns this @Point object.
		//
		inline Point& operator-=(const Point& other);

	};

	// <Function>
	//      Equal
	//      
	// <Description>
	//      This tests if the given @Structs are the same.
	//
	// <Note>
	//      This info is totally not copied and pasted for every Equal function.
	//
	// <Input>
	//      a::
	//          The first object for comparison.;;
	//      b::
	//          The second object for comparison.;;
	//       
	// <Return>
	//      This returns the test result in form of a boolean.
	//      
	ZAAP_API bool Equal(const Point& a, const Point& b);

	// <Function>
	//		Add
	//
	// <Description>
	//		This adds the two @Points together by adding
	//		their X and Y values together.
	//
	// <Input>
	//		a::
	//			The first @Point.;;
	//		b::
	//			The second @Point that will be added to the first @Point.;;
	//
	// <Return>
	//		The resulting @Point.
	//
	ZAAP_API Point Add(const Point& a, const Point& b);
	// <Function>
	//		Subtract
	//
	// <Description>
	//		This subtracts the two @Points from each other
	//		by subtracting their X and Y values.
	//		
	//
	// <Input>
	//		a::
	//			The first @Point.;;
	//		b::
	//			The second @Point that will be subtracted from 
	//			the first @Point.;;
	//
	// <Return>
	//		The resulting @Point.
	//
	ZAAP_API Point Subtract(const Point& a, const Point& b);

}}
