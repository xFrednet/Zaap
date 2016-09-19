#include "MathHelper.h"

#include <maths/Maths.h>

namespace zaap { namespace math {
	
	//
	// Matrix math
	//
	Mat4 CreateTransformationMatrix(const Vec3 const &position, const Vec3 const &rotation, const Vec3 const &scale)
	{
		Mat4 mat;
		mat.identity();

		mat.rotate(toRadians(rotation.X), 1.0f, 0.0f, 0.0f);
		mat.rotate(toRadians(rotation.Y), 0.0f, 1.0f, 0.0f);
		mat.rotate(toRadians(rotation.Z), 0.0f, 0.0f, 1.0f);
		mat.scale(scale);
		mat.m41 = position.X;
		mat.m42 = position.Y;
		mat.m43 = position.Z;

		return mat;
	}

	Mat4 CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane)//60
	{
		Mat4 mat;
		mat.identity(1.0f);

		float difference = farPlane - nearPlane;
		float f = atan(fov / 2.0f);

		mat.m11 = f / aspect;
		mat.m22 = f;
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

	Mat4 CreateViewMatrix(Vec3& position, Vec3& lookAt, Vec3& up)
	{
		Vec3 zAxis = Normalize(position - lookAt);
		Vec3 xAxis = Normalize(Cross(up, zAxis));
		Vec3 yAxis = Cross(zAxis, xAxis);

		return Mat4(
			Vec4(xAxis.X, yAxis.X, zAxis.X, 0.0f),
			Vec4(xAxis.Y, yAxis.Y, zAxis.Y, 0.0f),
			Vec4(xAxis.Z, yAxis.Z, zAxis.Z, 0.0f),
			Vec4(-Dot(xAxis, position), -Dot(yAxis, position), -Dot(zAxis, position), 1.0f)
		);
	}

	//
	// Util
	//
	float toRadians(float angdeg)
	{
		return angdeg / 180.0f * PI;
	}

	float BarycentricY(const Vec3& a, const Vec3& b, const Vec3& c, const Vec2 &point)
	{
		float det = (b.Z - c.Z) * (a.X - c.X) + (c.X - b.X) * (a.Z - c.Z);
		float l1 = ((b.Z - c.Z) * (point.X - c.X) + (c.X - b.X) * (point.Y - c.Z)) / det;
		float l2 = ((c.Z - a.Z) * (point.X - c.X) + (a.X - c.X) * (point.Y - c.Z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * a.Y + l2 * b.Y + l3 * c.Y;
	}

}}
