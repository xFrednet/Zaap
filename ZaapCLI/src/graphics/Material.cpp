#include "Material.h"

namespace ZaapCLI
{
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructor //
	/* //////////////////////////////////////////////////////////////////////////////// */
	Material::Material()
		: ManagedClass(new zaap::graphics::Material())
	{
	}
	Material::Material(Color^ color, float reflectivity)
		: ManagedClass(new zaap::graphics::Material(*color->getHandle(), reflectivity))
	{
	}
	Material::Material(zaap::graphics::Material* instance) 
		: ManagedClass(instance)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	bool Material::operator==(Material^ other)
	{
		return Equal(*m_Instance, *other->getHandle());
	}
	bool Material::operator!=(Material^ other)
	{
		return !Equal(*m_Instance, *other->getHandle());
	}
}
