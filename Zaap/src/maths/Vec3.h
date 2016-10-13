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
		Vec3(float x, float y, float z);
		Vec3(Vec2 vec2, float z);

		String toString() const;
		
		// operations
		void scale(float scale);
		float getLength(void) const;
		void normalize(void);
		void clamp(float min, float max);
		float dot(const Vec3 &v) const;

		// operators
		bool operator==(const Vec3 &other) const;
		bool operator!=(const Vec3 &other) const;

		Vec3& operator+=(const Vec3 &other);
		Vec3& operator-=(const Vec3 &other);
		Vec3& operator*=(const Vec3 &other);
		Vec3& operator*=(const float scale);

		Vec3 operator+(const Vec3 &other) const;
		Vec3 operator-(const Vec3 &other) const;
		Vec3 operator*(const Vec3 &other) const;
		Vec3 operator*(const float scale) const;
	};

	//Util methods
	ZAAP_API Vec3  Scale(const Vec3 &a, float scale);
	ZAAP_API float GetLength(const Vec3 &a);
	ZAAP_API Vec3  Normalize(const Vec3 &a);
	ZAAP_API Vec3  Cross(const Vec3 &a, const Vec3 &b);
	ZAAP_API Vec3  Clamp(const Vec3 &a, float min, float max);
	ZAAP_API float Dot(const Vec3 &a, const Vec3 &b);

}