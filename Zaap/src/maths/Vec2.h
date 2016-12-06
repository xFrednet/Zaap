#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap {
		
	struct ZAAP_API Vec2
	{
		float X;
		float Y;
		
		Vec2();
		Vec2(const Vec2& a);
		Vec2(const float &x, const float &y);

		String toString() const;

		//operations
		inline void  normalize();
		inline void  scale(const float &scale);
		inline void  clamp(const float &min, const float &max);
		inline float dot(const Vec2 &v) const;
		inline float getLength() const;

		// operators
		inline bool operator==(const Vec2 &other) const;
		inline bool operator!=(const Vec2 &other) const;
		
		Vec2& operator+=(const Vec2 &other);
		Vec2& operator-=(const Vec2 &other);
		Vec2& operator*=(const Vec2 &other);
		Vec2& operator/=(const Vec2 &other);

		Vec2& operator*=(const float &value);
		Vec2& operator/=(const float &value);

		inline Vec2 operator+(const Vec2 &other) const;
		inline Vec2 operator-(const Vec2 &other) const;
		inline Vec2 operator*(const Vec2 &other) const;
		inline Vec2 operator/(const Vec2 &other) const;

		inline Vec2 operator*(const float &value) const;
		inline Vec2 operator/(const float &value) const;

	};

	//operations
	ZAAP_API inline Vec2 Add(const Vec2 &a, const Vec2 &b);
	ZAAP_API inline Vec2 Subtract(const Vec2 &a, const Vec2 &b);
	ZAAP_API inline Vec2 Multiply(const Vec2 &a, const Vec2 &b);
	ZAAP_API inline Vec2 Divide(const Vec2 &a, const Vec2 &b);

	ZAAP_API inline Vec2 Multiply(const Vec2 &a, const float &b);
	ZAAP_API inline Vec2 Divide(const Vec2 &a, const float &b);

	ZAAP_API inline bool Equal(const Vec2 &a, const Vec2 &b);
	
	//Util methods
	ZAAP_API inline Vec2  Normalize(const Vec2 &a);
	ZAAP_API inline Vec2  Scale(const Vec2 &a, const float &scale);
	ZAAP_API inline Vec2  Clamp(const Vec2 &a, const float &min, const float &max);
	ZAAP_API inline float Dot(const Vec2 &a, const Vec2 &b);
	ZAAP_API inline float Length(const Vec2 &a);
}

