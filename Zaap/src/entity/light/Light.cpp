#include "Light.h"

namespace zaap {
	
	Light::Light(const Vec3& position, const graphics::Color& color)
		: m_Color(color),
		m_Position(position)
	{
	}
	
	//
	// Color
	//
	void Light::setColor(const graphics::Color& color)
	{
		m_Color = color;
	}
	graphics::Color Light::getColor() const
	{
		return m_Color;
	}
	graphics::Color* Light::getColorP()
	{
		return &m_Color;
	}

	//
	// Position
	//
	void Light::setPosition(const Vec3& position)
	{
		m_Position = position;
	}
	void Light::increasePosition(const Vec3& position)
	{
		m_Position += position;
	}
	Vec3 Light::getPosition() const
	{
		return m_Position;
	}
	Vec3* Light::getPositionP()
	{
		return &m_Position;
	}

	void Light::update()
	{
	}
}