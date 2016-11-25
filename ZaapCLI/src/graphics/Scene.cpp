#include "Scene.h"

namespace ZaapCLI {
	
	Scene::Scene()
		: ManagedClass(new zaap::graphics::Scene())
	{
	}
	Scene::Scene(zaap::graphics::Scene* instance)
		: ManagedClass(instance)
	{
	}

	void Scene::addEntity(Entity^ entity)
	{
		m_Instance->addEntity(entity->getHandle());
	}
	void Scene::removeEntity(Entity^ entity)
	{
		m_Instance->removeEntity(entity->getHandle());
	}

	void Scene::render()
	{
		m_Instance->render();
	}
	void Scene::update()
	{
		m_Instance->update();
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
}
