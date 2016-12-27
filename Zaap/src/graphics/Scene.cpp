#include "Scene.h"
#include <util/Console.h>
#include <events/Input.h>

namespace zaap { namespace graphics {
	Scene::Scene()
		: m_Terrain(nullptr),
		m_LightSetup(nullptr),
		m_Renderer(nullptr),
		m_Camera(nullptr)
	{
	}

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
			m_Terrain = nullptr;
		}
		
		if (m_Renderer)
		{
			m_Renderer->cleanup();
			delete m_Renderer;
			m_Renderer = nullptr;
		}
	}

	void Scene::init()
	{
		m_Renderer = Renderer3D::CreateNewInstance();
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
		m_Renderer->loadScene(this);

		if (m_LightSetup)
			m_Renderer->loadLightSetup(*m_LightSetup);
		
		m_Renderer->prepareFrame();

		//
		// rendering
		//
		if (m_Terrain)
			m_Terrain->render(m_Renderer);
		
		for (uint i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->render(m_Renderer);
		}

		m_Renderer->presentFrame();
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

	Renderer3D* Scene::getRenderer()
	{
		return m_Renderer;
	}
}}
