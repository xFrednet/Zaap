#include "Entity.h"

#include <maths/MathHelper.h>

#include <graphics/Renderer.h>

namespace zaap {

	Entity::Entity(graphics::Mesh *mesh, math::Vec3 position, math::Vec3 rotation, math::Vec3 scale)
		: BasicEntity(position),
		m_Mesh(mesh),
		m_Rotation(rotation),
		m_Scale(scale)
	{
	}
	Entity::Entity()
		: m_Scale(1.0f, 1.0f, 1.0f)
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
		setScale(math::Vec3(scale, scale, scale));
	}
	void Entity::setScale(math::Vec3 scale)
	{
		m_Scale = scale;
	}
	void Entity::increaseScale(float scale)
	{
		increaseScale(math::Vec3(scale, scale, scale));
	}
	void Entity::increaseScale(math::Vec3 scale)
	{
		m_Scale += scale;
	}

	math::Vec3 Entity::getScale() const
	{
		return m_Scale;
	}

	math::Vec3* Entity::getScaleP()
	{
		return &m_Scale;
	}

	//
	// Getters
	//
	graphics::Mesh* Entity::getMesh()
	{
		return m_Mesh;
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
