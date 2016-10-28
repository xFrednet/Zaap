#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {
	
	struct ZAAP_API Color
	{
		union
		{
			struct
			{
				float R;
				float G;
				float B;
				float A;
			};
			
			Vec4 RGBA;
		};

	private:
		static float GetAccordingFloat(const int &colorInt);
		static int GetAccordingInt(const float &colorFloat);
	public:
		//constructors
		Color(const float &r = 0.0f, const float &g = 0.0f, const float &b = 0.0f, const float &a = 1.0f);
		Color(const Vec4 &color);
		Color(const Vec3 &color, const float &a = 1.0f);
		Color(const int &intR, const int &intG, const int &intB, const int &intA = 255);
		Color(const int &hex);

		//setters
		void setRGB(const float &r, const float &g, const float &b);
		void setRGBA(const float &r, const float &g, const float &b, const float &a);

		void setRGB(const Vec3 &rgb);
		void setRGBA(const Vec4 &rgba);

		//int setters
		void setIntR(const int &r);
		void setIntG(const int &g);
		void setIntB(const int &b);
		void setIntA(const int &a);

		void setIntRGB(const int &r, const int &g, const int &b);
		void setIntRGBA(const int &r, const int &g, const int &b, const int &a);

		//getters
		Vec3 getRGB(void) const;
		Vec4 getRGBA(void) const;

		int getIntR(void) const;
		int getIntG(void) const;
		int getIntB(void) const;
		int getIntA(void) const;

		String toString(void) const;
	};

}}
