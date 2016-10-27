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

//__FILE__ is always defined
#ifdef __FILE__
		//Row 1
		property float m11 {
			float get()
			{
				return m_Instance->m11;
			}
			void set(float m11)
			{
				m_Instance->m11 = m11;
			}
		}
		property float m12 {
			float get()
			{
				return m_Instance->m12;
			}
			void set(float m12)
			{
				m_Instance->m12 = m12;
			}
		}
		property float m13 {
			float get()
			{
				return m_Instance->m13;
			}
			void set(float m13)
			{
				m_Instance->m13 = m13;
			}
		}
		property float m14 {
			float get()
			{
				return m_Instance->m14;
			}
			void set(float m14)
			{
				m_Instance->m14 = m14;
			}
		}
		property Vector4^ Row1 {
			Vector4^ get()
			{
				return gcnew Vector4(&m_Instance->Row[0]);
			}
			void set(Vector4^ Row1)
			{
				m_Instance->Row[0] = *Row1->getHandle();
			}
		}

		//Row 2
		property float m21 {
			float get()
			{
				return m_Instance->m21;
			}
			void set(float m21)
			{
				m_Instance->m21 = m21;
			}
		}
		property float m22 {
			float get()
			{
				return m_Instance->m22;
			}
			void set(float m22)
			{
				m_Instance->m22 = m22;
			}
		}
		property float m23 {
			float get()
			{
				return m_Instance->m23;
			}
			void set(float m23)
			{
				m_Instance->m23 = m23;
			}
		}
		property float m24 {
			float get()
			{
				return m_Instance->m24;
			}
			void set(float m24)
			{
				m_Instance->m24 = m24;
			}
		}
		property Vector4^ Row2 {
			Vector4^ get()
			{
				return gcnew Vector4(&m_Instance->Row[1]);
			}
			void set(Vector4^ Row2)
			{
				m_Instance->Row[1] = *Row2->getHandle();
			}
		}

		//Row 3
		property float m31 {
			float get()
			{
				return m_Instance->m31;
			}
			void set(float m31)
			{
				m_Instance->m31 = m31;
			}
		}
		property float m32 {
			float get()
			{
				return m_Instance->m32;
			}
			void set(float m32)
			{
				m_Instance->m32 = m32;
			}
		}
		property float m33 {
			float get()
			{
				return m_Instance->m33;
			}
			void set(float m33)
			{
				m_Instance->m33 = m33;
			}
		}
		property float m34 {
			float get()
			{
				return m_Instance->m34;
			}
			void set(float m34)
			{
				m_Instance->m34 = m34;
			}
		}
		property Vector4^ Row3 {
			Vector4^ get()
			{
				return gcnew Vector4(&m_Instance->Row[2]);
			}
			void set(Vector4^ Row3)
			{
				m_Instance->Row[2] = *Row3->getHandle();
			}
		}

		//Row 4
		property float m41 {
			float get()
			{
				return m_Instance->m41;
			}
			void set(float m41)
			{
				m_Instance->m41 = m41;
			}
		}
		property float m42 {
			float get()
			{
				return m_Instance->m42;
			}
			void set(float m42)
			{
				m_Instance->m42 = m42;
			}
		}
		property float m43 {
			float get()
			{
				return m_Instance->m43;
			}
			void set(float m43)
			{
				m_Instance->m43 = m43;
			}
		}
		property float m44 {
			float get()
			{
				return m_Instance->m44;
			}
			void set(float m44)
			{
				m_Instance->m44 = m44;
			}
		}
		property Vector4^ Row4 {
			Vector4^ get()
			{
				return gcnew Vector4(&m_Instance->Row[3]);
			}
			void set(Vector4^ Row4)
			{
				m_Instance->Row[3] = *Row4->getHandle();
			}
		}
#endif
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
