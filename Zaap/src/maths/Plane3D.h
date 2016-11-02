#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Vec3.h>
#include <maths/Vec4.h>

namespace zaap {

	typedef enum ZAAP_API {
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
		Plane3D(const float &a, const float &b, const float &c, const float &d);
		Plane3D(const Vec3 &n, const float &d);
		Plane3D(const Vec4 &p);

		String toString() const;
		
		//util
		void  normalize();
		bool  isPointOnPlane(const Vec3 &point) const;
		float getSignedDistance(const Vec3 &point) const;
		ZA_POINT_RELATION getRelation(const Vec3 &point) const;

		//operators
		bool operator==(const Plane3D &other) const;
		bool operator!=(const Plane3D &other) const;
	};

	ZAAP_API bool Equal(const Plane3D &a, const Plane3D &b);

	ZAAP_API Plane3D Normalize(const Plane3D &a);
	ZAAP_API bool    IsPointOnPlane(const Plane3D &a, const Vec3 &p);
	ZAAP_API float   GetSignedDistance(const Plane3D &a, const Vec3 &p);
	ZAAP_API ZA_POINT_RELATION GetRelation(const Plane3D& plane, const Vec3& point);
}
