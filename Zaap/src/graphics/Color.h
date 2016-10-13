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
		float getAccordingFloat(int colorInt) const;
		int getAccordingUint(float colorFloat) const;
	public:
		//constructor
		Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
		Color(Vec4 color);
		Color(Vec3 color, float a = 1.0f);
		Color(int intR, int intG, int intB, int intA = 255);
		Color(int hex);

		//setters
		void setRGB(float r, float g, float b);
		void setRGBA(float r, float g, float b, float a);

		void setRGB(Vec3 rgb);
		void setRGBA(Vec4 rgba);

		void setIntRGB(int r, int g, int b);
		void setIntRGBA(int r, int g, int b, int a);

		//getters
		float getR(void) const;
		float getG(void) const;
		float getB(void) const;
		float getA(void) const;
		Vec3 getRGB(void) const;
		Vec4 getRGBA(void) const;

		int getIntR(void) const;
		int getIntG(void) const;
		int getIntB(void) const;
		int getIntA(void) const;

		String toString(void) const;
	};

}}
