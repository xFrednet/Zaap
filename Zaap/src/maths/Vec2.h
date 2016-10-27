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
		void  normalize();
		void  scale(const float &scale);
		void  clamp(const float &min, const float &max);
		float dot(const Vec2 &v) const;
		float getLength() const;

		// operators
		bool operator==(const Vec2 &other) const;
		bool operator!=(const Vec2 &other) const;
		
		Vec2& operator+=(const Vec2 &other);
		Vec2& operator-=(const Vec2 &other);
		Vec2& operator*=(const Vec2 &other);
		Vec2& operator/=(const Vec2 &other);

		Vec2& operator*=(const float &value);
		Vec2& operator/=(const float &value);

		Vec2 operator+(const Vec2 &other) const;
		Vec2 operator-(const Vec2 &other) const;
		Vec2 operator*(const Vec2 &other) const;
		Vec2 operator/(const Vec2 &other) const;

		Vec2 operator*(const float &value) const;
		Vec2 operator/(const float &value) const;

	};

	//operations
	ZAAP_API Vec2 Add(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2 Subtract(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2 Multiply(const Vec2 &a, const Vec2 &b);
	ZAAP_API Vec2 Divide(const Vec2 &a, const Vec2 &b);

	ZAAP_API Vec2 Multiply(const Vec2 &a, const float &b);
	ZAAP_API Vec2 Divide(const Vec2 &a, const float &b);

	ZAAP_API bool Equal(const Vec2 &a, const Vec2 &b);
	
	//Util methods
	ZAAP_API Vec2  Normalize(const Vec2 &a);
	ZAAP_API Vec2  Scale(const Vec2 &a, const float &scale);
	ZAAP_API Vec2  Clamp(const Vec2 &a, const float &min, const float &max);
	ZAAP_API float Dot(const Vec2 &a, const Vec2 &b);
	ZAAP_API float Length(const Vec2 &a);
}

