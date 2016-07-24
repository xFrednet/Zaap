#include "Scene.h"
#include "util/Console.h"

namespace zaap { namespace graphics {
	
	void Scene::addModel(Model* model)
	{
		//addModel if it is not present aleady
		m_Models.push_back(model);
	}

	void Scene::removeModel(Model* model)
	{
		for (unsigned int i = 0; i < m_Models.size(); i++)
		{
			if (model == m_Models[i])
			{
				m_Models.erase(m_Models.begin() + i);
				return;
			}
		}

	}

	void Scene::render() const
	{
		Renderer::RenderModelArray(m_Models);
	}

	void Scene::update() const
	{
	}
}}
