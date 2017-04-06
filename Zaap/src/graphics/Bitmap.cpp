#include "Bitmap.h"

#include <util/ImageLoader.h>
#include "util/Log.h"

namespace zaap { namespace graphics {

	uint Bitmap::getRIndex(const uint &x, const uint &y) const
	{
		switch (m_Format)
		{
			case ZA_FORMAT_R8G8B8A8_UINT:
				return (x + y * m_Width) * 4;
			case ZA_FORMAT_R8G8B8_UINT:
				return (x + y * m_Width) * 3;
			case ZA_FORMAT_R8_UINT:
			case ZA_FORMAT_A8_UINT:
				return (x + y * m_Width);
			default: 
				return 0;
		}
	}
	uint Bitmap::getGIndex(const uint &x, const uint &y) const
	{
		switch (m_Format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return (x + y * m_Width) * 4 + 1;
		case ZA_FORMAT_R8G8B8_UINT:
			return (x + y * m_Width) * 3 + 1;
		case ZA_FORMAT_R8_UINT:
			return 0;
		case ZA_FORMAT_A8_UINT:
			return (x + y * m_Width);
		default:
			return 0;
		}
	}
	uint Bitmap::getBIndex(const uint &x, const uint &y) const
	{
		switch (m_Format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return (x + y * m_Width) * 4 + 2;
		case ZA_FORMAT_R8G8B8_UINT:
			return (x + y * m_Width) * 3 + 2;
		case ZA_FORMAT_R8_UINT:
			return 0;
		case ZA_FORMAT_A8_UINT:
			return (x + y * m_Width);
		default:
			return 0;
		}
	}
	uint Bitmap::getAIndex(const uint &x, const uint &y) const
	{
		switch (m_Format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return (x + y * m_Width) * 4 + 3;
		case ZA_FORMAT_R8G8B8_UINT:
		case ZA_FORMAT_R8_UINT:
			return 0;
		case ZA_FORMAT_A8_UINT:
			return (x + y * m_Width);
		default:
			return 0;
		}
	}

	//
	// Constructor
	//
	Bitmap::Bitmap(const uint &width, const uint &height, const uint &bitsPerPixel)
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
	Bitmap::Bitmap(const uint &width, const uint &height, ZA_FORMAT format)
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
		byte *bytes = nullptr;
		ZA_RESULT result = ImageLoader::Load(file, &m_Width, &m_Height, &bitsPerPixel, &bytes);

		//error test
		if (ZA_FAILED(result))
		{
			ZA_SUBMIT_ERROR(result);
			return;
		}

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
	// RGBA Values
	//
	uint Bitmap::getR(const uint &x, const uint &y) const
	{
		if (!contains(x, y)) return 0;
		if (Format_is_R_Readable(m_Format))
			return uint(m_Bytes[getRIndex(x, y)]);
		
		return 0;
	}
	uint Bitmap::getG(const uint &x, const uint &y) const
	{
		if (!contains(x, y)) return 0;
		if (Format_is_G_Readable(m_Format))
			return uint(m_Bytes[getGIndex(x, y)]);

		return 0;
	}
	uint Bitmap::getB(const uint &x, const uint &y) const
	{
		if (!contains(x, y)) return 0;
		if (Format_is_B_Readable(m_Format))
			return uint(m_Bytes[getBIndex(x, y)]);

		return 0;
	}
	uint Bitmap::getA(const uint &x, const uint &y) const
	{
		if (!contains(x, y)) return 0;
		if (Format_is_A_Readable(m_Format))
			return uint(m_Bytes[getAIndex(x, y)]);

		return 255;
	}

	
	void Bitmap::setR(const uint &x, const uint &y, const uint &r)
	{
		if (Format_is_R_Setable(m_Format) && contains(x, y))
			m_Bytes[getRIndex(x, y)] = r;
	}
	void Bitmap::setG(const uint &x, const uint &y, const uint &g)
	{
		if (Format_is_G_Setable(m_Format) && contains(x, y))
			m_Bytes[getGIndex(x, y)] = g;
	}
	void Bitmap::setB(const uint &x, const uint &y, const uint &b)
	{
		if (Format_is_B_Setable(m_Format) && contains(x, y))
			m_Bytes[getBIndex(x, y)] = b;
	}
	void Bitmap::setA(const uint &x, const uint &y, const uint &a)
	{
		if (Format_is_A_Setable(m_Format) && contains(x, y))
			m_Bytes[getAIndex(x, y)] = a;
	}
	
	//
	// Color
	//
	void Bitmap::setColor(const uint &x, const uint &y, Color color)
	{
		setR(x, y, uint(color.getIntR()));
		setG(x, y, uint(color.getIntG()));
		setB(x, y, uint(color.getIntB()));
		setA(x, y, uint(color.getIntA()));
	}
	Color Bitmap::getColor(const uint &x, const uint &y) const
	{
		if (!contains(x, y)) return Color(0.0f, 0.0f, 0.0f, 255.0f);

		return Color(
			int(m_Bytes[getRIndex(x, y)]),
			int(m_Bytes[getGIndex(x, y)]),
			int(m_Bytes[getBIndex(x, y)]),
			int(m_Bytes[getAIndex(x, y)]));
	}

	//
	// Byte
	//
	void Bitmap::setByte(const uint &index, byte value)
	{
		if (index < m_Bytes.size())
			m_Bytes[index] = value;
	}
	
	//
	// Getters
	//
	bool Bitmap::contains(const uint &x, const uint &y) const
	{
		return (x < m_Width && y < m_Height);
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

	Vec2 Bitmap::getPixelCoord(const uint &x, const uint &y) const
	{
		return Vec2(((float)x / (float)m_Width), (float)y / (float)m_Height);
	}

	Bitmap Bitmap::getSubMap(const uint &x, const uint &y, const uint &width, const uint &height) const
	{
		Bitmap b(width, height, m_Format);

		uint copyWidth = ((x + width) < m_Width) ? width : m_Width - x;
		uint copyHeight = ((y + height) < m_Height) ? height : m_Height - y;

		for (uint yl = 0; yl < copyHeight; yl++)
		{
			for (uint xl = 0; xl < copyWidth; xl++)
			{
				b.setColor(xl, yl, getColor(x + xl, y + yl));//TODO switch to memcpy
			}
		}

		return b;
	}

}}
