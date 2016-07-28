#include "Vec4.h"
#include <util/Console.h>

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
	Vec4::Vec4(Vec2 vec2, float z, float w)
	{
		X = vec2.X;
		Y = vec2.Y;
		Z = z;
		W = w;
	}
	Vec4::Vec4(Vec3 vec3, float w)
	{
		X = vec3.X;
		Y = vec3.Y;
		Z = vec3.Z;
		W = w;
	}

	String Vec4::toString()
	{
		return "Vec4(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ", Z:" + StringUtil::to_string(Z) + ", W:" + StringUtil::to_string(W) + ")";
	}

	//
	// Operations
	//
	void Vec4::scale(float scale)
	{
		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
	}

	float Vec4::getLength() const
	{
		return sqrtf(X * X + Y * Y + Z * Z + W * W);
	}

	void Vec4::normalize()
	{
		float d = getLength();
		X /= d;
		Y /= d;
		Z /= d;
		W /= d;
	}

	void Vec4::clamp(float min, float max)
	{
		if (min >= max)
		{
			ZAAP_ALERT("Vec4::clamp: The min Value has to be lower than the max Value");
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

		//W
		if (W < min) W = min;
		else if (W > max) W = max;
	}

	float Vec4::dot(const Vec4& v) const
	{
		return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
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
