#pragma once

#include <ZaapCLI.h>

#include <graphics/Color.h>

#include <maths/Vector3.h>
#include <maths/Vector4.h>

namespace ZaapCLI {

	public ref class Color : public ManagedClass<zaap::graphics::Color>
	{
	private:
	public:
		ZA_CLI_VALUE(float, R, r);
		ZA_CLI_VALUE(float, G, g);
		ZA_CLI_VALUE(float, B, b);
		ZA_CLI_VALUE(float, A, a);
		ZA_CLI_VECTOR4(RGBA, rgba, RGBA);

		//constructor
		Color();
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
		Color(Vector4^ color);
		Color(Vector3^ color);
		Color(Vector3^ color, float a);
		Color(int intR, int intG, int intB);
		Color(int intR, int intG, int intB, int intA);
		Color(int hex);

		//float setters
		void setRGB(float r, float g, float b);
		void setRGBA(float r, float g, float b, float a);

		void setRGB(Vector3^ rgb);
		void setRGBA(Vector4^ rgba);

		//int setters
		void setIntR(int r);
		void setIntG(int g);
		void setIntB(int b);
		void setIntA(int a);

		float setIntRGB(int r, int g, int b);
		float setIntRGBA(int r, int g, int b, int a);

		//getters
		Vector3^ getRGB();
		Vector4^ getRGBA();

		int getIntR();
		int getIntG();
		int getIntB();
		int getIntA();

		virtual System::String^ ToString() override;
	};
}
