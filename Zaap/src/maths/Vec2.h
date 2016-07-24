#pragma once

#include "Common.h"
#include "Types.h"

namespace zaap { namespace math {
		
	struct ZAAP_API Vec2
	{
		
		float X;
		float Y;
		
		Vec2();
		Vec2(float x, float y);

		void scale(float scale);

		String toString();

		//
		// operators
		//
		bool operator==(Vec2 &other) const;
		bool operator!=(Vec2 &other) const;
		
		Vec2& operator+=(Vec2 &other);
		Vec2& operator-=(Vec2 &other);
		Vec2& operator*=(Vec2 &other);
		Vec2& operator*=(float scale);

		Vec2 operator+(Vec2 &other) const;
		Vec2 operator-(Vec2 &other) const;
		Vec2 operator*(Vec2 &other) const;
		Vec2 operator*(float scale) const;

	};

}}
