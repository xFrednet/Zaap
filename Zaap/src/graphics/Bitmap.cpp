#include "Bitmap.h"

#include <util/ImageLoader.h>

namespace zaap { namespace graphics {
		
	uint Bitmap::getIndex(uint x, uint y) const
	{
		if (BitsPerPixel == 32) 
			return (x + y * Width) * 4;
		if (BitsPerPixel == 24)
			return (x + y * Width) * 3;

		return (x + y * Width) * (BitsPerPixel / 8);
	}

	//
	// Constructor
	//
	Bitmap::Bitmap()
	{
		Bytes = nullptr;
		Width = 0;
		Height = 0;
		BitsPerPixel = 0;
	}
	Bitmap::Bitmap(uint width, uint height, uint bitsPerPixel)
		: Width(width),
		Height(height),
		BitsPerPixel(bitsPerPixel)
	{
		uint bitMultiplier = (BitsPerPixel == 32) ? 4 : 3;

		Bytes = new byte[Width * Height * bitMultiplier];
		memset(Bytes, 0, Width * Height * sizeof(byte) * bitMultiplier);
	}
	Bitmap::Bitmap(char* file)
	{
		Bytes = ImageLoader::Load(file, &Width, &Height, &BitsPerPixel);
	}
	Bitmap::Bitmap(String& file)
	{
		Bytes = ImageLoader::Load(file, &Width, &Height, &BitsPerPixel);
	}


	Bitmap::~Bitmap()
	{
		//delete[] Bytes;
	}

	//
	// Getters
	//
	bool Bitmap::contains(uint x, uint y) const
	{
		return (x < Width || y < Height);
	}

	uint Bitmap::getR(uint x, uint y) const
	{
		if (!contains(x, y)) return 0;
		return uint(Bytes[getIndex(x, y)]);
	}
	uint Bitmap::getG(uint x, uint y) const
	{
		if (!contains(x, y)) return 0;
		return uint(Bytes[getIndex(x, y) + 1]);
	}
	uint Bitmap::getB(uint x, uint y) const
	{
		if (!contains(x, y)) return 0;
		return uint(Bytes[getIndex(x, y) + 2]);
	}
	uint Bitmap::getA(uint x, uint y) const
	{
		if (BitsPerPixel != 32) return 255;
		if (!contains(x, y)) return 0;
		return uint(Bytes[getIndex(x, y) + 3]);
	}

	Color Bitmap::getColor(uint x, uint y) const
	{
		if (!contains(x, y)) return Color(0.0f, 0.0f, 0.0f, 0.0f);
		uint index = getIndex(x, y);
		Color c = Color(
			(int)Bytes[index],
			(int)Bytes[index + 1],
			(int)Bytes[index + 2],
			(int)Bytes[index + 3]);
		return c;
	}

	Bitmap Bitmap::getSubMap(uint x, uint y, uint width, uint height) const
	{
		Bitmap b(width, height, BitsPerPixel);

		uint copyWidth = ((x + width) < Width) ? width : Width - x;
		uint copyHeight = ((y + height) < Height) ? height : Height - y;

		for (uint i = 0; i < copyHeight; i++)
		{
			//memcpy(&b.Bytes[i * b.Width * bitMultiplier], &Bytes[getIndex(x, y + i)], copyWidth * bitMultiplier);
		}

		std::vector<Color> colors(width * height);
		Color color;
		for (uint yl = 0; yl < copyHeight; yl++)
		{
			for (uint xl = 0; xl < copyWidth; xl++)
			{
				color = getColor(x + xl, y + yl);
				b.setColor(xl, yl, color);
				//colors[xl + yl * width] = b.getColor(xl, yl);
			}
		}

		return b;
	}

	//
	// Setters
	//
	void Bitmap::setR(uint x, uint y, uint r)
	{
		if (contains(x, y))
			Bytes[getIndex(x, y)] = r;
	}
	void Bitmap::setG(uint x, uint y, uint g)
	{
		if (contains(x, y))
			Bytes[getIndex(x, y) + 1] = g;
	}
	void Bitmap::setB(uint x, uint y, uint b)
	{
		if (contains(x, y))
			Bytes[getIndex(x, y) + 2] = b;
	}
	void Bitmap::setA(uint x, uint y, uint a)
	{
		if (BitsPerPixel == 32 && contains(x, y))
			Bytes[getIndex(x, y) + 3] = a;
	}

	void Bitmap::setColor(uint x, uint y, Color color)
	{
		setR(x, y, uint(color.getIntR()));
		setG(x, y, uint(color.getIntG()));
		setB(x, y, uint(color.getIntB()));
		setA(x, y, uint(color.getIntA()));
	}
}}