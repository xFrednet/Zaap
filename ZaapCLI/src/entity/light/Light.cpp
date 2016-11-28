#include "Light.h"

namespace ZaapCLI
{
	Light::Light(zaap::Light* instance)
		: m_Instance(instance)
	{
	}

	Light::Light()
		: m_Instance(new zaap::Light())
	{
	}
	Light::Light(Vector3^ position)
		: m_Instance(new zaap::Light(*position->getHandle()))
	{
		
	}
	Light::Light(Vector3^ position, Color^ color)
		: m_Instance(new zaap::Light(*position->getHandle(), *color->getHandle()))
	{
	}

	Light::~Light()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	Light::!Light()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

	//
	//color
	//
	void Light::setColor(Color^ color)
	{
		m_Instance->setColor(*color->getHandle());
	}
	Color^ Light::getColor()
	{
		return gcnew Color(&m_Instance->getColor());
	}

	//
	//position
	//
	void Light::setPosition(Vector3^ position)
	{
		m_Instance->setPosition(*position->getHandle());
	}
	void Light::increasePosition(Vector3^ position)
	{
		m_Instance->increasePosition(*position->getHandle());
	}
	Vector3^ Light::getPosition()
	{
		return gcnew Vector3(&m_Instance->getPosition());
	}

	bool Light::operator==(Light^ left, Light^ right)
	{
		return left->getHandle()->equal(right->getHandle());
	}
	bool Light::operator!=(Light^ left, Light^ right)
	{
		return !left->getHandle()->equal(right->getHandle());
	}

	zaap::Light* Light::getHandle()
	{
		return m_Instance;
	}
}