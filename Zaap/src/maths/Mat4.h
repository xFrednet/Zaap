#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Vec3.h>
#include <maths/Vec4.h>

namespace zaap {
		
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

		Mat4(float diagonal = 1.0f);
		Mat4(const Mat4 &mat);
		Mat4(float mat[16]);
		Mat4(Vec4 rows[4]);
		Mat4(const Vec4 &row0, const Vec4 &row1, const Vec4 &row2, const Vec4 &row3);

		String toString() const;
		//
		// util
		//
		void identify(const float &value = 1.0f);

		void translate(const Vec3 &vec);
		void translate(const float &x, const float &y, const float &z);

		void rotate(const float &angle, const Vec3 &axis);
		void rotate(const float &angle, const float &x, const float &y, const float &z);

		void scale(const Vec3& scale);
		void scale(const float &x, const float &y, const float &z);

		// operators
		bool operator==(const Mat4 &other) const;
		bool operator!=(const Mat4 &other) const;

		Mat4& operator+=(const Mat4 &other);
		Mat4& operator-=(const Mat4 &other);
		Mat4& operator*=(const Mat4 &other);

		Mat4& operator*=(const float &value);
		Mat4& operator/=(const float &value);

		Mat4 operator+(const Mat4 &other) const;
		Mat4 operator-(const Mat4 &other) const;
		Mat4 operator*(const Mat4 &other) const;

		Vec4 operator*(const Vec4 &other) const;
		Mat4 operator*(const float &value) const;
		Mat4 operator/(const float &value) const;
	};

	//operations
	ZAAP_API Mat4 Add(const Mat4 &a, const Mat4 &b);
	ZAAP_API Mat4 Subtract(const Mat4 &a, const Mat4 &b);
	ZAAP_API Mat4 Multiply(const Mat4 &a, const Mat4 &b);
	
	ZAAP_API Vec4 Multiply(const Mat4 &a, const Vec4 &b);

	ZAAP_API Mat4 Multiply(const Mat4 &a, const float &b);
	ZAAP_API Mat4 Divide(const Mat4 &a, const float &b);

	ZAAP_API bool Equal(const Mat4 &a, const Mat4 &b);

	//operations 
	ZAAP_API Mat4 Identify(const float &diagonal);
	ZAAP_API Mat4 Traslate(const Mat4 &a, const Vec3 &b);
	ZAAP_API Mat4 Traslate(const Mat4 &a, const float &x, const float &y, const float &z);
	ZAAP_API Mat4 Rotate(const Mat4 &a, const float &angle, const Vec3 &axis);
	ZAAP_API Mat4 Rotate(const Mat4 &a, const float &angle, const float &x, const float &y, const float &z);
	ZAAP_API Mat4 Scale(const Mat4 &a, const Vec3& scale);
	ZAAP_API Mat4 Scale(const Mat4 &a, const float &x, const float &y, const float &z);
}
