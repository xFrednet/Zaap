#include "Material.h"

namespace zaap { namespace graphics {
	Material::Material()
		: DiffuseReflectivity(1.0f, 1.0f, 1.0f),
		SpectralReflectivity(0.0f)
	{
	}

	Material::Material(Color color, float reflectivity)
		: DiffuseReflectivity(color.getRGB()),
		SpectralReflectivity(reflectivity)
	{
	}

	String Material::toString() const
	{
		return "Material(DiffuseReflectivity: " + DiffuseReflectivity.toString() + 
			", SpectralReflectivity: " + std::to_string(SpectralReflectivity) + ")";
	}

	bool Material::operator==(const Material& other) const
	{
		return Equal(*this, other);
	}

	bool Material::operator!=(const Material& other) const
	{
		return !Equal(*this, other);
	}

	bool Equal(const Material& a, const Material& b)
	{
		return Equal(a.DiffuseReflectivity, b.DiffuseReflectivity) &&
			(a.SpectralReflectivity == b.SpectralReflectivity);
	}
}}