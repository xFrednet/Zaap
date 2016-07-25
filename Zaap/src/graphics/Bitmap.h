#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap
{
	namespace graphics
	{
		struct ZAAP_API BITMAP
		{
		public:
			byte* Bytes;
			uint Width;
			uint Height;
			uint BitsPerPixel;

			BITMAP(char *file);
			BITMAP(String &file);

			~BITMAP();

			uint getR(uint x, uint y) const;
			uint getG(uint x, uint y) const;
			uint getB(uint x, uint y) const;
			uint getA(uint x, uint y) const;

		};
	}
}