#include "MathHelper.h"

#include <maths/Maths.h>

namespace zaap { namespace math {
	
	Mat4 CreateTransformationMatrix(const Vec3 const &position, const Vec3 const &rotation, const float const &scale)
	{
		Mat4 mat;
		mat.identity(scale);

		mat.rotate(toRadians(rotation.X), 1.0f, 0.0f, 0.0f);
		mat.rotate(toRadians(rotation.Y), 0.0f, 1.0f, 0.0f);
		mat.rotate(toRadians(rotation.Z), 0.0f, 0.0f, 1.0f);
		mat.m41 = position.X;
		mat.m42 = position.Y;
		mat.m43 = position.Z;

		return mat;
	}

	Mat4 CreateProjectionMatrix(float nearPlane, float farPlane, float fovX, float fovY)
	{
		Mat4 mat;
		mat.identity(1.0f);

		float difference = farPlane - nearPlane;
		
		mat.m11 = atan(fovX / 2);
		mat.m22 = atan(fovY / 2);
		mat.m33 = -((farPlane + nearPlane) / difference);
		mat.m34 = -1;
		mat.m43 = -((2 * nearPlane * farPlane) / difference);
		mat.m44 = 0;

		return mat;
	}

	Mat4 CreateViewMatrix(Vec3& position, float yaw, float pitch)
	{
		Mat4 mat(1.0f);
		
		mat.rotate(toRadians(pitch), 1, 0, 0);
		mat.rotate(toRadians(yaw), 0, 1, 0);
		mat.translate(position * -1);

		return mat;
	}

	float toRadians(float angdeg)
	{
		return angdeg / 180.0f * PI;
	}
}}
