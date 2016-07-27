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

		Mat4 ZAAP_API CreateProjectionMatrix(float nearPlane, float farPlane, float fovX, float fovY);

		Mat4 ZAAP_API CreateViewMatrix(Vec3 &position, float yaw, float pitch);

		float ZAAP_API toRadians(float angdeg);

	}
}