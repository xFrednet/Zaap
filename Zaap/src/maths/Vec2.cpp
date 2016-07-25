#include "Vec2.h"

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

	void Vec2::scale(float scale)
	{
		X *= scale;
		Y *= scale;
	}

	String Vec2::toString()
	{
		return "Vec2(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ")";
	}

	//
	// operators
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