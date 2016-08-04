#include "Bitmap.h"

#include <util/ImageLoader.h>

namespace zaap {
	namespace graphics {
		
		Bitmap::Bitmap(String& file)
		{
			Bytes = ImageLoader::Load(file, &Width, &Height, &BitsPerPixel);
		}

		Bitmap::Bitmap()
		{
			Bytes = nullptr;
			Width = 0;
			Height = 0;
			BitsPerPixel = 0;
		}

		Bitmap::Bitmap(char* file)
		{
			Bytes = ImageLoader::Load(file, &Width, &Height, &BitsPerPixel);
		}


		Bitmap::~Bitmap()
		{
			delete[] Bytes;
		}

		uint Bitmap::getR(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width]);
		}
		uint Bitmap::getG(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width + 1]);
		}
		uint Bitmap::getB(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width + 2]);
		}
		uint Bitmap::getA(uint x, uint y) const
		{
			if (BitsPerPixel != 32) return 255;
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width + 3]);
		}

		Color Bitmap::getColor(uint x, uint y) const
		{
			return Color(int(getR(x, y)), int(getG(x, y)), int(getB(x, y)), int(getA(x, y)));
		}
	}
}