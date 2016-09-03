#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Mat4.h>
#include <maths/Vec3.h>


namespace zaap
{
	namespace math
	{
		Mat4 ZAAP_API CreateTransformationMatrix(const Vec3 const &position, const Vec3 const &rotation, const Vec3 const &scale);

		//fovY aspect
		Mat4 ZAAP_API CreateProjectionMatrix(float fovY, float aspect, float nearPlane, float farPlane);

		Mat4 ZAAP_API CreateViewMatrix(Vec3 &position, float yaw, float pitch);
		Mat4 ZAAP_API CreateViewMatrix(Vec3 &position, Vec3 &lookAt, Vec3 &up);

		float ZAAP_API toRadians(float angdeg);

	}
}