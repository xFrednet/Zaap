#include "Bitmap.h"

namespace ZaapCLI {

	Bitmap::Bitmap()
		: ManagedClass(new zaap::graphics::Bitmap())
	{
	}
	Bitmap::Bitmap(uint width, uint height, ZA_FORMAT format)
		: ManagedClass(new zaap::graphics::Bitmap(width, height, format))
	{
	}
	Bitmap::Bitmap(System::String^ file)
		: ManagedClass(new zaap::graphics::Bitmap(to_CPP_String(file)))
	{
	}
	Bitmap::Bitmap(zaap::graphics::Bitmap* instance)
		: ManagedClass(instance)
	{
	}

	//RGBA Values
	uint Bitmap::getR(uint x, uint y)
	{
		return m_Instance->getR(x, y);
	}
	uint Bitmap::getG(uint x, uint y)
	{
		return m_Instance->getG(x, y);
	}
	uint Bitmap::getB(uint x, uint y)
	{
		return m_Instance->getB(x, y);
	}
	uint Bitmap::getA(uint x, uint y)
	{
		return m_Instance->getA(x, y);
	}

	void Bitmap::setR(uint x, uint y, uint r)
	{
		m_Instance->setR(x, y, r);
	}
	void Bitmap::setG(uint x, uint y, uint g)
	{
		m_Instance->setG(x, y, g);
	}
	void Bitmap::setB(uint x, uint y, uint b)
	{
		m_Instance->setB(x, y, b);
	}
	void Bitmap::setA(uint x, uint y, uint a)
	{
		m_Instance->setA(x, y, a);
	}

	//color
	void Bitmap::setColor(uint x, uint y, Color^ color)
	{
		m_Instance->setColor(x, y, *color->getHandle());
	}
	Color^ Bitmap::getColor(uint x, uint y)
	{
		return gcnew Color(&m_Instance->getColor(x, y));
	}

	//byte
	void Bitmap::setByte(uint index, byte value)
	{
		m_Instance->setByte(index, value);
	}

	//getters
	bool Bitmap::contains(uint x, uint y)
	{
		return m_Instance->contains(x, y);
	}

	uint Bitmap::getWidth()
	{
		return m_Instance->getWidth();
	}
	uint Bitmap::getHeight()
	{
		return m_Instance->getHeight();
	}
	uint Bitmap::getBitsPerPixel()
	{
		return m_Instance->getBitsPerPixel();
	}
	byte* Bitmap::getPixelArray()
	{
		m_Instance->getPixelArray();
	}
	ZA_FORMAT Bitmap::getFormat()
	{
		return to_CLI_ZAFormat(m_Instance->getFormat());
	}

	//converts the X and Y values to the Coordinate system from 0.0f - 1.0f
	Vector2^ Bitmap::getPixelCoord(uint x, uint y)
	{
		return gcnew Vector2(&m_Instance->getPixelCoord(x, y));
	}

	Bitmap^ Bitmap::getSubMap(uint x, uint y, uint width, uint height)
	{
		return gcnew Bitmap(&m_Instance->getSubMap(x, y, width, height));
	}
}
