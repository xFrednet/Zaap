#pragma once

#include <Common.h>

#include "Point.h"
#include "Dimensions.h"

namespace zaap {
	
	struct ZAAP_API Rectangle
	{
		union
		{
			struct
			{
				int X;
				int Y;
			};
			Point Position;
		};

		union
		{
			struct
			{
				uint Width;
				uint Height;
			};
			Dimensions Dimension;
		};

		// <Constructor>
		//		Rectangle
		//
		// <Description>
		//		This creates a new object with the given parameters.
		//
		// <Input>
		//		x::
		//			The value that should be used for the x Position.;;
		//		y::
		//			The value that should be used for the y Position.;;
		//		width::
		//			The width of the @Rectangle.;;
		//		height::
		//			The height of the @Rectangle.;;
		//
		Rectangle(int x = 0, int y = 0, uint width = 0, uint height = 0);
		Rectangle(Point position, uint width = 0, uint height = 0);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//		getSize
		//
		// <Description>
		//		This returns the area size of this @Rectangle.
		//
		// <Return>
		//		The area of this Rectangle.
		//
		int getSize() const;
		// <Method>
		//		intersects
		//
		// <Description>
		//		This tests if the given @Rectangle intersects with
		//		this @Rectangle
		//
		// <Input>
		//		other::
		//			The other rectangle that should be tested.;;
		//
		// <Return>
		//		The test Result.
		//
		bool intersects(const Rectangle& other) const;
		
		// <Method>
		//		contains
		//
		// <Description>
		//		This tests if the given point is inside this @Rectangle.
		//
		// <Input>
		//		point::
		//			The point that should be tested.;;
		//
		// <Return>
		//		This returns the test result.
		//
		bool contains(const Point& point) const;
		// <Method>
		//		contains
		//
		// <Description>
		//		This tests if the given coordinates are
		//		inside this @Rectangle.
		//
		// <Input>
		//		x::
		//			The x value of the point that should be tested.;;
		//		y::
		//			The y value of the point that should be tested.;;
		//
		// <Return>
		//		This returns the test result.
		//
		bool contains(const int& x, const int& y) const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Setters and Getters // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		/* ********************************************************* */
		// * Position/X/Y *
		/* ********************************************************* */

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
		//		setPosition
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
		inline void setPosition(const float& x, const float& y)
		{
			setX(x);
			setY(y);
		}

		/* ********************************************************* */
		// * size *
		/* ********************************************************* */

		// <Method>
		//		setWidth
		//
		// <Input>
		//		width::
		//			The new width value.;;
		//
		inline void setWidth(const float& width);

		// <Method>
		//		setHeight
		//
		// <Input>
		//		height::
		//			The new height value.;;
		//
		inline void setHeight(const float& height);

		// <Method>
		//		setSize
		//
		// <Input>
		//		width::
		//			The new Width value.;;
		//		height::
		//			The new Height Value.;;
		//
		inline void setDimension(const float& width, const float& height);

		/* ********************************************************* */
		// * calculated values *
		/* ********************************************************* */

		// <Method>
		//		getMinX
		//
		// <Description>
		//		This calculates the smallest X value of this Rectangle.
		//
		// <Note>
		//		This also works with negative values.
		//
		// <Return>
		//		The smallest X value.
		//
		int getMinX() const;
		// <Method>
		//		getMinY
		//
		// <Description>
		//		This calculates the smallest Y value of this Rectangle.
		//
		// <Note>
		//		This also works with negative values.
		//
		// <Return>
		//		The smallest Y value.
		//
		int getMinY() const;

		// <Method>
		//		getMaxX
		//
		// <Description>
		//		This calculates the largest X value of this Rectangle.
		//
		// <Note>
		//		This also works with negative values.
		//
		// <Return>
		//		The largest X value.
		//
		int getMaxX() const;
		// <Method>
		//		getMaxY
		//
		// <Description>
		//		This calculates the largest Y value of this Rectangle.
		//
		// <Note>
		//		This also works with negative values.
		//
		// <Return>
		//		The largest Y value.
		//
		int getMaxY() const;

		// <Method>
		//		getCenterX
		//
		// <Description>
		//		This returns the X value from this center.
		//
		// <Note>
		//		The return value is a Integer this means that
		//		any decimal info will be lost.
		//
		// <Return>
		//		The X value of the center.
		//
		int getCenterX() const;
		// <Method>
		//		getCenterY
		//
		// <Description>
		//		This returns the Y value from this center.
		//
		// <Note>
		//		The return value is a Integer this means that
		//		any decimal info will be lost.
		//
		// <Return>
		//		The Y value of the center.
		//
		int getCenterY() const;
		// <Method>
		//		getCenter
		//
		// <Description>
		//		This returns the center point of this @Rectangle.
		//
		// <Note>
		//		The Point stores the values as Integers this means that
		//		any decimal info will be lost.
		//
		// <Return>
		//		This returns the center point of this @Rectangle.
		//
		Point getCenter() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Operators // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//      operator==
		//
		// <Description>
		//      This method compares this and the given @Rectangle.
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
		inline bool operator==(const Rectangle& other) const;

		// <Method>
		//      operator!=
		//
		// <Description>
		//      This method compares this and the given @Rectangle.
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
		inline bool operator!=(const Rectangle& other) const;
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
	ZAAP_API bool Equal(const Rectangle& a, const Rectangle& b);
}
