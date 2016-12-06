#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Vec2.h>
#include <maths/Vec3.h>

namespace zaap {

	struct ZAAP_API Vec4
	{
		float X;
		float Y;
		float Z;
		float W;

		Vec4();
		Vec4(const float& x, const float& y, const float& z, const float& w);
		Vec4(const Vec2& vec2, const float& z, const float& w);
		Vec4(const Vec3& vec3, const float& w = 0);

		String toString() const;

		//operations
		inline void  normalize();
		inline void  scale(const float& scale);
		inline void  clamp(const float& min, const float& max);
		inline float dot(const Vec4& v) const;
		inline float getLength() const;

		// operators
		inline bool operator==(Vec4& other) const;
		inline bool operator!=(Vec4& other) const;

		Vec4& operator+=(Vec4& other);
		Vec4& operator-=(Vec4& other);
		Vec4& operator*=(Vec4& other);
		Vec4& operator/=(Vec4& other);

		Vec4& operator*=(const float& value);
		Vec4& operator/=(const float& value);

		inline Vec4 operator+(Vec4& other) const;
		inline Vec4 operator-(Vec4& other) const;
		inline Vec4 operator*(Vec4& other) const;
		inline Vec4 operator/(Vec4& other) const;

		inline Vec4 operator*(const float& value) const;
		inline Vec4 operator/(const float& value) const;

	};

	//operations
	ZAAP_API inline Vec4 Add(const Vec4& a, const Vec4& b);
	ZAAP_API inline Vec4 Subtract(const Vec4& a, const Vec4& b);
	ZAAP_API inline Vec4 Multiply(const Vec4& a, const Vec4& b);
	ZAAP_API inline Vec4 Divide(const Vec4& a, const Vec4& b);

	ZAAP_API inline Vec4 Multiply(const Vec4& a, const float& b);
	ZAAP_API inline Vec4 Divide(const Vec4& a, const float& b);

	ZAAP_API inline bool Equal(const Vec4& a, const Vec4& b);

	//Util methods
	ZAAP_API inline Vec4  Normalize(const Vec4& a);
	ZAAP_API inline Vec4  Scale(const Vec4& a, const float& scale);
	ZAAP_API inline Vec4  Clamp(const Vec4& a, const float& min, const float& max);
	ZAAP_API inline float Dot(const Vec4& a, const Vec4& b);
	ZAAP_API inline float Length(const Vec4& a);
}