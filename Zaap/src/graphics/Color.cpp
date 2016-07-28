#include "Color.h"

namespace zaap { namespace graphics {
	
	//
	// Util
	//
	float Color::getAccordingFloat(int colorInt) const
	{
		if (colorInt < 0) return 0.0f;
		if (colorInt > 255) return 1.0f;

		return (float)colorInt / 255;
	}
	int Color::getAccordingUint(float colorFloat) const
	{
		if (colorFloat < 0) return 0;
		if (colorFloat > 1.0f) return 255;
		return  uint(255.0f * colorFloat);
	}

	//
	// Constructors
	//
	Color::Color(float r, float g, float b, float a)
		: R(r), G(g), B(b), A(a)
	{
	}
	Color::Color(math::Vec4 color)
		: RGBA(color)
	{
	}
	Color::Color(math::Vec3 color, float a)
		: RGBA(color, a)
	{
	}
	Color::Color(int intR, int intG, int intB, int intA)
	{
		setIntRGBA(intR, intG, intB, intA);
	}

	//
	// Setters
	//
	void Color::setRGB(float r, float g, float b)
	{
		setIntRGBA(r, g, b, A);
	}
	void Color::setRGBA(float r, float g, float b, float a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
		RGBA.clamp(0.0f, 1.0f);
	}

	void Color::setRGB(math::Vec3 rgb)
	{
		setIntRGBA(rgb.X, rgb.Y, rgb.Z, A);
	}
	void Color::setRGBA(math::Vec4 rgba)
	{
		setRGBA(rgba.X, rgba.Y, rgba.Z, rgba.W);
	}

	void Color::setIntRGB(int r, int g, int b)
	{
		setRGBA(getAccordingFloat(r), getAccordingFloat(g), getAccordingFloat(b), A);
	}
	void Color::setIntRGBA(int r, int g, int b, int a)
	{
		setRGBA(getAccordingFloat(r), getAccordingFloat(g), getAccordingFloat(b), getAccordingFloat(a));
	}

	//
	// Getters
	//
	float Color::getR() const
	{
		return R;
	}
	float Color::getG() const
	{
		return G;
	}
	float Color::getB() const
	{
		return B;
	}
	float Color::getA() const
	{
		return A;
	}

	math::Vec3 Color::getRGB() const
	{
		return math::Vec3(R, G, B);
	}
	math::Vec4 Color::getRGBA() const
	{
		return RGBA;
	}

	int Color::getIntR() const
	{
		return getAccordingUint(R);
	}
	int Color::getIntG() const
	{
		return getAccordingUint(G);
	}
	int Color::getIntB() const
	{
		return getAccordingUint(B);
	}
	int Color::getIntA() const
	{
		return getAccordingUint(A);
	}

}}
