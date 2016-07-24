#include "Mat4.h"

#include <cmath>

namespace zaap { namespace math {
	
	Mat4::Mat4(bool addDiagonal)
	{
		if (addDiagonal)
			identity(0.0f);
		else
			identity(1.0f);
	}
	Mat4::Mat4(float diagonal)
	{
		identity(diagonal);
	}
	Mat4::Mat4(Mat4& mat)
	{
		memcpy(this, &mat, sizeof(Mat4));
	}
	Mat4::Mat4(float mat[16])
	{
		for (int i = 0; i < 16; i++)
		{
			Mat[i] = mat[i];
		}
	}
	Mat4::Mat4(Vec4 rows[4])
	{
		for (int i = 0; i < 4; i++)
		{
			Row[i] = rows[i];
		}
	}
	Mat4::Mat4(const Vec4 &row0, const Vec4 &row1, const Vec4 &row2, const Vec4 &row3)
	{
		Row[0] = row0;
		Row[1] = row1;
		Row[2] = row2;
		Row[3] = row3;
	}

	//
	// util
	//
	void Mat4::identity(float value)
	{
		memset(Mat, 0, 16 * sizeof(float));
		Mat[0] = value;
		Mat[5] = value;
		Mat[10] = value;
		Mat[15] = value;
	}

	void Mat4::translate(Vec3& vec)
	{
		translate(vec.X, vec.Y, vec.Z);
	}
	void Mat4::translate(float x, float y, float z)
	{
		m41 = m11 * x + m21 * y + m31 * z + m41;
		m42 = m12 * x + m22 * y + m32 * z + m42;
		m43 = m13 * x + m23 * y + m33 * z + m43;
		m44 = m14 * x + m24 * y + m34 * z + m44;
	}

	void Mat4::rotate(float angle, Vec3 &axis)
	{
		rotate(angle, axis.X, axis.Y, axis.Z);
	}
	void Mat4::rotate(float angle, float x, float y, float z)
	{
		/*
		float s = sin(angle);
		float c = cos(angle);
		float c1 = 1.0f - c;
		
		//row 0
		float m[16] = {
			(x*x*c1 + c)  , (y*x*c1 - s*z), (z*x*c1 + s*y), m14,
			(x*y*c1 + s*z), (y*y*c1 + c)  , (z*y*c1 - s*x), m24,
			(x*z*c1 - s*y), (y*z*c1 + s*x), (z*z*c1 + c)  , m34,
			m41           , m42           , m43           , m44
		};
		Mat4 mat(m);
		*this = mat;*/
		
		Mat4 dest(*this);

		float s = (float)sin(angle);
		float c = (float)cos(angle);
		float C = 1.0f - c;

		// rotation matrix elements:
		// m40, m41, m43, m04, m14, m34 = 0
		// m44 = 1
		float rm11 = x * x * C + c;
		float rm12 = y * x * C + z * s;
		float rm13 = z * x * C - y * s;
		float rm21 = x * y * C - z * s;
		float rm22 = y * y * C + c;
		float rm23 = z * y * C + x * s;
		float rm31 = x * z * C + y * s;
		float rm32 = y * z * C - x * s;
		float rm33 = z * z * C + c;

		// set non-dependent values directly
		dest.m31 = m11 * rm31 + m21 * rm32 + m31 * rm33;
		dest.m32 = m12 * rm31 + m22 * rm32 + m32 * rm33;
		dest.m33 = m13 * rm31 + m23 * rm32 + m33 * rm33;
		dest.m34 = m14 * rm31 + m24 * rm32 + m34 * rm33;
		// set other values
		dest.m11 = m11 * rm11 + m21 * rm12 + m31 * rm13;
		dest.m12 = m12 * rm11 + m22 * rm12 + m32 * rm13;
		dest.m13 = m13 * rm11 + m23 * rm12 + m33 * rm13;
		dest.m14 = m14 * rm11 + m24 * rm12 + m34 * rm13;
		dest.m21 = m11 * rm21 + m21 * rm22 + m31 * rm23;
		dest.m22 = m12 * rm21 + m22 * rm22 + m32 * rm23;
		dest.m23 = m13 * rm21 + m23 * rm22 + m33 * rm23;
		dest.m24 = m14 * rm21 + m24 * rm22 + m34 * rm23;
		dest.m41 = m41;
		dest.m42 = m42;
		dest.m43 = m43;
		dest.m44 = m44;

		*this = dest;
	}

	String Mat4::toString()
	{
		return "Mat4(" + Row[0].toString() + ",\n     " +
			Row[1].toString() + ",\n     " +
			Row[2].toString() + ",\n     " +
			Row[3].toString() + ")";
	}

	//
	// operators
	//
	bool Mat4::operator==(Mat4 &other) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (Mat[i] != other.Mat[i])
				return false;
		}
		return true;
	}
	bool Mat4::operator!=(Mat4 &other) const
	{
		return !(*this == other);
	}

	Mat4& Mat4::operator+=(Mat4& other)
	{
		*this = *this + other;
		return *this;
	}
	Mat4& Mat4::operator-=(Mat4& other)
	{
		*this = *this - other;
		return *this;
	}
	Mat4& Mat4::operator*=(Mat4& other)
	{
		*this = *this * other;
		return *this;
	}
	Mat4& Mat4::operator*=(float &scale)
	{
		*this = *this * scale;
		return *this;
	}

	Mat4 Mat4::operator+(Mat4 &other) const
	{
		Mat4 mat;
		for (int i = 0; i < 16; i++)
		{
			mat.Mat[i] = Mat[i] + other.Mat[i];
		}
		return mat;
	}
	Mat4 Mat4::operator-(Mat4 &other) const
	{
		Mat4 mat;
		for (int i = 0; i < 16; i++)
		{
			mat.Mat[i] = Mat[i] - other.Mat[i];
		}
		return mat;
	}
	Mat4 Mat4::operator*(Mat4 &other) const
	{
		Mat4 mat4;

		int column;
		for (int row = 0; row < 4; row++)
		{
			for (column = 0; column < 4; column++)
			{
				mat4.Mat[column + row * 4] =
					Mat[row * 4] * other.Mat[column] +
					Mat[1 + row * 4] * other.Mat[column + 4] +
					Mat[2 + row * 4] * other.Mat[column + 8] +
					Mat[3 + row * 4] * other.Mat[column + 12];
			}
		}

		return mat4;
	}
	Mat4 Mat4::operator*(float &scale) const
	{
		Mat4 mat;
		for (int i = 0; i < 16; i++)
		{
			mat.Mat[i] = Mat[i] * scale;
		}
		return mat;
	}
}}