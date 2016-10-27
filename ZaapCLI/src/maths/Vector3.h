#pragma once

#include <ZaapCLI.h>

#include <maths/Vec3.h>

#include "Vector2.h"

namespace ZaapCLI {

	public ref class Vector3 : public ManagedClass<zaap::Vec3>
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

			//Constructors
			Vector3();
			Vector3(zaap::Vec3 *instance);
			Vector3(float x, float y, float z);
			Vector3(Vector2^ vec2, float z);

			//operations
			void  scale(float scale);
			float getLength();
			void  normalize();
			void  clamp(float min, float max);
			float dot(Vector3^ v);

			//operators
			bool operator==(Vector3^ other);
			bool operator!=(Vector3^ other);

			Vector3^ operator+=(Vector3^ other);
			Vector3^ operator-=(Vector3^ other);
			Vector3^ operator*=(Vector3^ other);
			Vector3^ operator/=(Vector3^ other);

			static Vector3^ operator+(Vector3^ left, Vector3^ right);
			static Vector3^ operator-(Vector3^ left, Vector3^ right);
			static Vector3^ operator*(Vector3^ left, Vector3^ right);
			static Vector3^ operator/(Vector3^ left, Vector3^ right);
	};

}
