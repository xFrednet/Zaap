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
	public:
		~LightSetup(void);

		//util
		virtual void add(Light *light);
		virtual void remove(Light *light);

		virtual void update(void);
		virtual void render(void);

		//getters
		uint getSize() const;
		Light* getLight(int index);
		const Light* getConstLight(int index) const;
	};

}}