#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Vec3.h>
#include <maths/Vec4.h>

namespace zaap { namespace math {
		
	struct ZAAP_API Mat4
	{
		union
		{
			struct
			{
				float m11, m12, m13, m14;
				float m21, m22, m23, m24;
				float m31, m32, m33, m34;
				float m41, m42, m43, m44;
			};
			float Mat[16];
			Vec4 Row[4];
		};

		Mat4(bool addDiagonal = true);
		Mat4(float diagonal);
		Mat4(Mat4 &mat);
		Mat4(float mat[16]);
		Mat4(Vec4 rows[4]);
		Mat4(const Vec4 &row0, const Vec4 &row1, const Vec4 &row2, const Vec4 &row3);

		//
		// util
		//
		void identity(float value);

		void translate(Vec3 &vec);
		void translate(float x, float y, float z);

		void rotate(float angle, Vec3 &axis);
		void rotate(float angle, float x, float y, float z);

		String toString();

		// operators
		bool operator==(Mat4 &other) const;
		bool operator!=(Mat4 &other) const;

		Mat4& operator+=(Mat4 &other);
		Mat4& operator-=(Mat4 &other);
		Mat4& operator*=(Mat4 &other);
		Mat4& operator*=(float &scale);

		Mat4 operator+(Mat4 &other) const;
		Mat4 operator-(Mat4 &other) const;
		Mat4 operator*(Mat4 &other) const;
		Mat4 operator*(float &scale) const;
	};

}}
