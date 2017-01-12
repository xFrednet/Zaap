#include "Scene.h"

#include "..\entity\Entity.h"

namespace ZaapCLI {
	
	Scene::Scene()
		: ManagedClass(new zaap::graphics::Scene())
	{
	}
	Scene::Scene(zaap::graphics::Scene* instance)
		: ManagedClass(instance)
	{
	}

	Scene::~Scene()
	{
		m_Instance = nullptr;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // The Environment //
	/* //////////////////////////////////////////////////////////////////////////////// */

	//entity
	void Scene::addEntity(Entity^ entity)
	{
		m_Instance->addEntity(entity->getHandle());
	}
	void Scene::removeEntity(Entity^ entity)
	{
		m_Instance->removeEntity(entity->getHandle());
	}
	
	//terrain
	void Scene::setTerrain(Terrain^ terrain)
	{
		m_Instance->setTerrain(terrain->getHandle());
	}
	Terrain^ Scene::getTerrain()
	{
		return gcnew Terrain(m_Instance->getTerrain());
	}

	// LightSetup
	void Scene::setLightSetup(LightSetup^ lightSetup)
	{
		m_Instance->setLightSetup(lightSetup->getHandle());
	}
	LightSetup^ Scene::getLightSetup()
	{
		return gcnew LightSetup(m_Instance->getLightSetup());
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Rendering //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void Scene::setCamera(Camera^ camera)
	{
		m_Instance->setCamera(camera->getHandle());
	}
	Matrix4^ Scene::getViewMatrix()
	{
		return gcnew Matrix4(&m_Instance->getViewMatrix());
	}
	Camera^ Scene::getCamera()
	{
		return gcnew Camera(m_Instance->getCamera());
	}
	ViewFrustum^ Scene::getViewFrustum()
	{
		return gcnew ViewFrustum(&m_Instance->getViewFrustum());
	}

	void Scene::presentFrame()
	{
		m_Instance->getRenderer()->presentFrame();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void Scene::render()
	{
		m_Instance->render();
	}
	void Scene::update()
	{
		m_Instance->update();
	}

}
