#include "Bitmap.h"

#include <util/ImageLoader.h>
#include <util/Console.h>

namespace zaap { namespace graphics {

	uint Bitmap::getIndex(uint x, uint y) const
	{
		if (m_BitsPerPixel == 32) 
			return (x + y * m_Width) * 4;
		if (m_BitsPerPixel == 24)
			return (x + y * m_Width) * 3;

		return (x + y * m_Width) * (m_BitsPerPixel / 8);
	}

	//
	// Constructor
	//
	Bitmap::Bitmap()
		: m_Bytes(0),
		m_Width(0),
		m_Height(0),
		m_BitsPerPixel(0)
	{
	}
	Bitmap::Bitmap(uint width, uint height, uint bitsPerPixel)
		: m_Bytes(width * height * ((bitsPerPixel == 32) ? 4 : 3)),
		m_Width(width),
		m_Height(height),
		m_BitsPerPixel(bitsPerPixel)
	{
	}
	Bitmap::Bitmap(const char* file)
		: m_Bytes(0)
	{
		byte *bytes = ImageLoader::Load(file, &m_Width, &m_Height, &m_BitsPerPixel);

		uint size = m_Width * m_Height * ((m_BitsPerPixel == 32) ? 4 : 3);

		m_Bytes = std::vector<byte>(m_Width * m_Height * ((m_BitsPerPixel == 32) ? 4 : 3));

		memcpy(&m_Bytes[0], bytes, m_Bytes.size());

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
		if (m_BitsPerPixel != 32) return 255;
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
		if (m_BitsPerPixel == 32 && contains(x, y))
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
		return m_BitsPerPixel;
	}

	byte const* Bitmap::getPixelArray() const
	{
		return &m_Bytes[0];
	}

	Bitmap Bitmap::getSubMap(uint x, uint y, uint width, uint height) const
	{
		Bitmap b(width, height, m_BitsPerPixel);

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
