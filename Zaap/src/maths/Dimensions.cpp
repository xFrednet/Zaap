#include "Dimensions.h"

#include <maths/Vec2.h>
#include "Maths.h"

namespace zaap
{

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Setters and Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	Vec2 Dimensions::getVector() const
	{
		return Vec2((float)Width, (float)Height);
	}

	uint Dimensions::getArea() const
	{
		return Width * Height;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	bool Dimensions::operator==(const Dimensions& other) const
	{
		return Equal(*this, other);
	}
	bool Dimensions::operator!=(const Dimensions& other) const
	{
		return !Equal(*this, other);
	}

	Dimensions Dimensions::operator+(const Dimensions& other) const
	{
		return Add(*this, other);
	}
	Dimensions Dimensions::operator-(const Dimensions& other) const
	{
		return Subtract(*this, other);
	}

	Dimensions& Dimensions::operator+=(const Dimensions& other)
	{
		*this = Add(*this, other);
		return *this;
	}
	Dimensions& Dimensions::operator-=(const Dimensions& other)
	{
		*this = Subtract(*this, other);
		return *this;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Outside Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	bool Equal(const Dimensions& a, const Dimensions& b)
	{
		return (a.Width == b.Width) && 
			(a.Height == b.Height);
	}

	Dimensions Add(const Dimensions& a, const Dimensions& b)
	{
		return Dimensions(a.Width + b.Width, a.Height + b.Height);
	}
	Dimensions Subtract(const Dimensions& a, const Dimensions& b)
	{
		return Dimensions(
			(a.Width > b.Width) ? a.Width - b.Width : 0,
			(a.Height > b.Height) ? a.Height - b.Height : 0);
	}
}
