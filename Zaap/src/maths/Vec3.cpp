#include "Vec3.h"
#include <util/Console.h>

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

	Vec3::Vec3(Vec2 vec2, float z)
	{
		X = vec2.X;
		Y = vec2.Y;
		Z = z;
	}

	String Vec3::toString()
	{
		return "Vec3(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ", Z:" + StringUtil::to_string(Z) + ")";
	}

	//
	// Operations
	//
	void Vec3::scale(float scale)
	{
		X *= scale;
		Y *= scale;
		Z *= scale;
	}

	float Vec3::getLength() const
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	void Vec3::normalize()
	{
		float d = getLength();
		X /= d;
		Y /= d;
		Z /= d;
	}

	void Vec3::clamp(float min, float max)
	{
		if (min >= max)
		{
			ZAAP_ALERT("Vec3::clamp: The min Value has to be lower than the max Value");
			return;
		}
		//X
		if (X < min) X = min;
		else if (X > max) X = max;

		//Y
		if (Y < min) Y = min;
		else if (Y > max) Y = max;

		//Z
		if (Z < min) Z = min;
		else if (Z > max) Z = max;
	}

	float Vec3::dot(const Vec3& v) const
	{
		return X * v.X + Y * v.Y + Z * v.Z;
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

	Vec3& Vec3::operator+=(const Vec3 &other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		return *this;
	}
	Vec3& Vec3::operator-=(const Vec3 &other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		return *this;
	}
	Vec3& Vec3::operator*=(const Vec3 &other)
	{
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;
		return *this;
	}
	Vec3& Vec3::operator*=(const float scale)
	{
		this->scale(scale);
		return *this;
	}

	Vec3 Vec3::operator+(const Vec3 &other) const
	{
		return Vec3(X + other.X,
			Y + other.Y,
			Z + other.Z);
	}
	Vec3 Vec3::operator-(const Vec3 &other) const
	{
		return Vec3(X - other.X,
			Y - other.Y,
			Z - other.Z);
	}
	Vec3 Vec3::operator*(const Vec3 &other) const
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
