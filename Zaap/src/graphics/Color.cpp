#include "Color.h"

namespace zaap { namespace graphics {
	
	//
	// Util
	//
	float Color::GetAccordingFloat(const int &colorInt)
	{
		if (colorInt < 0) return 0.0f;
		if (colorInt > 255) return 1.0f;

		return (const float &)colorInt / 255;
	}
	int Color::GetAccordingInt(const float &colorFloat)
	{
		if (colorFloat < 0) return 0;
		if (colorFloat > 1.0f) return 255;
		return  uint(255.0f * colorFloat);
	}

	//
	// Constructors
	//
	Color::Color(const float &r, const float &g, const float &b, const float &a)
		: R(r), G(g), B(b), A(a)
	{
		RGBA.clamp(0.0f, 1.0f);
	}
	Color::Color(const Vec4 &color)
		: RGBA(color)
	{
		RGBA.clamp(0.0f, 1.0f);
	}
	Color::Color(const Vec3 &color, const float &a)
		: RGBA(color, a)
	{
		RGBA.clamp(0.0f, 1.0f);
	}
	Color::Color(const int &intR, const int &intG, const int &intB, const int &intA)
	{
		setIntRGBA(intR, intG, intB, intA);
	}
	Color::Color(const int &hex)
	{
		R = ((hex >> 16) &0xFF) / 255.0f;  // Extract the RR byte
		G = ((hex >> 8) &0xFF) / 255.0f;   // Extract the GG byte
		B = ((hex) &0xFF) / 255.0f;        // Extract the BB byte
		A = 1.0f;
		RGBA.clamp(0.0f, 1.0f);
	}

	//
	// Setters
	//
	void Color::setRGB(const float &r, const float &g, const float &b)
	{
		setRGBA(r, g, b, A);
	}
	void Color::setRGBA(const float &r, const float &g, const float &b, const float &a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
		RGBA.clamp(0.0f, 1.0f);
	}

	void Color::setRGB(const Vec3 &rgb)
	{
		setRGBA(rgb.X, rgb.Y, rgb.Z, A);
	}
	void Color::setRGBA(const Vec4 &rgba)
	{
		setRGBA(rgba.X, rgba.Y, rgba.Z, rgba.W);
	}

	void Color::setIntRGB(const int &r, const int &g, const int &b)
	{
		setRGBA(GetAccordingFloat(r), GetAccordingFloat(g), GetAccordingFloat(b), A);
	}
	void Color::setIntRGBA(const int &r, const int &g, const int &b, const int &a)
	{
		setRGBA(GetAccordingFloat(r), GetAccordingFloat(g), GetAccordingFloat(b), GetAccordingFloat(a));
	}

	void Color::setIntR(const int& r)
	{
		R = GetAccordingFloat(r);
	}
	void Color::setIntG(const int& g)
	{
		R = GetAccordingFloat(g);
	}
	void Color::setIntB(const int& b)
	{
		R = GetAccordingFloat(b);
	}
	void Color::setIntA(const int& a)
	{
		R = GetAccordingFloat(a);
	}

	//
	// Getters
	//
	Vec3 Color::getRGB() const
	{
		return Vec3(R, G, B);
	}
	Vec4 Color::getRGBA() const
	{
		return RGBA;
	}

	int Color::getIntR() const
	{
		return GetAccordingInt(R);
	}
	int Color::getIntG() const
	{
		return GetAccordingInt(G);
	}
	int Color::getIntB() const
	{
		return GetAccordingInt(B);
	}
	int Color::getIntA() const
	{
		return GetAccordingInt(A);
	}

	String Color::toString() const
	{
		return "Color(R " + std::to_string(getIntR()) +
			", G " + std::to_string(getIntG()) +
			", B " + std::to_string(getIntB()) +
			", A " + std::to_string(getIntA()) + ")";
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	bool Color::operator==(const Color& other) const
	{
		return Equal(*this, other);
	}

	bool Color::operator!=(const Color& other) const
	{
		return !Equal(*this, other);
	}

	bool Equal(const Color& a, const Color& b)
	{
		return Equal(a.RGBA, b.RGBA);
	}
}}
