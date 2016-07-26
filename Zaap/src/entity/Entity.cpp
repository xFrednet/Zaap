#include "Entity.h"

#include <maths/MathHelper.h>

#include <graphics/Renderer.h>

namespace zaap {

	Entity::Entity(graphics::TexturedMesh& tMesh, math::Vec3& position, math::Vec3& rotation, float scale)
		: BasicEntity(position),
		m_TMesh(tMesh),
		m_Rotation(rotation),
		m_Scale(scale)
	{
	}
	Entity::Entity()
		: m_Scale(1.0f)
	{
	}

	//
	// Rotation
	//
	void Entity::setRotation(const math::Vec3& rotation)
	{
		m_Rotation = rotation;
	}
	void Entity::increaseRotation(const math::Vec3& rotation)
	{
		m_Rotation += rotation;
	}
	math::Vec3 Entity::getRotation() const
	{
		return m_Rotation;
	}
	math::Vec3* Entity::getRotationP()
	{
		return &m_Rotation;
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
	
	//
	// Util
	//
	void Entity::render()
	{
		graphics::Renderer::Render(this);
	}
}
