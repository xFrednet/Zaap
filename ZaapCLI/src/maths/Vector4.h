#pragma once

#include <ZaapCLI.h>

#include <maths/Vec4.h>

#include "Vector2.h"
#include "Vector3.h"

namespace ZaapCLI {

	public ref class Vector4 : public ManagedClass<zaap::Vec4>
	{
	private:
	public:
		property float X {
			float get()
			{
				return m_Instance->X;
			}
			void set(float x)
			{
				m_Instance->X = x;
			}
		}
		property float Y {
			float get()
			{
				return m_Instance->Y;
			}
			void set(float y)
			{
				m_Instance->Y = y;
			}
		}
		property float Z {
			float get()
			{
				return m_Instance->Z;
			}
			void set(float z)
			{
				m_Instance->Z = z;
			}
		}
		property float W {
			float get()
			{
				return m_Instance->W;
			}
			void set(float w)
			{
				m_Instance->W = w;
			}
		}

		//Constructors
		Vector4();
		Vector4(zaap::Vec4 *instance);
		Vector4(float x, float y, float z, float w);
		Vector4(Vector2^ vec2, float z, float w);
		Vector4(Vector3^ vec3, float w);

		//operations
		void  normalize();
		void  scale(float scale);
		void  clamp(float min, float max);
		float dot(Vector4^ other);
		float getLength();

		//operators
		bool operator==(Vector4^ other);
		bool operator!=(Vector4^ other);

		Vector4^ operator+=(Vector4^ other);
		Vector4^ operator-=(Vector4^ other);
		Vector4^ operator*=(Vector4^ other);
		Vector4^ operator/=(Vector4^ other);

		Vector4^ operator*=(float value);
		Vector4^ operator/=(float value);

		static Vector4^ operator+(Vector4^ left, Vector4^ right);
		static Vector4^ operator-(Vector4^ left, Vector4^ right);
		static Vector4^ operator*(Vector4^ left, Vector4^ right);
		static Vector4^ operator/(Vector4^ left, Vector4^ right);

		static Vector4^ operator*(Vector4^ left, float right);
		static Vector4^ operator/(Vector4^ left, float right);
	};
}
