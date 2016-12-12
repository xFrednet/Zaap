#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Vec3.h>
#include <maths/Vec4.h>

namespace zaap {

	typedef enum ZAAP_API ZA_POINT_RELATION_ {
		ZA_POINT_ABOVE = 0,
		ZA_POINT_ONPLANE = 1,
		ZA_POINT_BELOW = 2
	} ZA_POINT_RELATION;

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
		Plane3D(const float& a, const float& b, const float& c, const float& d);
		Plane3D(const Vec3& n, const float& d);
		Plane3D(const Vec4& p);

		String toString() const;
		
		//util
		inline void  normalize();
		inline bool  isPointOnPlane(const Vec3& point) const;
		inline float getSignedDistance(const Vec3& point) const;
		inline float getUnsignedDistance(const Vec3& point) const;
		inline Vec3  getClosestPoint(const Vec3& point) const;
		inline ZA_POINT_RELATION getRelation(const Vec3& point) const;

		//operators
		inline bool operator==(const Plane3D& other) const;
		inline bool operator!=(const Plane3D& other) const;
	};

	ZAAP_API inline bool Equal(const Plane3D& a, const Plane3D& b);

	ZAAP_API inline Plane3D Normalize(const Plane3D& a);
	ZAAP_API inline bool    IsPointOnPlane(const Plane3D& a, const Vec3& b);
	ZAAP_API inline float   GetSignedDistance(const Plane3D& a, const Vec3& b);
	ZAAP_API inline float   GetUnsignedDistance(const Plane3D& a, const Vec3& b);
	ZAAP_API inline Vec3    GetClosestPoint(const Plane3D& a, const Vec3& b);
	ZAAP_API inline ZA_POINT_RELATION GetRelation(const Plane3D& plane, const Vec3& point);
}
