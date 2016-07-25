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

		void scale(float scale);

		String toString();

		//
		// operators
		//
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