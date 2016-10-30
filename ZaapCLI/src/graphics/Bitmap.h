#pragma once

#include <ZaapCLI.h>

#include <graphics/Bitmap.h>

#include "Format.h"
#include "Color.h"
#include <maths\Vector2.h>

namespace ZaapCLI {

	public ref class Bitmap : public ManagedClass<zaap::graphics::Bitmap>
	{
	private:
	public:
		Bitmap();
		Bitmap(uint width, uint height, ZA_FORMAT format);
		Bitmap(System::String^ file);
		Bitmap(zaap::graphics::Bitmap* instance);

		//RGBA Values
		uint getR(uint x, uint y);
		uint getG(uint x, uint y);
		uint getB(uint x, uint y);
		uint getA(uint x, uint y);

		void setR(uint x, uint y, uint r);
		void setG(uint x, uint y, uint g);
		void setB(uint x, uint y, uint b);
		void setA(uint x, uint y, uint a);

		//color
		void setColor(uint x, uint y, Color^ color);
		Color^ getColor(uint x, uint y);

		//byte
		void setByte(uint index, byte value);

		//getters
		bool contains(uint x, uint y);

		uint getWidth();
		uint getHeight();
		uint getBitsPerPixel();
		byte* getPixelArray();
		ZA_FORMAT getFormat();

		//converts the X and Y values to the Coordinate system from 0.0f - 1.0f
		Vector2^ getPixelCoord(uint x, uint y);

		Bitmap^ getSubMap(uint x, uint y, uint width, uint height);
	};
}
