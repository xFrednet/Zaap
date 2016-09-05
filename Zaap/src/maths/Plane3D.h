#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Vec3.h>
#include <maths/Vec4.h>

namespace zaap { namespace math {

	struct ZAAP_API Plane3D
	{

		union
		{
			struct
			{
				float A, B, C;
			};

			Vec3 N;
		};

		float D;

		//constructor
		Plane3D();
		Plane3D(float a, float b, float c, float d);
		Plane3D(Vec3 n, float d);
		Plane3D(Vec4 p);

		//util
		String toString() const;
		void normalize();
		Vec3 getClosestPoint(const Vec3 &point) const;
		float getSignedDistance(const Vec3 &point) const;
		// above   = ZAAP_POINT_ABOVE   = 0
		// below   = ZAAP_POINT_BELOW   = 1
		// onPlane = ZAAP_POINT_ONPLANE = 2
		uint8 getRelation(const Vec3 &point) const;
		bool isPointOnPlane(const Vec3 &point) const;

		//operators
		bool operator==(const Plane3D &other) const;
		bool operator!=(const Plane3D &other) const;
	};

	ZAAP_API Plane3D Normalize(const Plane3D &a);
	ZAAP_API Vec3 GetClosestPoint(const Plane3D &a, const Vec3 &p);
	ZAAP_API float GetSignedDistance(const Plane3D &a, const Vec3 &p);
	ZAAP_API bool IsPointOnPlane(const Plane3D &a, const Vec3 &p);

#define ZAAP_POINT_ABOVE 0
#define ZAAP_POINT_BELOW 1
#define ZAAP_POINT_ONPLANE 2
	// above   = ZAAP_POINT_ABOVE   = 0
	// below   = ZAAP_POINT_BELOW   = 1
	// onPlane = ZAAP_POINT_ONPLANE = 2
	ZAAP_API uint8 GetRelation(const Plane3D& plane, const Vec3& point);
}}
