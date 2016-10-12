#include "Bitmap.h"

#include <util/ImageLoader.h>
#include <util/Console.h>

namespace zaap { namespace graphics {
	
	uint Bitmap::getIndex(uint x, uint y) const
	{
		//8 Bits == 1 Byte
		return (x + y * m_Width) * GetFormatSize(m_Format);
	}

	//
	// Constructor
	//
	Bitmap::Bitmap()
		: m_Bytes(0),
		m_Width(0),
		m_Height(0),
		m_Format(ZA_FORMAT_UNKNOWN)
	{
	}
	Bitmap::Bitmap(uint width, uint height, uint bitsPerPixel)
		: m_Bytes(width * height * ((bitsPerPixel == 32) ? 4 : 3)),
		m_Width(width),
		m_Height(height)
	{
		//Format
		if (bitsPerPixel == 32)
			m_Format = ZA_FORMAT_R8G8B8A8_UINT;
		else if (bitsPerPixel == 24)
			m_Format = ZA_FORMAT_R8G8B8_UINT;
		else
			m_Format = ZA_FORMAT_UNKNOWN;
	}
	Bitmap::Bitmap(uint width, uint height, ZA_FORMAT format)
		: m_Bytes(width * height * GetFormatSize(format)),
		m_Width(width),
		m_Height(height),
		m_Format(format)
	{
	}
	Bitmap::Bitmap(const char* file)
		: m_Bytes(0)
	{
		//load the Image
		uint bitsPerPixel;
		byte *bytes = ImageLoader::Load(file, &m_Width, &m_Height, &bitsPerPixel);

		//Format
		if (bitsPerPixel == 32)
			m_Format = ZA_FORMAT_R8G8B8A8_UINT;
		else if (bitsPerPixel == 24)
			m_Format = ZA_FORMAT_R8G8B8_UINT;
		else
			m_Format = ZA_FORMAT_UNKNOWN;

		uint size = m_Width * m_Height * ((bitsPerPixel == 32) ? 4 : 3);

		//copy the pixel bytes
		m_Bytes = std::vector<byte>(size);
		memcpy(&m_Bytes[0], bytes, size);

		delete[] bytes;
	}

	//
	// Color
	//
	uint Bitmap::getR(uint x, uint y) const
	{
		if (!contains(x, y)) return 0;
		return uint(m_Bytes[getIndex(x, y)]);
	}
	uint Bitmap::getG(uint x, uint y) const
	{
		if (!contains(x, y)) return 0;
		return uint(m_Bytes[getIndex(x, y) + 1]);
	}
	uint Bitmap::getB(uint x, uint y) const
	{
		if (!contains(x, y)) return 0;
		return uint(m_Bytes[getIndex(x, y) + 2]);
	}
	uint Bitmap::getA(uint x, uint y) const
	{
		if (m_Format != ZA_FORMAT_R8G8B8A8_UINT) return 255;
		if (!contains(x, y)) return 0;
		return uint(m_Bytes[getIndex(x, y) + 3]);
	}

	void Bitmap::setR(uint x, uint y, uint r)
	{
		if (contains(x, y))
			m_Bytes[getIndex(x, y)] = r;
	}
	void Bitmap::setG(uint x, uint y, uint g)
	{
		if (contains(x, y))
			m_Bytes[getIndex(x, y) + 1] = g;
	}
	void Bitmap::setB(uint x, uint y, uint b)
	{
		if (contains(x, y))
			m_Bytes[getIndex(x, y) + 2] = b;
	}
	void Bitmap::setA(uint x, uint y, uint a)
	{
		if (m_Format == ZA_FORMAT_R8G8B8A8_UINT && contains(x, y))
			m_Bytes[getIndex(x, y) + 3] = a;
	}
	
	Color Bitmap::getColor(uint x, uint y) const
	{
		if (!contains(x, y)) return Color(0.0f, 0.0f, 0.0f, 0.0f);
		uint index = getIndex(x, y);
		Color c = Color(
			(int)m_Bytes[index],
			(int)m_Bytes[index + 1],
			(int)m_Bytes[index + 2],
			(int)m_Bytes[index + 3]);
		return c;
	}

	void Bitmap::setByte(uint index, byte value)
	{
		m_Bytes[index] = value;
	}

	void Bitmap::setColor(uint x, uint y, Color color)
	{
		if (!contains(x, y)) return;
		setR(x, y, uint(color.getIntR()));
		setG(x, y, uint(color.getIntG()));
		setB(x, y, uint(color.getIntB()));
		setA(x, y, uint(color.getIntA()));
	}

	//
	// Getters
	//
	bool Bitmap::contains(uint x, uint y) const
	{
		return (x < m_Width || y < m_Height);
	}

	uint Bitmap::getWidth() const
	{
		return m_Width;
	}
	uint Bitmap::getHeight() const
	{
		return m_Height;
	}
	uint Bitmap::getBitsPerPixel() const
	{
		return GetFormatSize(m_Format) * 8;
	}
	byte const* Bitmap::getPixelArray() const
	{
		return &m_Bytes[0];
	}
	ZA_FORMAT Bitmap::getFormat() const
	{
		return m_Format;
	}


	Bitmap Bitmap::getSubMap(uint x, uint y, uint width, uint height) const
	{
		Bitmap b(width, height, m_Format);

		uint copyWidth = ((x + width) < m_Width) ? width : m_Width - x;
		uint copyHeight = ((y + height) < m_Height) ? height : m_Height - y;

		for (uint yl = 0; yl < copyHeight; yl++)
		{
			for (uint xl = 0; xl < copyWidth; xl++)
			{
				b.setColor(xl, yl, getColor(x + xl, y + yl));
			}
		}

		return b;
	}

}}
