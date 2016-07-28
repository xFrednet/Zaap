#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Vec2.h>

namespace zaap { namespace math	{
		
	struct ZAAP_API Vec3
	{
		float X;
		float Y;
		float Z;
		
		Vec3();
		Vec3(float x, float y, float z);
		Vec3(Vec2 vec2, float z);

		String toString();
		
		// operations
		void scale(float scale);
		
		float getLength(void) const;

		void normalize(void);

		void clamp(float min, float max);

		float dot(const Vec3 &v) const;

		// operators
		bool operator==(Vec3 &other) const;
		bool operator!=(Vec3 &other) const;

		Vec3& operator+=(const Vec3 &other);
		Vec3& operator-=(const Vec3 &other);
		Vec3& operator*=(const Vec3 &other);
		Vec3& operator*=(const float scale);

		Vec3 operator+(const Vec3 &other) const;
		Vec3 operator-(const Vec3 &other) const;
		Vec3 operator*(const Vec3 &other) const;
		Vec3 operator*(const float scale) const;
	};

}}