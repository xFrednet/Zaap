#include "Vec4.h"

namespace zaap { namespace math {

	Vec4::Vec4()
	{
		X = 0;
		Y = 0;
		Z = 0;
		W = 0;
	}
	Vec4::Vec4(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	void Vec4::scale(float scale)
	{
		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
	}

	String Vec4::toString()
	{
		return "Vec4(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ", Z:" + StringUtil::to_string(Z) + ", W:" + StringUtil::to_string(W) + ")";
	}

	//
	// operators
	//
	bool Vec4::operator==(Vec4 &other) const
	{
		return (X == other.X) && (Y == other.Y) && (Z == other.Z) && (W == other.W);
	}
	bool Vec4::operator!=(Vec4 &other) const
	{
		return (X != other.X) || (Y != other.Y) || (Z != other.Z) || (W != other.W);
	}

	Vec4& Vec4::operator+=(Vec4& other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		W += other.W;
		return *this;
	}
	Vec4& Vec4::operator-=(Vec4& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		W -= other.W;
		return *this;
	}
	Vec4& Vec4::operator*=(Vec4& other)
	{
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;
		W *= other.W;
		return *this;
	}
	Vec4& Vec4::operator*=(float scale)
	{
		this->scale(scale);
		return *this;
	}

	Vec4 Vec4::operator+(Vec4 &other) const
	{
		return Vec4(X + other.X, Y + other.Y, Z + other.Z, W + other.Z);
	}
	Vec4 Vec4::operator-(Vec4 &other) const
	{
		return Vec4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
	}
	Vec4 Vec4::operator*(Vec4 &other) const
	{
		return Vec4(X * other.X, Y * other.Y, Z * other.Z, W * other.W);
	}
	Vec4 Vec4::operator*(float scale) const
	{
		return Vec4(X * scale, Y * scale, Z * scale, W * scale);
	}
}}