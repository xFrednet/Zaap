#include "Scene.h"
#include "Renderer.h"

namespace zaap { namespace graphics {
	Scene::~Scene()
	{
		for (uint i = 0; i < m_Entities.size(); i++)
			delete m_Entities[i];
		if (!m_LightSetup) delete m_LightSetup;
	}

	void Scene::addEntity(BasicEntity* entity)
	{
		m_Entities.push_back(entity);
	}
	void Scene::removeEntity(BasicEntity* entity)
	{
		for (unsigned int i = 0; i < m_Entities.size(); i++)
			if (entity == m_Entities[i])
			{
				m_Entities.erase(m_Entities.begin() + i);
				return;
			}
	}

	void Scene::render() const
	{
		if (m_LightSetup)
		{
			m_LightSetup->render();
			Renderer::LoadLightSetup(m_LightSetup);
		}
		for (uint i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->render();
		}
	}
	void Scene::update() const
	{
		if (m_LightSetup) m_LightSetup->update();
		for (uint i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->update();
		}
	}

	//
	// LightSetup
	//
	void Scene::setLightSetup(LightSetup* lightSetup)
	{
		m_LightSetup = lightSetup;
		Renderer::LoadLightSetup(lightSetup);
	}
	LightSetup* Scene::getLightSetup()
	{
		return m_LightSetup;
	}
}}
