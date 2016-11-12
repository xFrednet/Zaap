#include "Vec2.h"
#include <util/Console.h>

namespace zaap {

	Vec2::Vec2()
	{
		X = 0;
		Y = 0;
	}
	Vec2::Vec2(const Vec2& a)
		: X(a.X),
		Y(a.Y)
	{
	}
	Vec2::Vec2(const float &x, const float &y)
	{
		X = x;
		Y = y;
	}

	String Vec2::toString() const
	{
		return "Vec2(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ")";
	}

	//
	// Operations
	//
	void  Vec2::normalize()
	{
		*this = Normalize(*this);
	}
	void  Vec2::scale(const float &scale)
	{
		*this = Scale(*this, scale);
	}
	void  Vec2::clamp(const float &min, const float &max)
	{
		*this = Clamp(*this, min, max);
	}
	float Vec2::dot(const Vec2& v) const
	{
		return Dot(*this, v);
	}
	float Vec2::getLength() const
	{
		return Length(*this);
	}

	//
	// Operators
	//
	bool Vec2::operator==(const Vec2 &other) const
	{
		return Equal(*this, other);
	}
	bool Vec2::operator!=(const Vec2 &other) const
	{
		return !Equal(*this, other);
	}

	Vec2& Vec2::operator+=(const Vec2 &other)
	{
		*this = Add(*this, other);
		return *this;
	}
	Vec2& Vec2::operator-=(const Vec2 &other)
	{
		*this = Subtract(*this, other);
		return *this;
	}
	Vec2& Vec2::operator*=(const Vec2 &other)
	{
		*this = Multiply(*this, other);
		return *this;
	}
	Vec2& Vec2::operator/=(const Vec2& other)
	{
		*this = Divide(*this, other);
		return *this;
	}

	Vec2& Vec2::operator*=(const float &value)
	{
		*this = Multiply(*this, value);
		return *this;
	}
	Vec2& Vec2::operator/=(const float &value)
	{
		*this = Divide(*this, value);
		return *this;
	}

	Vec2 Vec2::operator+(const Vec2 &other) const
	{
		return Add(*this, other);
	}
	Vec2 Vec2::operator-(const Vec2 &other) const
	{
		return Subtract(*this, other);
	}
	Vec2 Vec2::operator*(const Vec2 &other) const
	{
		return Multiply(*this, other);
	}
	Vec2 Vec2::operator/(const Vec2& other) const
	{
		return Divide(*this, other);
	}

	Vec2 Vec2::operator*(const float &value) const
	{
		return Multiply(*this, value);
	}
	Vec2 Vec2::operator/(const float &value) const
	{
		return Divide(*this, value);
	}
}

//
// Operations && Util Methods
//
namespace zaap
{
	//
	// Operations
	//
	Vec2 Add(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.X + b.X, a.Y + b.Y);
	}
	Vec2 Subtract(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.X - b.X, a.Y - b.Y);
	}
	Vec2 Multiply(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.X * b.X, a.Y * b.Y);
	}
	Vec2 Divide(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.X / b.X, a.Y / b.Y);
	}

	Vec2 Multiply(const Vec2& a, const float &b)
	{
		return Vec2(a.X * b, a.Y * b);
	}
	Vec2 Divide(const Vec2& a, const float &b)
	{
		return Vec2(a.X / b, a.Y / b);
	}

	bool Equal(const Vec2& a, const Vec2& b)
	{
		return (a.X == b.X) && (a.Y == b.Y);
	}
	
	//
	// Util Methods
	//
	Vec2  Normalize(const Vec2& a)
	{
		float d = Length(a);
		return Vec2(a.X / d, a.Y / d);
	}
	Vec2  Scale(const Vec2& a, const float &scale)
	{
		return Vec2(a.X * scale, a.Y * scale);
	}
	Vec2  Clamp(const Vec2& a, const float &min, const float &max)
	{
		Vec2 rVec(a);
		if (min > max)
		{
			ZAAP_ALERT("clamp: The min Value has to be lower than the max Value");
			return rVec;
		}

		if (rVec.X < min) rVec.X = min;
		else if (rVec.Y > max) rVec.X = max;

		if (rVec.Y < min) rVec.Y = min;
		else if (rVec.Y > max) rVec.Y = max;

		return rVec;
	}
	float Dot(const Vec2& a, const Vec2& b)
	{
		return (a.X * b.X) + (a.Y * b.Y);
	}
	float Length(const Vec2& a)
	{
		return sqrtf(a.X * a.X + a.Y * a.Y);
	}
}

