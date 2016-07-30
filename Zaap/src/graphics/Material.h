#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Color.h>

namespace zaap { namespace graphics {
	
	struct ZAAP_API Material
	{
		Color Color;
		float Reflectivity;

		Material();
		Material(graphics::Color color, float reflectivity);

		String toString(void) const;
	};

}}