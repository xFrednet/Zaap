#include "LightSetup.h"

namespace ZaapCLI {
	LightSetup::LightSetup()
		: ManagedClass(new zaap::LightSetup())
	{
	}

	//util
	void LightSetup::add(Light^ light)
	{
		m_Instance->add(light->getHandle());
	}
	void LightSetup::remove(Light^ light)
	{
		m_Instance->remove(light->getHandle());
	}

	void LightSetup::update()
	{
		m_Instance->update();
	}

	//Ambient lighting
	void LightSetup::setAmbientColor(Color^ color)
	{
		m_Instance->setAmbientColor(*color->getHandle());
	}
	Color^ LightSetup::getAmbientColor()
	{
		return gcnew Color(&m_Instance->getAmbientColor());
	}

	//getters
	uint LightSetup::getSize()
	{
		return m_Instance->getSize();
	}
	Light^ LightSetup::getLight(int index)
	{
		return gcnew Light(m_Instance->getLight(index));
	}
}
