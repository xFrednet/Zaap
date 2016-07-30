#include "Material.h"

namespace zaap { namespace graphics {
	Material::Material()
		: Color(1.0f, 1.0f, 1.0f),
		Reflectivity(0.0f)
	{
	}

	Material::Material(graphics::Color color, float reflectivity)
		: Color(color),
		Reflectivity(reflectivity)
	{
	}

	String Material::toString() const
	{
		return "Material(" + Color.toString() + ", Reflectivity: " + std::to_string(Reflectivity) + ")";
	}
}}