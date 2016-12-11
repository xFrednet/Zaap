#include "Scene.h"
#include "Renderer.h"
#include <util/Console.h>
#include <events/Input.h>

namespace zaap { namespace graphics {
	Scene::~Scene()
	{
		for (uint i = 0; i < m_Entities.size(); i++)
			delete m_Entities[i];

		if (m_LightSetup) 
			delete m_LightSetup;

		if (m_Terrain)
		{
			m_Terrain->cleanup();
			delete m_Terrain;
		}
		ZAAP_ALERT("Scene deletion");
	}

	/////////////////////
	// The Environment //
	/////////////////////
	//
	// Entitys
	//
	void Scene::addEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}
	void Scene::removeEntity(Entity* entity)
	{
		for (uint i = 0; i < m_Entities.size(); i++)
			if (entity == m_Entities[i])
			{
				m_Entities.erase(m_Entities.begin() + i);
				return;
			}
	}

	//
	// Terrain
	//
	void Scene::setTerrain(scene::Terrain* terrain)
	{
		m_Terrain = terrain;
	}
	scene::Terrain* Scene::getTerrain() const
	{
		return m_Terrain;
	}
	
	//
	// LightSetup
	//
	void Scene::setLightSetup(LightSetup* lightSetup)
	{
		m_LightSetup = lightSetup;
		Renderer::LoadLightSetup(lightSetup);
	}
	LightSetup* Scene::getLightSetup() const
	{
		return m_LightSetup;
	}

	///////////////
	// Rendering //
	///////////////
	//
	// Camera
	//
	void Scene::setCamera(Camera* camera)
	{
		m_Camera = camera;
	}
	Mat4 Scene::getViewMatrix() const
	{
		return m_Camera->getViewMatrix();
	}
	Camera* Scene::getCamera() const
	{
		return m_Camera;
	}
	ViewFrustum Scene::getViewFrustum() const
	{
		return m_Camera->getViewFrustum();
	}

	//
	// Util
	//
	ViewFrustum frustum;
	void Scene::render() const
	{
		//
		//render preparations
		//
		if (m_Camera)
		{
			Renderer::SetViewMatrix(m_Camera->getViewMatrix());
			m_Camera->calculateViewFrustum();
			frustum = m_Camera->getViewFrustum();
		}
		else
		{
			Mat4 m;
			CreateViewMatrix(&m, Vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
			Renderer::SetViewMatrix(m);
		}

		if (m_LightSetup)
			Renderer::LoadLightSetup(m_LightSetup);
		
		//
		// rendering
		//
		if (m_Terrain)
			m_Terrain->render(frustum);
		
		for (uint i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->render();
		}
	}
	void Scene::update()
	{
		if (m_Camera) m_Camera->update();
		if (m_LightSetup) m_LightSetup->update();
		for (uint i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->update();
		}
	}


}}
