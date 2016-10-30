#include "Color.h"

namespace ZaapCLI {
	
	//
	//constructors
	//
	Color::Color()
		: ManagedClass(new zaap::graphics::Color())
	{
	}
	Color::Color(zaap::graphics::Color* color)
		: ManagedClass(color)
	{
	}
	Color::Color(float r, float g, float b) 
		: ManagedClass(new zaap::graphics::Color(r, g, b))
	{
	}
	Color::Color(float r, float g, float b, float a)
		: ManagedClass(new zaap::graphics::Color(r, g, b, a))
	{
	}
	Color::Color(Vector4^ color)
		: ManagedClass(new zaap::graphics::Color(*color->getHandle()))
	{
	}
	Color::Color(Vector3^ color)
		: ManagedClass(new zaap::graphics::Color(*color->getHandle()))
	{
	}
	Color::Color(Vector3^ color, float a)
		: ManagedClass(new zaap::graphics::Color(*color->getHandle(), a))
	{
	}
	Color::Color(int intR, int intG, int intB)
		: ManagedClass(new zaap::graphics::Color(intR, intG, intB))
	{
	}
	Color::Color(int intR, int intG, int intB, int intA)
		: ManagedClass(new zaap::graphics::Color(intR, intG, intB, intA))
	{
	}
	Color::Color(int hex)
		: ManagedClass(new zaap::graphics::Color(hex))
	{
	}

	//
	//float setters
	//
	void Color::setRGB(float r, float g, float b)
	{
		m_Instance->setRGB(r, g, b);
	}
	void Color::setRGBA(float r, float g, float b, float a)
	{
		m_Instance->setRGBA(r, g, b, a);
	}

	void Color::setRGB(Vector3^ rgb)
	{
		m_Instance->setRGB(*rgb->getHandle());
	}
	void Color::setRGBA(Vector4^ rgba)
	{
		m_Instance->setRGBA(*rgba->getHandle());
	}

	//int setters
	void Color::setIntR(int r)
	{
		m_Instance->setIntR(r);
	}
	void Color::setIntG(int g)
	{
		m_Instance->setIntG(g);
	}
	void Color::setIntB(int b)
	{
		m_Instance->setIntB(b);
	}
	void Color::setIntA(int a)
	{
		m_Instance->setIntA(a);
	}

	void Color::setIntRGB(int r, int g, int b)
	{
		m_Instance->setIntRGB(r, g, b);
	}
	void Color::setIntRGBA(int r, int g, int b, int a)
	{
		m_Instance->setIntRGBA(r, g, b, a);
	}

	//getters
	Vector3^ Color::getRGB()
	{
		return gcnew Vector3(&m_Instance->getRGB());
	}
	Vector4^ Color::getRGBA()
	{
		return gcnew Vector4(&m_Instance->getRGBA());
	}

	int Color::getIntR()
	{
		return m_Instance->getIntR();
	}
	int Color::getIntG()
	{
		return m_Instance->getIntG();
	}
	int Color::getIntB()
	{
		return m_Instance->getIntB();
	}
	int Color::getIntA()
	{
		return m_Instance->getIntA();
	}

	System::String^ Color::ToString()
	{
		return to_CLI_String(m_Instance->toString());
	}
}
