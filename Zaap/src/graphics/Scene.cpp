#include "Scene.h"
#include "Renderer.h"

namespace zaap { namespace graphics {
	Scene::~Scene()
	{
		for (uint i = 0; i < m_Entities.size(); i++)
			delete m_Entities[i];

		if (m_LightSetup) delete m_LightSetup;
		if (m_Terrain)
		{
			m_Terrain->cleanup();
			delete m_Terrain;
		}
	}

	void Scene::addEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}
	void Scene::removeEntity(Entity* entity)
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
			Renderer::LoadLightSetup(m_LightSetup);
		}
		if (m_Terrain)
		{
			m_Terrain->render();
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

	//
	// Terrain
	//
	void Scene::setTerrain(scene::Terrain* terrain)
	{
		m_Terrain = terrain;
	}
	scene::Terrain* Scene::getTerrain()
	{
		return m_Terrain;
	}

}}
