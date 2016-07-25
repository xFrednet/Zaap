#include "Entity.h"
#include <maths/MathHelper.h>

namespace zaap {

	Entity::Entity(graphics::TexturedMesh& tMesh, math::Vec3& position, math::Vec3& rotation, float scale)
		: m_TMesh(tMesh),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{
	}
	Entity::Entity()
		: m_Scale(1.0f)
	{
	}

	//
	// Position
	//
	void Entity::setPosition(math::Vec3& position)
	{
		m_Position = position;
	}
	void Entity::increasePosition(math::Vec3& position)
	{
		m_Position += position;
	}
	math::Vec3 Entity::getPosition() const
	{
		return m_Position;
	}

	//
	// Rotation
	//
	void Entity::setRotation(math::Vec3& rotation)
	{
		m_Rotation = rotation;
	}
	void Entity::increaseRotation(math::Vec3& rotation)
	{
		m_Rotation += rotation;
	}
	math::Vec3 Entity::getRotation() const
	{
		return m_Rotation;
	}

	//
	// Scale
	//
	void Entity::setScale(float scale)
	{
		m_Scale = scale;
	}
	void Entity::addToScale(float scale)
	{
		m_Scale += scale;
	}
	float Entity::getScale() const
	{
		return m_Scale;
	}

	//
	// Getters
	//
	graphics::TexturedMesh* Entity::getTexturedMesh()
	{
		return &m_TMesh;
	}
	void Entity::getTransformationMatrix(math::Mat4 &result) const
	{
		result = math::CreateTransformationMatrix(m_Position, m_Rotation, m_Scale);
	}

}
