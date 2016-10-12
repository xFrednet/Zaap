#pragma once

#include <Common.h>
#include <Types.h>
#include "Color.h"
#include <graphics/Format.h>

namespace zaap { namespace graphics {

	class ZAAP_API Bitmap
	{
	private:
		std::vector<byte> m_Bytes;
		uint m_Width;
		uint m_Height;
		ZA_FORMAT m_Format;
			
		uint getIndex(uint x, uint y) const;
	public:
		Bitmap();
		Bitmap(uint width, uint height, uint bitsPerPixel);
		Bitmap(uint width, uint height, ZA_FORMAT format);
		Bitmap(const char *file);

		//color
		uint getR(uint x, uint y) const;
		uint getG(uint x, uint y) const;
		uint getB(uint x, uint y) const;
		uint getA(uint x, uint y) const;

		void setR(uint x, uint y, uint r);
		void setG(uint x, uint y, uint g);
		void setB(uint x, uint y, uint b);
		void setA(uint x, uint y, uint a);

		void setColor(uint x, uint y, Color color);
		Color getColor(uint x, uint y) const;
		
		//bit
		void setByte(uint index, byte value);

		//getters
		bool contains(uint x, uint y) const;

		uint getWidth(void) const;
		uint getHeight(void) const;
		uint getBitsPerPixel() const;
		byte const* getPixelArray() const;
		ZA_FORMAT getFormat() const;

		Bitmap getSubMap(uint x, uint y, uint width, uint height) const;
			
	};
}}
