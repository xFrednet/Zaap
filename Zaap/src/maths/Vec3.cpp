#include "Vec3.h"
#include <util/Console.h>
#include "Maths.h"

namespace zaap {

	Vec3::Vec3()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}
	Vec3::Vec3(const float &x, const float &y, const float &z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	Vec3::Vec3(const Vec2& vec2, const float &z)
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
	void  Vec3::normalize()
	{
		*this = Normalize(*this);
	}
	void  Vec3::scale(const float &scale)
	{
		*this = Scale(*this, scale);
	}
	void  Vec3::clamp(const float &min, const float &max)
	{
		*this = Clamp(*this, min, max);
	}
	Vec3  Vec3::cross(const Vec3& other) const
	{
		return Cross(*this, other);
	}
	float Vec3::dot(const Vec3& v) const
	{
		return Dot(*this, v);
	}
	float Vec3::getLength() const
	{
		return Length(*this);
	}
	float Vec3::angleRad(const Vec3& other) const
	{
		return AngleRad(*this, other);
	}
	float Vec3::angleDeg(const Vec3& other) const
	{
		return AngleDeg(*this, other);
	}


	//
	// operators
	//
	bool Vec3::operator==(const Vec3 &other) const
	{
		return Equal(*this, other);
	}
	bool Vec3::operator!=(const Vec3 &other) const
	{
		return !Equal(*this, other);
	}

	Vec3& Vec3::operator+=(const Vec3 &other)
	{
		*this = Add(*this, other);
		return *this;
	}
	Vec3& Vec3::operator-=(const Vec3 &other)
	{
		*this = Subtract(*this, other);
		return *this;
	}
	Vec3& Vec3::operator*=(const Vec3 &other)
	{
		*this = Multiply(*this, other);
		return *this;
	}
	Vec3& Vec3::operator/=(const Vec3& other)
	{
		*this = Divide(*this, other);
		return *this;
	}

	Vec3& Vec3::operator*=(const float &value)
	{
		*this = Multiply(*this, value);
		return *this;
	}
	Vec3& Vec3::operator/=(const float &value)
	{
		*this = Multiply(*this, value);
		return *this;
	}

	Vec3 Vec3::operator+(const Vec3 &other) const
	{
		return Add(*this, other);
	}
	Vec3 Vec3::operator-(const Vec3 &other) const
	{
		return Subtract(*this, other);
	}
	Vec3 Vec3::operator*(const Vec3 &other) const
	{
		return Multiply(*this, other);
	}
	Vec3 Vec3::operator/(const Vec3& other) const
	{
		return Divide(*this, other);
	}

	Vec3 Vec3::operator*(const float &scale) const
	{
		return Multiply(*this, scale);
	}
	Vec3 Vec3::operator/(const float &value) const
	{
		return Divide(*this, value);
	}
}
//
// Operations && Util Methods
//
namespace zaap {
	
	//
	// Operations
	//
	Vec3 Add(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.X + b.X,
			a.Y + b.Y,
			a.Z + b.Z);
	}
	Vec3 Subtract(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.X - b.X,
			a.Y - b.Y,
			a.Z - b.Z);
	}
	Vec3 Multiply(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.X * b.X,
			a.Y * b.Y,
			a.Z * b.Z);
	}
	Vec3 Divide(const Vec3& a, const Vec3& b)
	{
		if (b.X == 0 || b.Y == 0 || b.Z == 0)
		{
			ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
			return a;
		}
		return Vec3(a.X / b.X,
			a.Y / b.Y,
			a.Z / b.Z);
	}

	Vec3 Multiply(const Vec3& a, const float &b)
	{
		return Vec3(a.X * b,
			a.Y * b,
			a.Z * b);
	}
	Vec3 Divide(const Vec3& a, const float &b)
	{
		if (b == 0)
		{
			ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
			return a;
		}
		return Vec3(a.X / b,
			a.Y / b,
			a.Z / b);
	}

	bool Equal(const Vec3& a, const Vec3& b)
	{
		return (a.X == b.X) && (a.Y == b.Y) && (a.Z == b.Z);
	}

	//
	// Util Methods
	//
	Vec3  Normalize(const Vec3& vec)
	{
		return Divide(vec, Length(vec));
	}
	Vec3  Scale(const Vec3& vec, const float &scale)
	{
		return Multiply(vec, scale);
	}
	Vec3  Clamp(const Vec3& vec, const float &min, const float &max)
	{
		Vec3 rVec(vec);
		if (min > max)
		{
			ZA_SUBMIT_ERROR(ZA_ERROR_MATH_WRONG_CLAMP_VALUES);
			return rVec;
		}

		//X
		if (rVec.X < min) rVec.X = min;
		else if (rVec.X > max) rVec.X = max;

		//Y
		if (rVec.Y < min) rVec.Y = min;
		else if (rVec.Y > max) rVec.Y = max;

		//Z
		if (rVec.Z < min) rVec.Z = min;
		else if (rVec.Z > max) rVec.Z = max;

		return rVec;
	}
	Vec3  Cross(const Vec3& a, const Vec3& b)
	{
		return Vec3(((a.Y * b.Z) - (a.Z * b.Y)),
			((a.Z * b.X) - (a.X * b.Z)),
			((a.X * b.Y) - (a.Y * b.X)));
	}
	float Length(const Vec3& vec)
	{
		return sqrtf(vec.X * vec.X +
			vec.Y * vec.Y + 
			vec.Z * vec.Z);
	}
	float Dot(const Vec3& vec1, const Vec3& vec2)
	{
		return (vec1.X * vec2.X) +
			(vec1.Y * vec2.Y) +
			(vec1.Z * vec2.Z);
	}
	float AngleRad(const Vec3& a, const Vec3& b)
	{
		return acosf(Dot(a, b) / (Length(a) * Length(b)));
	}
	float AngleDeg(const Vec3& a, const Vec3& b)
	{
		return AngleRad(a, b) * 180.0f / PI;
	}
}
