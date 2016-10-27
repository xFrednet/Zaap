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
		Vec2(float x, float y);

		String toString() const;

		//operations
		void scale(float scale);
		float getLength(void) const;
		void normalize(void);
		void clamp(float min, float max);
		float dot(const Vec2 &v) const;

		// operators
		bool operator==(const Vec2 &other) const;
		bool operator!=(const Vec2 &other) const;
		
		Vec2& operator+=(const Vec2 &other);
		Vec2& operator-=(const Vec2 &other);
		Vec2& operator*=(const Vec2 &other);
		Vec2& operator/=(const Vec2 &other);

		Vec2& operator*=(float value);
		Vec2& operator/=(float value);

		Vec2 operator+(const Vec2 &other) const;
		Vec2 operator-(const Vec2 &other) const;
		Vec2 operator*(const Vec2 &other) const;
		Vec2 operator/(const Vec2 &other) const;

		Vec2 operator*(float value) const;
		Vec2 operator/(float value) const;

	};

	//operations

	//Util methods
	ZAAP_API Vec2 Add(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2 Subtract(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2 Multiply(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2 Divide(const Vec2 &a, const Vec2 &b);

	ZAAP_API Vec2 Multiply(const Vec2 &a, float b);
	ZAAP_API Vec2 Divide(const Vec2 &a, float b);

	ZAAP_API bool Equal(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2  Scale(const Vec2 &a, float scale);
	ZAAP_API float Length(const Vec2 &a);
	ZAAP_API Vec2  Normalize(const Vec2 &a);
	ZAAP_API Vec2  Clamp(const Vec2 &a, float min, float max);
	ZAAP_API float Dot(const Vec2 &a, const Vec2 &b);
}

