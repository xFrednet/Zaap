#include "Scene.h"

namespace zaap { namespace graphics {
	
	void Scene::addEntity(Entity* model)
	{
		m_Entities.push_back(model);
	}

	void Scene::removeEntity(Entity* model)
	{
		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			if (model == m_Entities[i])
			{
				m_Entities.erase(m_Entities.begin() + i);
				return;
			}
		}

	}

	void Scene::render() const
	{
		Renderer::RenderEntityArray(m_Entities);
	}

	void Scene::update() const
	{
	}
}}
