#include "BasicEntity.h"

namespace zaap
{
	BasicEntity::BasicEntity(math::Vec3 position)
		: m_Position(position)
	{
	}

	//
	// Position
	//
	void BasicEntity::setPosition(const math::Vec3& position)
	{
		m_Position = position;
	}
	void BasicEntity::increasePosition(const math::Vec3& position)
	{
		m_Position += position;
	}
	math::Vec3 BasicEntity::getPosition() const
	{
		return m_Position;
	}
	math::Vec3* BasicEntity::getPositionP()
	{
		return &m_Position;
	}

	//
	// Util
	//
	void BasicEntity::update() {}
	void BasicEntity::render() {}

}
