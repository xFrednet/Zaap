#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/light/Light.h>

#pragma warning( disable : 4251)

namespace zaap { namespace graphics {
	
	class ZAAP_API LightSetup
	{
	private:
		std::vector<Light*> m_Lights;

		Color m_AmbientLightColor;
	public:
		~LightSetup(void);

		//util
		void add(Light *light);
		void remove(Light *light);

		void update(void);
		void render(void);

		//Ambient lighting
		void setAmbientColor(Color color);
		Color getAmbientColor(void) const;

		//getters
		uint getSize() const;
		Light* getLight(int index);
		const Light* getConstLight(int index) const;
	};

}}