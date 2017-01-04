#include "LightSetup.h"

namespace zaap {
	
	LightSetup::~LightSetup()
	{
		for (Light *light : m_Lights)
		{
			if (light)
			{
				delete light;
				light = nullptr;
			}
		}

		m_Lights.clear();

	}

	//
	// Util
	//
	void LightSetup::add(Light* light)
	{
		m_Lights.push_back(light);
	}
	void LightSetup::remove(Light* light, const bool& deleteLight)
	{
		for (uint i = 0; i < m_Lights.size(); i++)
		{
			if (light->equal(m_Lights[i]))
			{
				if (deleteLight)
					delete m_Lights[i];

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
	Light* LightSetup::getLight(uint index)
	{
		if (index < 0 || index >= m_Lights.size())
			return m_Lights[0];

		return m_Lights[index];
	}
	const Light* LightSetup::getConstLight(uint index) const
	{
		if (index < 0 || index >= m_Lights.size())
			return m_Lights[0];

		return m_Lights[index];
	}

}