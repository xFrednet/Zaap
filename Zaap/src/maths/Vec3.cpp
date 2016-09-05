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

	String Vec3::toString() const
	{
		return "Vec3(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ", Z:" + StringUtil::to_string(Z) + ")";
	}

	//
	// Operations
	//
	void Vec3::scale(float scale)
	{
		*this = Scale(*this, scale);
	}

	float Vec3::getLength() const
	{
		return GetLength(*this);
	}

	void Vec3::normalize()
	{
		*this = Normalize(*this);
	}

	void Vec3::clamp(float min, float max)
	{
		*this = Clamp(*this, min, max);
	}

	float Vec3::dot(const Vec3& v) const
	{
		return Dot(*this, v);
	}

	//
	// operators
	//
	bool Vec3::operator==(const Vec3 &other) const
	{
		return (X == other.X) && (Y == other.Y) && (Z == other.Z);
	}
	bool Vec3::operator!=(const Vec3 &other) const
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

//
// Util Methods
//
namespace zaap { namespace math {
	
	Vec3 Scale(const Vec3& vec, float scale)
	{
		return vec * scale;
	}

	float GetLength(const Vec3& vec)
	{
		return sqrtf(vec.X * vec.X +
			vec.Y * vec.Y + 
			vec.Z * vec.Z);
	}

	Vec3 Normalize(const Vec3& vec)
	{
		float d = GetLength(vec);
		return Vec3(vec.X / d, vec.Y / d, vec.Z / d);
	}

	Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		return Vec3(((a.Y * b.Z) - (a.Z * b.Y)),
			((a.Z * b.X) - (a.X * b.Z)),
			((a.X * b.Y) - (a.Y * b.X)));
	}

	Vec3 Clamp(const Vec3& vec, float min, float max)
	{
		Vec3 rVec(vec);
		if (min > max)
		{
			ZAAP_ALERT("Vec3::clamp: The min Value has to be lower than the max Value");
			
			//switch values
			float t = min;
			min = max;
			max = t;
		}

		//X
		if (rVec.X < min) rVec.X = min;
		else if (rVec.X > max) rVec.X = max;

		//Y
		if (rVec.Y < min) rVec.X = min;
		else if (rVec.Y > max) rVec.X = max;

		//Z
		if (rVec.Z < min) rVec.X = min;
		else if (rVec.Z > max) rVec.X = max;

		return rVec;
	}

	float Dot(const Vec3& vec1, const Vec3& vec2)
	{
		return (vec1.X * vec2.X) +
			(vec1.Y * vec2.Y) +
			(vec1.Z * vec2.Z);
	}
}}
