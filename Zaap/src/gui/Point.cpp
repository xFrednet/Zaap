#include "Point.h"

namespace zaap { namespace gui {
	bool Point::operator==(const Point& other) const
	{
		return Equal(*this, other);
	}

	bool Point::operator!=(const Point& other) const
	{
		return !Equal(*this, other);
	}

	Point Point::operator+(const Point& other) const
	{
		return Add(*this, other);
	}
	Point Point::operator-(const Point& other) const
	{
		return Subtract(*this, other);
	}

	Point& Point::operator+=(const Point& other)
	{
		*this = Add(*this, other);
		return *this;
	}
	Point& Point::operator-=(const Point& other)
	{
		*this = Subtract(*this, other);
		return *this;
	}


	bool Equal(const Point& a, const Point& b)
	{
		return (a.X == b.X) && (a.Y == b.Y);
	}

	Point Add(const Point& a, const Point& b)
	{
		return Point(a.X + b.X, a.Y + b.Y);
	}
	Point Subtract(const Point& a, const Point& b)
	{
		return Point(a.X - b.X, a.Y - b.Y);
	}
}}
