#include "BaseEntity.h"

//
// EntityRedirecter
//
namespace ZaapCLI
{
	//Value Methods to excess the protected Values directly
	zaap::Vec3 EntityRedirecter::getPositionValue()
	{
		return m_Position;
	}
	zaap::Vec3 EntityRedirecter::getRotationValue()
	{
		return m_Rotation;
	}
	zaap::Vec3 EntityRedirecter::getScaleValue()
	{
		return m_Scale;
	}

	void EntityRedirecter::setPositionValue(const zaap::Vec3& position)
	{
		m_Position = position;
	}
	void EntityRedirecter::setRotationValue(const zaap::Vec3& rotation)
	{
		m_Rotation = rotation;
	}
	void EntityRedirecter::setScaleValue(const zaap::Vec3& scale)
	{
		m_Scale = scale;
	}

	EntityRedirecter::EntityRedirecter(ZaapCLI::BaseEntity^ owner, zaap::graphics::Mesh *mesh,
		const zaap::Vec3& position, const zaap::Vec3& rotation, const zaap::Vec3& scale)
		: Entity(mesh, position, rotation, scale),
		m_Owner(owner)
	{
	}
	EntityRedirecter::EntityRedirecter(ZaapCLI::BaseEntity^ owner)
		: Entity(),
		m_Owner(owner)
	{
	}

	//position
	void EntityRedirecter::setPosition(const zaap::Vec3 &position)
	{
		m_Owner->setPosition(gcnew Vector3(position.X, position.Y, position.Z));
	}
	void EntityRedirecter::callDefault_setPosition(const zaap::Vec3 &position)
	{
		Entity::setPosition(position);
	}

	void EntityRedirecter::increasePosition(const zaap::Vec3 &position)
	{
		m_Owner->increasePosition(gcnew Vector3(position.X, position.Y, position.Z));
	}
	void EntityRedirecter::callDefault_increasePosition(const zaap::Vec3 &position)
	{
		Entity::increasePosition(position);
	}

	//rotation
	void EntityRedirecter::setRotation(const zaap::Vec3 &rotation)
	{
		m_Owner->setRotation(gcnew Vector3(rotation.X, rotation.Y, rotation.Z));
	}
	void EntityRedirecter::callDefault_setRotation(const zaap::Vec3 &rotation)
	{
		Entity::setRotation(rotation);
	}

	void EntityRedirecter::increaseRotation(const zaap::Vec3 &rotation)
	{
		m_Owner->increaseRotation(gcnew Vector3(rotation.X, rotation.Y, rotation.Z));
	}
	void EntityRedirecter::callDefault_increaseRotation(const zaap::Vec3 &rotation)
	{
		Entity::increaseRotation(rotation);
	}

	//Scale
	void EntityRedirecter::setScale(const float& scale)
	{
		m_Owner->setScale(scale);
	}
	void EntityRedirecter::callDefault_setScale(const float& scale)
	{
		Entity::setScale(scale);
	}

	void EntityRedirecter::setScale(const zaap::Vec3& scale)
	{
		m_Owner->setScale(gcnew Vector3(scale.X, scale.Y, scale.Z));
	}
	void EntityRedirecter::callDefault_setScale(const zaap::Vec3& scale)
	{
		Entity::setScale(scale);
	}

	//Scale
	void EntityRedirecter::increaseScale(const float& scale)
	{
		m_Owner->increaseScale(scale);
	}
	void EntityRedirecter::callDefault_increaseScale(const float& scale)
	{
		Entity::increaseScale(scale);
	}

	void EntityRedirecter::increaseScale(const zaap::Vec3& scale)
	{
		m_Owner->increaseScale(gcnew Vector3(scale.X, scale.Y, scale.Z));
	}
	void EntityRedirecter::callDefault_increaseScale(const zaap::Vec3& scale)
	{
		Entity::increaseScale(scale);
	}

	// GameLoop util
	void EntityRedirecter::update()
	{
		m_Owner->update();
	}
	void EntityRedirecter::callDefault_update()
	{
		Entity::update();
	}
	void EntityRedirecter::render(zaap::graphics::Renderer3D* renderer)
	{
		m_Owner->render(gcnew Renderer3D);
	}
	void EntityRedirecter::callDefault_render(Renderer3D^ renderer)
	{
		Entity::render(renderer->getHandle());
	}
}

namespace ZaapCLI
{
	EntityRedirecter* BaseEntity::getInstance()
	{
		return static_cast<EntityRedirecter*>(m_Instance);
	}

	BaseEntity::BaseEntity(Vector3^ position)
		: Entity(new EntityRedirecter(this, nullptr, *position->getHandle()))
	{
		
	}
	BaseEntity::BaseEntity(Vector3^ position, Vector3^ rotation)
		: Entity(new EntityRedirecter(this, nullptr, *position->getHandle()))
	{

	}
	BaseEntity::BaseEntity(Vector3^ position, Vector3^ rotation, Vector3^ scale)
		: Entity(new EntityRedirecter(this, nullptr, *position->getHandle(), *rotation->getHandle(), *scale->getHandle()))
	{

	}

	//position
	void BaseEntity::setPosition(Vector3^ position)
	{
		getInstance()->callDefault_setPosition(*position->getHandle());
	}
	void BaseEntity::increasePosition(Vector3^ position)
	{
		getInstance()->callDefault_increasePosition(*position->getHandle());
	}

	//rotation
	void BaseEntity::setRotation(Vector3^ rotation)
	{
		getInstance()->callDefault_setRotation(*rotation->getHandle());
	}
	void BaseEntity::increaseRotation(Vector3^ rotation)
	{
		getInstance()->callDefault_increaseRotation(*rotation->getHandle());
	}

	//Scale
	void BaseEntity::setScale(float scale)
	{
		getInstance()->callDefault_setScale(scale);
	}
	void BaseEntity::setScale(Vector3^ scale)
	{
		getInstance()->callDefault_setScale(*scale->getHandle());
	}
	void BaseEntity::increaseScale(float scale)
	{
		getInstance()->callDefault_increaseScale(scale);
	}
	void BaseEntity::increaseScale(Vector3^ scale)
	{
		getInstance()->callDefault_increaseScale(*scale->getHandle());
	}

	// GameLoop util
	void BaseEntity::update()
	{
		getInstance()->callDefault_update();
	}
	void BaseEntity::render(Renderer3D^ renderer)
	{
		getInstance()->callDefault_render(renderer);
	}
}

