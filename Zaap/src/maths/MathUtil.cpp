#include "MathUtil.h"

#include <maths/Maths.h>

namespace zaap {
	
	//
	// Matrix math
	//
	void CreateTransformationMatrix(Mat4* result, const Vec3& position, const Vec3& rotation, const Vec3& scale)
	{
		result->identify();

		result->rotate(ToRadians(rotation.X), 1.0f, 0.0f, 0.0f);
		result->rotate(ToRadians(rotation.Y), 0.0f, 1.0f, 0.0f);
		result->rotate(ToRadians(rotation.Z), 0.0f, 0.0f, 1.0f);
		result->scale(scale);
		result->m41 = position.X;
		result->m42 = position.Y;
		result->m43 = position.Z;
	}

	void CreateProjectionMatrix(Mat4* result, const float& fov, const float& aspect, const float& nearPlane, const float& farPlane)//60
	{
		result->identify();

		float difference = farPlane - nearPlane;
		float f = atanf(fov / 2.0f);

		result->m11 = f / aspect;
		result->m22 = f;
		result->m33 = -((farPlane + nearPlane) / difference);
		result->m34 = -1;
		result->m43 = -((2 * nearPlane * farPlane) / difference);
		result->m44 = 0;
	}

	void CreateViewMatrix(Mat4* result, const Vec3& position, const float& yaw, const float& pitch)
	{
		result->identify();
		
		result->rotate(ToRadians(pitch), 1, 0, 0);
		result->rotate(ToRadians(yaw), 0, 1, 0);
		result->translate(position * -1);
	}
	void CreateViewMatrix(Mat4* result, const Vec3& position, const Vec3& lookAt, const Vec3& up)
	{
		Vec3 zAxis = Normalize(position - lookAt);
		Vec3 xAxis = Normalize(Cross(up, zAxis));
		Vec3 yAxis = Cross(zAxis, xAxis);

		*result =  Mat4(
			Vec4(xAxis.X, yAxis.X, zAxis.X, 0.0f),
			Vec4(xAxis.Y, yAxis.Y, zAxis.Y, 0.0f),
			Vec4(xAxis.Z, yAxis.Z, zAxis.Z, 0.0f),
			Vec4(-Dot(xAxis, position), -Dot(yAxis, position), -Dot(zAxis, position), 1.0f)
		);
	}

	//
	// Util
	//
	float ToRadians(const float& angdeg)
	{
		return angdeg / 180.0f * ZA_PI;
	}

	float ToDegrees(const float& radians)
	{
		return radians * 180.0f / ZA_PI;
	}

	float BarycentricY(const Vec3& a, const Vec3& b, const Vec3& c, const Vec2& point)
	{
		float det = (b.Z - c.Z) * (a.X - c.X) + (c.X - b.X) * (a.Z - c.Z);
		float l1 = ((b.Z - c.Z) * (point.X - c.X) + (c.X - b.X) * (point.Y - c.Z)) / det;
		float l2 = ((c.Z - a.Z) * (point.X - c.X) + (a.X - c.X) * (point.Y - c.Z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * a.Y + l2 * b.Y + l3 * c.Y;
	}

}
