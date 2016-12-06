#include "Mat4.h"

namespace zaap {

	Mat4::Mat4(float diagonal)
	{
		*this = Identify(diagonal);
	}
	Mat4::Mat4(const Mat4& mat)
	{
		memcpy(this,& mat, sizeof(Mat4));
	}
	Mat4::Mat4(float mat[16])
	{
		memcpy(this,& mat[0], sizeof(Mat4));
	}
	Mat4::Mat4(Vec4 rows[4])
	{
		memcpy(this,& rows[0], sizeof(Mat4));
	}
	Mat4::Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3)
	{
		Row[0] = row0;
		Row[1] = row1;
		Row[2] = row2;
		Row[3] = row3;
	}

	String Mat4::toString() const
	{
		return "Mat4(" + Row[0].toString() + ",\n     " +
			Row[1].toString() + ",\n     " +
			Row[2].toString() + ",\n     " +
			Row[3].toString() + ")";
	}

	//
	// util
	//
	void Mat4::identify(const float& value)
	{
		*this = Identify(value);
	}

	void Mat4::translate(const Vec3& vec)
	{
		*this = Traslate(*this, vec);
	}
	void Mat4::translate(const float& x, const float& y, const float& z)
	{
		*this = Traslate(*this, x, y, z);
	}

	void Mat4::rotate(const float& angle, const Vec3& axis)
	{
		*this = Rotate(*this, angle, axis.X, axis.Y, axis.Z);
	}
	void Mat4::rotate(const float& angle, const float& x, const float& y, const float& z)
	{
		*this = Rotate(*this, angle, x, y, z);
	}

	void Mat4::scale(const Vec3& scale)
	{
		*this = Scale(*this, scale.X, scale.Y, scale.Z);
	}
	void Mat4::scale(const float& x, const float& y, const float& z)
	{
		*this = Scale(*this, x, y, z);
	}

	//
	// operators
	//
	bool Mat4::operator==(const Mat4& other) const
	{
		return Equal(*this, other);
	}
	bool Mat4::operator!=(const Mat4& other) const
	{
		return !Equal(*this, other);
	}

	Mat4& Mat4::operator+=(const Mat4& other)
	{
		*this = Add(*this, other);
		return *this;
	}
	Mat4& Mat4::operator-=(const Mat4& other)
	{
		*this = Subtract(*this, other);
		return *this;
	}
	Mat4& Mat4::operator*=(const Mat4& other)
	{
		*this = Multiply(*this, other);
		return *this;
	}

	Mat4& Mat4::operator*=(const float& value)
	{
		*this = Multiply(*this, value);
		return *this;
	}
	Mat4& Mat4::operator/=(const float& value)
	{
		*this = Divide(*this, value);
		return *this;
	}

	Mat4 Mat4::operator+(const Mat4& other) const
	{
		return Add(*this, other);
	}
	Mat4 Mat4::operator-(const Mat4& other) const
	{
		return Subtract(*this, other);
	}
	Mat4 Mat4::operator*(const Mat4& other) const
	{
		return Multiply(*this, other);
	}

	Vec4 Mat4::operator*(const Vec4& other) const
	{
		return Multiply(*this, other);
	}
	Mat4 Mat4::operator*(const float& value) const
	{
		return Multiply(*this, value);
	}
	Mat4 Mat4::operator/(const float& value) const
	{
		return Divide(*this, value);
	}
}

//
// Operations& & Util methods
//
namespace zaap {
	
	//
	// Operations
	//
	Mat4 Add(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			Add(a.Row[0], b.Row[0]),
			Add(a.Row[1], b.Row[1]),
			Add(a.Row[2], b.Row[2]),
			Add(a.Row[3], b.Row[3]));
	}
	Mat4 Subtract(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			Subtract(a.Row[0], b.Row[0]),
			Subtract(a.Row[1], b.Row[1]),
			Subtract(a.Row[2], b.Row[2]),
			Subtract(a.Row[3], b.Row[3]));
	}
	Mat4 Multiply(const Mat4& a, const Mat4& b)
	{
		Mat4 mat;

		int column;
		for (int row = 0; row < 4; row++)
		{
			for (column = 0; column < 4; column++)
			{
				mat.Mat[column + row * 4] =
					a.Mat[row * 4] * b.Mat[column] +
					a.Mat[1 + row * 4] * b.Mat[column + 4] +
					a.Mat[2 + row * 4] * b.Mat[column + 8] +
					a.Mat[3 + row * 4] * b.Mat[column + 12];
			}
		}

		return mat;
	}

	Vec4 Multiply(const Mat4& a, const Vec4& b)
	{
		return Vec4(a.m11 * b.X + a.m21 * b.Y + a.m31 * b.Z + a.m41 * b.W,
			a.m12 * b.X + a.m22 * b.Y + a.m32 * b.Z + a.m42 * b.W,
			a.m13 * b.X + a.m23 * b.Y + a.m33 * b.Z + a.m43 * b.W,
			a.m14 * b.X + a.m24 * b.Y + a.m34 * b.Z + a.m44 * b.W);
	}

	Mat4 Multiply(const Mat4& a, const float& b)
	{
		return Mat4(
			Multiply(a.Row[0], b),
			Multiply(a.Row[1], b),
			Multiply(a.Row[2], b),
			Multiply(a.Row[3], b));
	}
	Mat4 Divide(const Mat4& a, const float& b)
	{
		if (b == 0)
		{
			ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
			return a;
		}
		return Mat4(
			Divide(a.Row[0], b),
			Divide(a.Row[1], b),
			Divide(a.Row[2], b),
			Divide(a.Row[3], b));
	}

	bool Equal(const Mat4& a, const Mat4& b)
	{
		return (memcmp(&a,& b, sizeof(Mat4)) == 0);
	}

	//
	// Util methods
	//
	Mat4 Identify(const float& diagonal)
	{
		return Mat4(
			Vec4(diagonal, 0.0f    , 0.0f    , 0.0f),
			Vec4(0.0f    , diagonal, 0.0f    , 0.0f),
			Vec4(0.0f    , 0.0f    , diagonal, 0.0f),
			Vec4(0.0f    , 0.0f    , 0.0f    , diagonal));
		
	}

	Mat4 Traslate(const Mat4& a, const Vec3& b)
	{
		return Traslate(a, b.X, b.Y, b.Z);
	}
	Mat4 Traslate(const Mat4& a, const float& x, const float& y, const float& z)
	{
		Mat4 b(a);
		
		b.m41 = a.m11 * x + a.m21 * y + a.m31 * z + a.m41;
		b.m42 = a.m12 * x + a.m22 * y + a.m32 * z + a.m42;
		b.m43 = a.m13 * x + a.m23 * y + a.m33 * z + a.m43;
		b.m44 = a.m14 * x + a.m24 * y + a.m34 * z + a.m44;

		return b;
	}

	Mat4 Rotate(const Mat4& a, const float& angle, const Vec3& axis)
	{
		return Rotate(a, angle, axis.X, axis.Y, axis.Z);
	}
	Mat4 Rotate(const Mat4& a, const float& angle, const float& x, const float& y, const float& z)
	{
		Mat4 dest(a);

		float s = sinf(angle);
		float c = cosf(angle);
		float C = 1.0f - c;

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
		dest.m31 = a.m11 * rm31 + a.m21 * rm32 + a.m31 * rm33;
		dest.m32 = a.m12 * rm31 + a.m22 * rm32 + a.m32 * rm33;
		dest.m33 = a.m13 * rm31 + a.m23 * rm32 + a.m33 * rm33;
		dest.m34 = a.m14 * rm31 + a.m24 * rm32 + a.m34 * rm33;
		
		// set other values
		dest.m11 = a.m11 * rm11 + a.m21 * rm12 + a.m31 * rm13;
		dest.m12 = a.m12 * rm11 + a.m22 * rm12 + a.m32 * rm13;
		dest.m13 = a.m13 * rm11 + a.m23 * rm12 + a.m33 * rm13;
		dest.m14 = a.m14 * rm11 + a.m24 * rm12 + a.m34 * rm13;
		dest.m21 = a.m11 * rm21 + a.m21 * rm22 + a.m31 * rm23;
		dest.m22 = a.m12 * rm21 + a.m22 * rm22 + a.m32 * rm23;
		dest.m23 = a.m13 * rm21 + a.m23 * rm22 + a.m33 * rm23;
		dest.m24 = a.m14 * rm21 + a.m24 * rm22 + a.m34 * rm23;
		dest.m41 = a.m41;
		dest.m42 = a.m42;
		dest.m43 = a.m43;
		dest.m44 = a.m44;

		return dest;
	}

	Mat4 Scale(const Mat4& a, const Vec3& scale)
	{
		return Scale(a, scale.X, scale.Y, scale.Z);
	}
	Mat4 Scale(const Mat4& a, const float& x, const float& y, const float& z)
	{
		Mat4 b(a);

		b.Row[0] *= x;
		b.Row[1] *= y;
		b.Row[2] *= z;

		return b;
	}
	
}
