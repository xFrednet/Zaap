#include "Entity.h"

#include <maths/MathHelper.h>

#include <graphics/Renderer.h>

namespace zaap {

	Entity::Entity(graphics::Mesh *mesh, Vec3 position, Vec3 rotation, Vec3 scale)
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
	void Entity::setRotation(const Vec3& rotation)
	{
		m_Rotation = rotation;
	}
	void Entity::increaseRotation(const Vec3& rotation)
	{
		m_Rotation += rotation;
	}
	Vec3 Entity::getRotation() const
	{
		return m_Rotation;
	}
	Vec3* Entity::getRotationP()
	{
		return &m_Rotation;
	}

	//
	// Scale
	//
	void Entity::setScale(float scale)
	{
		setScale(Vec3(scale, scale, scale));
	}
	void Entity::setScale(Vec3 scale)
	{
		m_Scale = scale;
	}
	void Entity::increaseScale(float scale)
	{
		increaseScale(Vec3(scale, scale, scale));
	}
	void Entity::increaseScale(Vec3 scale)
	{
		m_Scale += scale;
	}

	Vec3 Entity::getScale() const
	{
		return m_Scale;
	}

	Vec3* Entity::getScaleP()
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
	void Entity::getTransformationMatrix(Mat4 &result) const
	{
		result = CreateTransformationMatrix(m_Position, m_Rotation, m_Scale);
	}
	
	//
	// Util
	//
	void Entity::render()
	{
		graphics::Renderer::Render(this);
	}
}
