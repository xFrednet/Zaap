#pragma once

#include <Common.h>

namespace zaap
{
	struct Vec2;

	struct ZAAP_API Dimensions
	{
		uint Width;
		uint Height;

		// <Constructor>
		//      Point
		//
		// <Input>
		//      width::
		//          The width value.;;
		//      height::
		//          The height value.;;
		//
		Dimensions(uint width = 0, uint height = 0)
			: Width(width), Height(height)
		{
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Setters and Getters // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//      setWidth
		//
		// <Input>
		//      width::
		//          The new Width of this object.
		//          The width will be set to 0 if the input 
		//          is below 0.;;
		//
		inline void setWidth(const float& width)
		{
			if (width > 0)
				Width = (uint)floor(width + 0.5f);
			else
				Width = 0;
		}
		// <Method>
		//      setHeight
		//
		// <Input>
		//      height::
		//          The new Height of this object.
		//          The height will be set to 0 if the input 
		//          is below 0.;;
		//
		inline void setHeight(const float& height)
		{
			if (height > 0)
				Height = (uint)floor(height + 0.5f);
			else
				Height = 0;
		}

		// <Method>
		//      setDimensions
		//
		// <Input>
		//      width::
		//          The new Width of this object.
		//          The width will be set to 0 if the input 
		//          is below 0.;;
		//      height::
		//          The new Height of this object.
		//          The height will be set to 0 if the input 
		//          is below 0.;;
		//
		inline void setDimensions(const float& width, const float& height)
		{
			setWidth(width);
			setHeight(height);
		}

		// <Method>
		//      getVector
		//
		// <Description>
		//      This saves the Width and the Height
		//      value to a a Vec2 and returns it.
		//
		// <Return>
		//      The @Vec2 width the Width and Height value.
		//
		Vec2 getVector() const;

		// <Method>
		//      getArea
		//
		// <Description>
		//      This calculates the area of this @Dimensions.
		//
		uint getArea() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Operators // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//      operator==
		//
		// <Description>
		//      This method compares this and the given @Dimensions.
		//
		// <Note>
		//      This calls the Equal method for this struct.
		//
		// <Input>
		//      other::
		//          The second object for comparison.;;
		//
		// <Return>
		//      This returns the test result in form of a boolean.
		//
		inline bool operator==(const Dimensions& other) const;
		// <Method>
		//      operator!=
		//
		// <Description>
		//      This method compares this and the given @Dimensions.
		//
		// <Note>
		//      This calls the Equal method for this struct.
		//
		// <Input>
		//      other::
		//          The second object for comparison.;;
		//
		// <Return>
		//      This returns the test result in form of a boolean.
		//
		inline bool operator!=(const Dimensions& other) const;

		// <Method>
		//      operator+
		//
		// <Description>
		//      This adds the submitted @Dimensions to this
		//      @Dimensions and returns the result.
		//
		// <Input>
		//      other::
		//          The other @Dimensions that should be added.;;
		//
		// <Return>
		//      The @Dimensions that resulted from this operation.
		//
		inline Dimensions operator+(const Dimensions& other) const;
		// <Method>
		//      operator-
		//
		// <Description>
		//      This subtracts the this and the submitted
		//      @Dimensions and returns the result.
		//
		// <Input>
		//      other::
		//          The other @Dimensions that should be subtracted.;;
		//
		// <Return>
		//      The @Dimensions that resulted from this operation.
		//
		inline Dimensions operator-(const Dimensions& other) const;

		// <Method>
		//      operator+=
		//
		// <Description>
		//      This adds the submitted @Dimensions to this @Dimensions
		//
		// <Input>
		//      other::
		//          The other @Dimensions that should be added.;;
		//
		// <Return>
		//      This returns this @Dimensions object.
		//
		inline Dimensions& operator+=(const Dimensions& other);
		// <Method>
		//      operator-=
		//
		// <Description>
		//      This subtracts the submitted @Dimensions from this @Dimensions.
		//
		// <Input>
		//      other::
		//          The other @Dimensions that should be subtracted.;;
		//
		// <Return>
		//      This returns this @Dimensions object.
		//
		inline Dimensions& operator-=(const Dimensions& other);
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
	ZAAP_API bool Equal(const Dimensions& a, const Dimensions& b);

	// <Function>
	//      Add
	//
	// <Description>
	//      This adds the two @Dimensions together by adding
	//      their Width and Height values together.
	//
	// <Input>
	//      a::
	//          The first @Dimensions.;;
	//      b::
	//          The second @Dimensions that will be added 
	//          to the first @Dimensions.;;
	//
	// <Return>
	//      The resulting @Dimensions.
	//
	ZAAP_API Dimensions Add(const Dimensions& a, const Dimensions& b);
	// <Function>
	//      Subtract
	//
	// <Description>
	//      This subtracts the two @Dimensions from each other
	//      by subtracting their X and Y values.
	//
	// <Input>
	//      a::
	//          The first @Dimensions.;;
	//      b::
	//          The second @Dimensions that will be subtracted from 
	//          the first @Dimensions.;;
	//
	// <Return>
	//      The resulting @Dimensions.
	//
	ZAAP_API Dimensions Subtract(const Dimensions& a, const Dimensions& b);
}
