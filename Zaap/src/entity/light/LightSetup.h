#pragma once

#include <Common.h>
#include <Types.h>

#include "Light.h"

#pragma warning( disable : 4251)

namespace zaap {
	
	class ZAAP_API LightSetup
	{
	private:
		std::vector<Light*> m_Lights;

		graphics::Color m_AmbientLightColor;
	public:
		~LightSetup(void);

		//util
		void add(Light *light);
		void remove(Light *light);

		void update();

		//Ambient lighting
		void setAmbientColor(graphics::Color color);
		graphics::Color getAmbientColor() const;

		//getters
		uint getSize() const;
		Light* getLight(int index);
		const Light* getConstLight(int index) const;
	};

}