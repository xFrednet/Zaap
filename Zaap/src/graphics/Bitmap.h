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
		private:
			uint getIndex(uint x, uint y) const;
		public:
			byte* Bytes;
			uint Width;
			uint Height;
			uint BitsPerPixel;

			Bitmap();
			Bitmap(uint width, uint height, uint bitsPerPixel);
			Bitmap(char *file);
			Bitmap(String &file);

			~Bitmap();

			//getters
			bool contains(uint x, uint y) const;

			uint getR(uint x, uint y) const;
			uint getG(uint x, uint y) const;
			uint getB(uint x, uint y) const;
			uint getA(uint x, uint y) const;

			Color getColor(uint x, uint y) const;

			Bitmap getSubMap(uint x, uint y, uint width, uint height) const;

			//setters
			void setR(uint x, uint y, uint r);
			void setG(uint x, uint y, uint g);
			void setB(uint x, uint y, uint b);
			void setA(uint x, uint y, uint a);

			void setColor(uint x, uint y, Color color);
		};
	}
}
