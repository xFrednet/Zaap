#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Mat4.h>
#include <maths/Vec3.h>


namespace zaap {
	
	//Matrix Math
	Mat4 ZAAP_API CreateTransformationMatrix(const Vec3 &position, const Vec3 &rotation, const Vec3 &scale);

	Mat4 ZAAP_API CreateProjectionMatrix(const float &fov, const float &aspect, const float &nearPlane, const float &farPlane);

	Mat4 ZAAP_API CreateViewMatrix(const Vec3 &position, const float yaw, const float pitch);
	Mat4 ZAAP_API CreateViewMatrix(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up);

	//Util
	float ZAAP_API toRadians(const float &angdeg);

	// Compute barycentric coordinates for
	// Vec3 point with respect to triangle (a, b, c)
	float ZAAP_API BarycentricY(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec2 &point);
}