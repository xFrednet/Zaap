#pragma once

#include <ZaapCLI.h>

#include <maths/Vec3.h>

#include "Vector2.h"

namespace ZaapCLI {

	public ref class Vector3 : public ManagedClass<zaap::Vec3>
	{
	private:
	public:
		ZA_CLI_VALUE(float, X, x);
		ZA_CLI_VALUE(float, Y, y);
		ZA_CLI_VALUE(float, Z, z);

		//Constructors
		Vector3();
		Vector3(zaap::Vec3 *instance);
		Vector3(float x, float y, float z);
		Vector3(Vector2^ vec2, float z);

		//operations
		void  normalize();
		void  scale(float scale);
		void  clamp(float min, float max);
		Vector3^ cross(Vector3^ other);
		float dot(Vector3^ other);
		float getLength();

		//operators
		bool operator==(Vector3^ other);
		bool operator!=(Vector3^ other);

		Vector3^ operator+=(Vector3^ other);
		Vector3^ operator-=(Vector3^ other);
		Vector3^ operator*=(Vector3^ other);
		Vector3^ operator/=(Vector3^ other);

		Vector3^ operator*=(float value);
		Vector3^ operator/=(float value);

		static Vector3^ operator+(Vector3^ left, Vector3^ right);
		static Vector3^ operator-(Vector3^ left, Vector3^ right);
		static Vector3^ operator*(Vector3^ left, Vector3^ right);
		static Vector3^ operator/(Vector3^ left, Vector3^ right);

		static Vector3^ operator*(Vector3^ left, float right);
		static Vector3^ operator/(Vector3^ left, float right);
	};

}
