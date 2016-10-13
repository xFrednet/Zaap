#include "Light.h"

namespace zaap { namespace graphics {
	
	Light::Light(Vec3 position, Color color)
		: BasicEntity(position),
		m_Color(color)
	{
	}
	
	//
	// Color
	//
	void Light::setColor(Color color)
	{
		m_Color = color;
	}
	Color Light::getColor() const
	{
		return m_Color;
	}
	Color* Light::getColorP()
	{
		return &m_Color;
	}

}}