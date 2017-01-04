#pragma once

#include <Common.h>
#include <Types.h>

#include "Light.h"

#pragma warning( disable : 4251)

namespace zaap {
	
	// <Class>
	//      LightSetup
	// 
	// <Description>
	//
	class ZAAP_API LightSetup
	{
	private:
		std::vector<Light*> m_Lights;

		graphics::Color m_AmbientLightColor;
	public:
		~LightSetup(void);

		//util
		void add(Light *light);
		void remove(Light *light, const bool& deleteLight = true);

		void update();

		//Ambient lighting
		void setAmbientColor(graphics::Color color);
		graphics::Color getAmbientColor() const;

		//getters
		uint getSize() const;
		Light* getLight(uint index);
		const Light* getConstLight(uint index) const;
	};

}