#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace math {
	
	struct ZAAP_API Vec4
	{
		float X;
		float Y;
		float Z;
		float W;

		Vec4();
		Vec4(float x, float y, float z, float w);

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