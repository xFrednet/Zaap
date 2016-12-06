#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Vec2.h>

namespace zaap {
		
	struct ZAAP_API Vec3
	{
		float X;
		float Y;
		float Z;
		
		Vec3();
		Vec3(const float& x, const float& y, const float& z);
		Vec3(const Vec2& vec2, const float& z = 0);

		String toString() const;
		
		// operations
		inline void  normalize();
		inline void  scale(const float& scale);
		inline void  clamp(const float& min, const float& max);
		inline Vec3  cross(const Vec3& other) const;
		inline float dot(const Vec3& v) const;
		inline float getLength() const;
		inline float angleRad(const Vec3& other) const;
		inline float angleDeg(const Vec3& other) const;

		// operators
		inline bool operator==(const Vec3& other) const;
		inline bool operator!=(const Vec3& other) const;

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const Vec3& other);
		Vec3& operator/=(const Vec3& other);

		Vec3& operator*=(const float& value);
		Vec3& operator/=(const float& value);

		inline Vec3 operator+(const Vec3& other) const;
		inline Vec3 operator-(const Vec3& other) const;
		inline Vec3 operator*(const Vec3& other) const;
		inline Vec3 operator/(const Vec3& other) const;

		inline Vec3 operator*(const float& value) const;
		inline Vec3 operator/(const float& value) const;
	};

	//operations
	ZAAP_API inline Vec3 Add(const Vec3& a, const Vec3& b);
	ZAAP_API inline Vec3 Subtract(const Vec3& a, const Vec3& b);
	ZAAP_API inline Vec3 Multiply(const Vec3& a, const Vec3& b);
	ZAAP_API inline Vec3 Divide(const Vec3& a, const Vec3& b);

	ZAAP_API inline Vec3 Multiply(const Vec3& a, const float& b);
	ZAAP_API inline Vec3 Divide(const Vec3& a, const float& b);

	ZAAP_API inline bool Equal(const Vec3& a, const Vec3& b);

	//Util methods
	ZAAP_API inline Vec3  Normalize(const Vec3& a);
	ZAAP_API inline Vec3  Scale(const Vec3& a, const float& scale);
	ZAAP_API inline Vec3  Clamp(const Vec3& a, const float& min, const float& max);
	ZAAP_API inline Vec3  Cross(const Vec3& a, const Vec3& b);
	ZAAP_API inline float Length(const Vec3& a);
	ZAAP_API inline float Dot(const Vec3& a, const Vec3& b);
	ZAAP_API inline float AngleRad(const Vec3& a, const Vec3& b);
	ZAAP_API inline float AngleDeg(const Vec3& a, const Vec3& b);
}