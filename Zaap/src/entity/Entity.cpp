#include "Entity.h"

#include <maths/MathUtil.h>

#include <graphics/Renderer.h>

namespace zaap {
	
	//
	// Constructors
	// 
	Entity::Entity(graphics::Mesh* mesh, const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: m_Mesh(mesh),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{
	}
	Entity::Entity()
		: m_Mesh(nullptr),
		m_Position(0.0f, 0.0f, 0.0f),
		m_Rotation(0.0f, 0.0f, 0.0f),
		m_Scale(1.0f, 1.0f, 1.0f)
	{
	}

	//
	// Position
	//
	void Entity::setPosition(const Vec3& position)
	{
		m_Position = position;
	}
	void Entity::increasePosition(const Vec3& position)
	{
		m_Position += position;
	}
	Vec3 Entity::getPosition() const
	{
		return m_Position;
	}
	Vec3* Entity::getPositionP()
	{
		return &m_Position;
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
	void Entity::setScale(const float& scale)
	{
		setScale(Vec3(scale, scale, scale));
	}
	void Entity::setScale(const Vec3& scale)
	{
		m_Scale = scale;
	}
	void Entity::increaseScale(const float& scale)
	{
		increaseScale(Vec3(scale, scale, scale));
	}
	void Entity::increaseScale(const Vec3& scale)
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
	void Entity::getTransformationMatrix(Mat4* result) const
	{
		CreateTransformationMatrix(result, m_Position, m_Rotation, m_Scale);
	}
	
	//
	// GameLoop Util
	//
	void Entity::update()
	{
	}
	void Entity::render()
	{
		graphics::Renderer::Render(this);
	}
}
