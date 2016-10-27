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
		Vec3(const float &x, const float &y, const float &z);
		Vec3(Vec2 vec2, const float &z = 0);

		String toString() const;
		
		// operations
		void  normalize();
		void  scale(const float &scale);
		void  clamp(const float &min, const float &max);
		Vec3  cross(const Vec3 &other) const;
		float dot(const Vec3 &v) const;
		float getLength() const;

		// operators
		bool operator==(const Vec3 &other) const;
		bool operator!=(const Vec3 &other) const;

		Vec3& operator+=(const Vec3 &other);
		Vec3& operator-=(const Vec3 &other);
		Vec3& operator*=(const Vec3 &other);
		Vec3& operator/=(const Vec3 &other);

		Vec3& operator*=(const float &value);
		Vec3& operator/=(const float &value);

		Vec3 operator+(const Vec3 &other) const;
		Vec3 operator-(const Vec3 &other) const;
		Vec3 operator*(const Vec3 &other) const;
		Vec3 operator/(const Vec3 &other) const;

		Vec3 operator*(const float &value) const;
		Vec3 operator/(const float &value) const;
	};

	//operations
	ZAAP_API Vec3 Add(const Vec3 &a, const Vec3 &b);
	ZAAP_API Vec3 Subtract(const Vec3 &a, const Vec3 &b);
	ZAAP_API Vec3 Multiply(const Vec3 &a, const Vec3 &b);
	ZAAP_API Vec3 Divide(const Vec3 &a, const Vec3 &b);

	ZAAP_API Vec3 Multiply(const Vec3 &a, const float &b);
	ZAAP_API Vec3 Divide(const Vec3 &a, const float &b);

	ZAAP_API bool Equal(const Vec3 &a, const Vec3 &b);

	//Util methods
	ZAAP_API Vec3  Normalize(const Vec3 &a);
	ZAAP_API Vec3  Scale(const Vec3 &a, const float &scale);
	ZAAP_API Vec3  Clamp(const Vec3 &a, const float &min, const float &max);
	ZAAP_API Vec3  Cross(const Vec3 &a, const Vec3 &b);
	ZAAP_API float Length(const Vec3 &a);
	ZAAP_API float Dot(const Vec3 &a, const Vec3 &b);

}