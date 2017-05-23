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
		
		//returns 0 if the channel is not supported
		uint getRIndex(const uint &x, const uint &y) const;
		uint getGIndex(const uint &x, const uint &y) const;
		uint getBIndex(const uint &x, const uint &y) const;
		uint getAIndex(const uint &x, const uint &y) const;
	public:
		Bitmap(const uint &width = 0, const uint &height = 0, const uint &bitsPerPixel = 0);
		Bitmap(const uint &width, const uint &height, ZA_FORMAT format);
		Bitmap(const char *file);

		//RGBA Values
		uint getR(const uint &x, const uint &y) const;
		uint getG(const uint &x, const uint &y) const;
		uint getB(const uint &x, const uint &y) const;
		uint getA(const uint &x, const uint &y) const;

		void setR(const uint &x, const uint &y, const uint &r);
		void setG(const uint &x, const uint &y, const uint &g);
		void setB(const uint &x, const uint &y, const uint &b);
		void setA(const uint &x, const uint &y, const uint &a);

		//color
		void setColor(const uint &x, const uint &y, Color color);
		Color getColor(const uint &x, const uint &y) const;
		
		//byte
		void setByte(const uint &index, byte value);

		//getters
		bool contains(const uint &x, const uint &y) const;

		uint getWidth() const;
		uint getHeight() const;
		uint getBitsPerPixel() const;
		byte const* getPixelArray() const;
		byte* getPixelArray();
		ZA_FORMAT getFormat() const;

		//converts the X and Y values to the Coordinate system from 0.0f - 1.0f
		Vec2 getPixelCoord(const uint &x, const uint &y) const;

		Bitmap getSubMap(const uint &x, const uint &y, const uint &width, const uint &height) const;
			
	};
}}
