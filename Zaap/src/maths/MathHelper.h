#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Mat4.h>
#include <maths/Vec3.h>


namespace zaap { namespace math {
	
	//Matrix Math
	Mat4 ZAAP_API CreateTransformationMatrix(const Vec3 const &position, const Vec3 const &rotation, const Vec3 const &scale);

	Mat4 ZAAP_API CreateProjectionMatrix(float fovY, float aspect, float nearPlane, float farPlane);

	Mat4 ZAAP_API CreateViewMatrix(Vec3 &position, float yaw, float pitch);
	Mat4 ZAAP_API CreateViewMatrix(Vec3 &position, Vec3 &lookAt, Vec3 &up);

	//Util
	float ZAAP_API toRadians(float angdeg);

	// Compute barycentric coordinates for
	// Vec3 point with respect to triangle (a, b, c)
	float ZAAP_API BarycentricY(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec2 &point);
}}