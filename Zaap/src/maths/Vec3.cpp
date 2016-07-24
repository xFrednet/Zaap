#include "Vec3.h"

namespace zaap { namespace math {

	Vec3::Vec3()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}
	Vec3::Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	void Vec3::scale(float scale)
	{
		X *= scale;
		Y *= scale;
		Z *= scale;
	}

	String Vec3::toString()
	{
		return "Vec3(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ", Z:" + StringUtil::to_string(Z) + ")";
	}

	//
	// operators
	//
	bool Vec3::operator==(Vec3 &other) const
	{
		return (X == other.X) && (Y == other.Y) && (Z == other.Z);
	}
	bool Vec3::operator!=(Vec3 &other) const
	{
		return (X != other.X) || (Y != other.Y) || (Z != other.Z);
	}

	Vec3& Vec3::operator+=(Vec3 &other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		return *this;
	}
	Vec3& Vec3::operator-=(Vec3 &other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		return *this;
	}
	Vec3& Vec3::operator*=(Vec3 &other)
	{
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;
		return *this;
	}
	Vec3& Vec3::operator*=(float scale)
	{
		this->scale(scale);
		return *this;
	}

	Vec3 Vec3::operator+(Vec3 &other) const
	{
		return Vec3(X + other.X,
			Y + other.Y,
			Z + other.Z);
	}
	Vec3 Vec3::operator-(Vec3 &other) const
	{
		return Vec3(X - other.X,
			Y - other.Y,
			Z - other.Z);
	}
	Vec3 Vec3::operator*(Vec3 &other) const
	{
		return Vec3(X * other.X,
			Y * other.Y,
			Z * other.Z);
	}
	Vec3 Vec3::operator*(float scale) const
	{
		return Vec3(X * scale, Y * scale, Z * scale);
	}
}}