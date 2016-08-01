#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Vec2.h>
#include <maths/Vec3.h>

namespace zaap { namespace math {

	struct ZAAP_API Vec4
	{
		float X;
		float Y;
		float Z;
		float W;

		Vec4();
		Vec4(float x, float y, float z, float w);
		Vec4(Vec2 vec2, float z, float w);
		Vec4(Vec3 vec3, float w = 0);

		String toString();

		//operations
		void scale(float scale);

		float getLength(void) const;

		void normalize(void);

		void clamp(float min, float max);

		float dot(const Vec4 &v) const;

		// operators
		bool operator==(Vec4 &other) const;
		bool operator!=(Vec4 &other) const;

		Vec4& operator+=(Vec4 &other);
		Vec4& operator-=(Vec4 &other);
		Vec4& operator*=(Vec4 &other);
		Vec4& operator*=(float scale);

		Vec4 operator+(Vec4 &other) const;
		Vec4 operator-(Vec4 &other) const;
		Vec4 operator*(Vec4 &other) const;
		Vec4 operator*(float scale) const;

	};

}}