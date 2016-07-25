#include "Bitmap.h"

#include <util/ImageLoader.h>

namespace zaap {
	namespace graphics {
		
		BITMAP::BITMAP(String& file)
		{
			Bytes = ImageLoader::Load(file, &Width, &Height, &BitsPerPixel);
		}
		BITMAP::BITMAP(char* file)
		{
			Bytes = ImageLoader::Load(file, &Width, &Height, &BitsPerPixel);
		}


		BITMAP::~BITMAP()
		{
			delete Bytes;
		}

		uint BITMAP::getR(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width]);
		}
		uint BITMAP::getG(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width + 1]);
		}
		uint BITMAP::getB(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width + 2]);
		}
		uint BITMAP::getA(uint x, uint y) const
		{
			if (x > Width || y >= Height) return 0;
			return uint(Bytes[x + y * Width + 3]);
		}
	}
}