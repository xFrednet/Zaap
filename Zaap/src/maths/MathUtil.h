#pragma once

#include <Common.h>

#include <maths/Mat4.h>
#include <maths/Vec3.h>

namespace zaap {
	
	//Matrix Math
	void ZAAP_API CreateTransformationMatrix(Mat4* result, const Vec3& position, const Vec3& rotation, const Vec3& scale);

	void ZAAP_API CreateProjectionMatrix(Mat4* result, const float& fov, const float& aspect, const float& nearPlane, const float& farPlane);

	void ZAAP_API CreateViewMatrix(Mat4* result, const Vec3& position, const float& yaw, const float& pitch);
	void ZAAP_API CreateViewMatrix(Mat4* result, const Vec3& position, const Vec3& lookAt, const Vec3& up);

	//Util
	inline float ZAAP_API ToRadians(const float& angdeg);
	inline float ZAAP_API ToDegrees(const float& radians);
	
	// Compute barycentric coordinates for
	// Vec3 point with respect to triangle (a, b, c)
	float ZAAP_API BarycentricY(const Vec3& a, const Vec3& b, const Vec3& c, const Vec2& point);
}