﻿#pragma once

#include <ZaapCLI.h>

#include <maths/Vec2.h>

namespace ZaapCLI {

	public ref class Vector2 : public ManagedClass<zaap::Vec2>
	{
		private:
			Vector2(zaap::Vec2* instance);
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

			Vector2();
			Vector2(float x, float y);

			//operations
			void scale(float scale);
			float getLength();
			void normalize();
			void clamp(float min, float max);
			float dot(Vector2^ v);

			//operators 
			bool operator==(Vector2^ other);
			bool operator!=(Vector2^ other);

			Vector2^ operator+=(Vector2^ other);
			Vector2^ operator-=(Vector2^ other);
			Vector2^ operator*=(Vector2^ other);
			Vector2^ operator/=(Vector2^ other);

			static Vector2^ operator+(Vector2^ left, Vector2^ right);
			static Vector2^ operator-(Vector2^ left, Vector2^ right);
			static Vector2^ operator*(Vector2^ left, Vector2^ right);
			static Vector2^ operator/(Vector2^ left, Vector2^ right);
	};

}
