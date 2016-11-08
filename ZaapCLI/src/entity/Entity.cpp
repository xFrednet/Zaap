#include "Entity.h"

namespace ZaapCLI {

	Entity::Entity(zaap::Entity* instance)
		: m_Instance(instance)
	{
	}
	Entity::~Entity()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	Entity::!Entity() 
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

	//position
	void Entity::setPosition(Vector3^ position)
	{
		m_Instance->setPosition(*position->getHandle());
	}
	void Entity::increasePosition(Vector3^ position)
	{
		m_Instance->increasePosition(*position->getHandle());
	}
	Vector3^ Entity::getPosition()
	{
		return gcnew Vector3(&m_Instance->getPosition());
	}

	//rotation
	void Entity::setRotation(Vector3^ rotation)
	{
		m_Instance->setRotation(*rotation->getHandle());
	}
	void Entity::increaseRotation(Vector3^ rotation)
	{
		m_Instance->increaseRotation(*rotation->getHandle());
	}
	Vector3^ Entity::getRotation()
	{
		return gcnew Vector3(&m_Instance->getRotation());
	}

	//Scale
	void Entity::setScale(float scale)
	{
		m_Instance->setScale(scale);
	}
	void Entity::setScale(Vector3^ scale)
	{
		m_Instance->setScale(*scale->getHandle());
	}
	void Entity::increaseScale(float scale)
	{
		m_Instance->increaseScale(scale);
	}
	void Entity::increaseScale(Vector3^ scale)
	{
		m_Instance->increaseScale(*scale->getHandle());
	}
	Vector3^ Entity::getScale()
	{
		return gcnew Vector3(&m_Instance->getScale());
	}

	//Getters
	//virtual graphics::Mesh* getMesh();
	void Entity::getTransformationMatrix(Matrix4^ result)
	{
		m_Instance->getTransformationMatrix(*result->getHandle());
	}

	// GameLoop util
	void Entity::update()
	{
		m_Instance->update();
	}
	void Entity::render()
	{
		m_Instance->render();
	}

	zaap::Entity* Entity::getHandle()
	{
		return m_Instance;
	}

}
