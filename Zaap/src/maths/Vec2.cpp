#include "Vec2.h"
#include <util/Console.h>

namespace zaap { namespace math {

	Vec2::Vec2()
	{
		X = 0;
		Y = 0;
	}
	Vec2::Vec2(float x, float y)
	{
		X = x;
		Y = y;
	}


	String Vec2::toString()
	{
		return "Vec2(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ")";
	}

	//
	// Operations
	//
	void Vec2::scale(float scale)
	{
		X *= scale;
		Y *= scale;
	}

	float Vec2::getLength() const
	{
		return sqrtf(X * X + Y * Y);
	}

	void Vec2::normalize()
	{
		float d = getLength();
		X /= d;
		Y /= d;
	}

	void Vec2::clamp(float min, float max)
	{
		if (min >= max)
		{
			ZAAP_ALERT("Vec2::clamp: The min Value has to be lower than the max Value");
			return;
		}
		//X
		if (X < min) X = min;
		else if (X > max) X = max;

		//Y
		if (Y < min) Y = min;
		else if (Y > max) Y = max;
	}

	float Vec2::dot(const Vec2& v) const
	{
		return X * v.X + Y * v.Y;
	}

	//
	// Operators
	//
	bool Vec2::operator==(Vec2 &other) const
	{
		return X == other.X && Y == other.Y;
	}
	bool Vec2::operator!=(Vec2 &other) const
	{
		return X != other.X || Y != other.Y;
	}

	Vec2& Vec2::operator+=(Vec2 &other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}
	Vec2& Vec2::operator-=(Vec2 &other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}
	Vec2& Vec2::operator*=(Vec2 &other)
	{
		X *= other.X;
		Y *= other.Y;
		return *this;
	}
	Vec2& Vec2::operator*=(float scale)
	{
		this->scale(scale);
		return *this;
	}

	Vec2 Vec2::operator+(Vec2 &other) const
	{
		return Vec2(X + other.X, Y + other.Y);
	}
	Vec2 Vec2::operator-(Vec2 &other) const
	{
		return Vec2(X - other.X, Y - other.Y);
	}
	Vec2 Vec2::operator*(Vec2 &other) const
	{
		return Vec2(X * other.X, Y * other.Y);
	}
	Vec2 Vec2::operator*(float scale) const
	{
		return Vec2(X * scale, Y * scale);
	}

}}
