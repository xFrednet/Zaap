#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace math	{
		
	struct ZAAP_API Vec3
	{
		float X;
		float Y;
		float Z;
		
		Vec3();
		Vec3(float x, float y, float z);

		void scale(float scale);

		String toString();

		//
		// operators
		//
		bool operator==(Vec3 &other) const;
		bool operator!=(Vec3 &other) const;

		Vec3& operator+=(Vec3 &other);
		Vec3& operator-=(Vec3 &other);
		Vec3& operator*=(Vec3 &other);
		Vec3& operator*=(float scale);

		Vec3 operator+(Vec3 &other) const;
		Vec3 operator-(Vec3 &other) const;
		Vec3 operator*(Vec3 &other) const;
		Vec3 operator*(float scale) const;
	};

}}