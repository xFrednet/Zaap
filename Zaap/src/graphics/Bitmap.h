#pragma once

#include <Common.h>
#include <Types.h>
#include "Color.h"

namespace zaap
{
	namespace graphics
	{
		struct ZAAP_API Bitmap
		{
		public:
			byte* Bytes;
			uint Width;
			uint Height;
			uint BitsPerPixel;

			Bitmap();
			Bitmap(char *file);
			Bitmap(String &file);

			~Bitmap();

			uint getR(uint x, uint y) const;
			uint getG(uint x, uint y) const;
			uint getB(uint x, uint y) const;
			uint getA(uint x, uint y) const;

			Color getColor(uint x, uint y) const;

		};
	}
}
