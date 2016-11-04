#include "LightSetup.h"

namespace zaap {
	
	LightSetup::~LightSetup()
	{
		for (Light *light : m_Lights)
			delete light;
	}

	//
	// Util
	//
	void LightSetup::add(Light* light)
	{
		m_Lights.push_back(light);
	}
	void LightSetup::remove(Light* light)
	{
		for (uint i = 0; i < m_Lights.size(); i++)
		{
			if (light == m_Lights[i])
			{
				m_Lights.erase(m_Lights.begin() + i);
				return;
			}
		}
	}

	void LightSetup::update()
	{
		for (uint i = 0; i < m_Lights.size(); i++)
			m_Lights[i]->update();
	}

	//
	// Ambient lighting
	//
	void LightSetup::setAmbientColor(graphics::Color color)
	{
		m_AmbientLightColor = color;
	}
	graphics::Color LightSetup::getAmbientColor() const
	{
		return m_AmbientLightColor;
	}

	//
	// Getters
	//
	uint LightSetup::getSize() const
	{
		return m_Lights.size();
	}
	Light* LightSetup::getLight(int index)
	{
		return m_Lights[index];
	}
	const Light* LightSetup::getConstLight(int index) const
	{
		return m_Lights[index];
	}

}