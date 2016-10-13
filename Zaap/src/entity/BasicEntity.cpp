#include "BasicEntity.h"

namespace zaap
{
	BasicEntity::BasicEntity(Vec3 position)
		: m_Position(position)
	{
	}

	//
	// Position
	//
	void BasicEntity::setPosition(const Vec3& position)
	{
		m_Position = position;
	}
	void BasicEntity::increasePosition(const Vec3& position)
	{
		m_Position += position;
	}
	Vec3 BasicEntity::getPosition() const
	{
		return m_Position;
	}
	Vec3* BasicEntity::getPositionP()
	{
		return &m_Position;
	}

	//
	// Util
	//
	void BasicEntity::update() {}
	void BasicEntity::render() {}

}
