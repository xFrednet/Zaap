#include "Light.h"

namespace zaap { namespace graphics {
	
	Light::Light(math::Vec3 position, math::Vec3 color)
		: BasicEntity(position),
		m_Color(color)
	{
	}
	
	//
	// Color
	//
	void Light::setColor(math::Vec3 color)
	{
		m_Color = color;
		m_Color.clamp(0.0f, 1.0f);
	}
	void Light::increaseColor(math::Vec3 color)
	{
		m_Color = color;
		m_Color.clamp(0.0f, 1.0f);
	}
	math::Vec3 Light::getColor() const
	{
		return m_Color;
	}
	math::Vec3* Light::getColorP()
	{
		return &m_Color;
	}

}}