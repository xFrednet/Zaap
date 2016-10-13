#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap {
		
	struct ZAAP_API Vec2
	{
		float X;
		float Y;
		
		Vec2();
		Vec2(float x, float y);

		String toString();

		//operations
		void scale(float scale);
		
		float getLength(void) const;
		
		void normalize(void);

		void clamp(float min, float max);

		float dot(const Vec2 &v) const;

		// operators
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

}
