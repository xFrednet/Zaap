#include "Vec4.h"
#include <util/Console.h>

namespace zaap {

	Vec4::Vec4()
	{
		X = 0;
		Y = 0;
		Z = 0;
		W = 0;
	}
	Vec4::Vec4(const float& x, const float& y, const float& z, const float& w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
	Vec4::Vec4(const Vec2& vec2, const float& z, const float& w)
	{
		X = vec2.X;
		Y = vec2.Y;
		Z = z;
		W = w;
	}
	Vec4::Vec4(const Vec3& vec3, const float& w)
	{
		X = vec3.X;
		Y = vec3.Y;
		Z = vec3.Z;
		W = w;
	}

	String Vec4::toString() const
	{
		return "Vec4(X:" + StringUtil::to_string(X) + ", Y:" + StringUtil::to_string(Y) + ", Z:" + StringUtil::to_string(Z) + ", W:" + StringUtil::to_string(W) + ")";
	}

	//
	// Operations
	//
	void Vec4::normalize()
	{
		*this = Normalize(*this);
	}
	void Vec4::scale(const float& scale)
	{
		*this = Scale(*this, scale);
	}
	void Vec4::clamp(const float& min, const float& max)
	{
		*this = Clamp(*this, min, max);
	}
	float Vec4::dot(const Vec4& v) const
	{
		return Dot(*this, v);
	}
	float Vec4::getLength() const
	{
		return Length(*this);
	}

	//
	// Operators
	//
	bool Vec4::operator==(Vec4& other) const
	{
		return Equal(*this, other);
	}
	bool Vec4::operator!=(Vec4& other) const
	{
		return !Equal(*this, other);
	}

	Vec4& Vec4::operator+=(Vec4& other)
	{
		*this = Add(*this, other);
		return *this;
	}
	Vec4& Vec4::operator-=(Vec4& other)
	{
		*this = Subtract(*this, other);
		return *this;
	}
	Vec4& Vec4::operator*=(Vec4& other)
	{
		*this = Multiply(*this, other);
		return *this;
	}
	Vec4& Vec4::operator/=(Vec4& other)
	{
		*this = Divide(*this, other);
		return *this;
	}

	Vec4& Vec4::operator*=(const float& value)
	{
		*this = Multiply(*this, value);
		return *this;
	}
	Vec4& Vec4::operator/=(const float& value)
	{
		*this = Divide(*this, value);
		return *this;
	}

	Vec4 Vec4::operator+(Vec4& other) const
	{
		return Add(*this, other);
	}
	Vec4 Vec4::operator-(Vec4& other) const
	{
		return Subtract(*this, other);
	}
	Vec4 Vec4::operator*(Vec4& other) const
	{
		return Multiply(*this, other);
	}
	Vec4 Vec4::operator/(Vec4& other) const
	{
		return Divide(*this, other);
	}

	Vec4 Vec4::operator*(const float& value) const
	{
		return Multiply(*this, value);
	}
	Vec4 Vec4::operator/(const float& value) const
	{
		return Divide(*this, value);
	}

}

//
// Operations& & Util Methods
//
namespace zaap {
	
	//
	// Operations
	//
	Vec4 Add(const Vec4& a, const Vec4& b)
	{
		return Vec4(a.X + b.X,
			a.Y + b.Y,
			a.Z + b.Z,
			a.W + b.W);
	}
	Vec4 Subtract(const Vec4& a, const Vec4& b)
	{
		return Vec4(a.X - b.X,
			a.Y - b.Y,
			a.Z - b.Z,
			a.W - b.W);
	}
	Vec4 Multiply(const Vec4& a, const Vec4& b)
	{
		return Vec4(a.X * b.X,
			a.Y * b.Y,
			a.Z * b.Z,
			a.W * b.W);
	}
	Vec4 Divide(const Vec4& a, const Vec4& b)
	{
		if (b.X == 0 || b.Y == 0 || b.Z == 0 || b.W == 0)
		{
			ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
			return a;
		}
		return Vec4(a.X / b.X,
			a.Y / b.Y,
			a.Z / b.Z,
			a.W / b.W);
	}

	Vec4 Multiply(const Vec4& a, const float& b)
	{
		return Vec4(a.X * b,
			a.Y * b,
			a.Z * b,
			a.W * b);
	}
	Vec4 Divide(const Vec4& a, const float& b)
	{
		if (b == 0)
		{
			ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
			return a;
		}
		return Vec4(a.X / b,
			a.Y / b,
			a.Z / b,
			a.W / b);
	}

	bool Equal(const Vec4& a, const Vec4& b)
	{
		return (a.X == b.X) &&
			(a.Y == b.Y) &&
			(a.Z == b.Z) &&
			(a.W == b.W);
	}

	//
	// Util Methods
	//
	Vec4 Normalize(const Vec4& a)
	{
		return Divide(a, Length(a));
	}
	Vec4 Scale(const Vec4& a, const float& scale)
	{
		return Multiply(a, scale);
	}
	Vec4 Clamp(const Vec4& a, const float& min, const float& max)
	{
		Vec4 rVec(a);
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

		//W
		if (rVec.W < min) rVec.W = min;
		else if (rVec.W > max) rVec.W = max;

		return rVec;
	}
	float Dot(const Vec4& a, const Vec4& b)
	{
		return (a.X * b.X) +
			(a.Y * b.Y) +
			(a.Z * b.Z) +
			(a.W * b.W);
	}
	float Length(const Vec4& a)
	{
		//A^2 = X^2 + Y^2 + Z^2 + W^2
		return sqrtf((a.X * a.X) +
			(a.Y * a.Y) +
			(a.Z * a.Z) +
			(a.W * a.W));
	}
}
