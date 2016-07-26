#include "LightSetup.h"

namespace zaap { namespace graphics {
	
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
	void LightSetup::render()
	{
		for (uint i = 0; i < m_Lights.size(); i++)
			m_Lights[i]->render();
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

}}