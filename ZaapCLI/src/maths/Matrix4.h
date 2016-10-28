#pragma once

#include <ZaapCLI.h>

#include <maths/Mat4.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace ZaapCLI {

	public ref class Matrix4 : public ManagedClass<zaap::Mat4>
	{
	private:
	public:
		//Row 1
		ZA_CLI_VALUE(float, m11, m11);
		ZA_CLI_VALUE(float, m12, m12);
		ZA_CLI_VALUE(float, m13, m13);
		ZA_CLI_VALUE(float, m14, m14);
		ZA_CLI_VECTOR4(Row1, row1, Row[0]);

		//Row 2
		ZA_CLI_VALUE(float, m21, m21);
		ZA_CLI_VALUE(float, m22, m22);
		ZA_CLI_VALUE(float, m23, m23);
		ZA_CLI_VALUE(float, m24, m24);
		ZA_CLI_VECTOR4(Row2, row2, Row[1]);

		//Row 3
		ZA_CLI_VALUE(float, m31, m31);
		ZA_CLI_VALUE(float, m32, m32);
		ZA_CLI_VALUE(float, m33, m33);
		ZA_CLI_VALUE(float, m34, m34);
		ZA_CLI_VECTOR4(Row3, row3, Row[2]);

		//Row 4
		ZA_CLI_VALUE(float, m41, m41);
		ZA_CLI_VALUE(float, m42, m42);
		ZA_CLI_VALUE(float, m43, m43);
		ZA_CLI_VALUE(float, m44, m44);
		ZA_CLI_VECTOR4(Row4, row4, Row[3]);

		//constructors
		Matrix4();
		Matrix4(float diagonal);
		Matrix4(zaap::Mat4 *mat);
		Matrix4(float mat[16]);
		Matrix4(Vector4^ row1, Vector4^ row2, Vector4^ row3, Vector4^ row4);

		//operations
		void identify();
		void identify(float value);

		void translate(Vector3^ vec);
		void translate(float x, float y, float z);

		void rotate(float angle, Vector3^ axis);
		void rotate(float angle, float x, float y, float z);

		void scale(Vector3^ scale);
		void scale(float x, float y, float z);

		// operators
		bool operator==(Matrix4^ other);
		bool operator!=(Matrix4^ other);

		Matrix4^ operator+=(Matrix4^ other);
		Matrix4^ operator-=(Matrix4^ other);
		Matrix4^ operator*=(Matrix4^ other);

		Matrix4^ operator*=(float value);
		Matrix4^ operator/=(float value);

		static Matrix4^ operator+(Matrix4^ left, Matrix4^ right);
		static Matrix4^ operator-(Matrix4^ left, Matrix4^ right);
		static Matrix4^ operator*(Matrix4^ left, Matrix4^ right);

		static Vector4^ operator*(Matrix4^ left, Vector4^ right);
		static Matrix4^ operator*(Matrix4^ left, float value);
		static Matrix4^ operator/(Matrix4^ left, float value);
	};
}
