#pragma once

#include <common.h>
#include <types.h>

#include <entity/Entity.h>
#include <graphics/light/LightSetup.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		std::vector<BasicEntity*> m_Entities;

		LightSetup* m_LightSetup = nullptr;
	public:
		~Scene(void);

		virtual void addEntity(BasicEntity* entity);
		virtual void removeEntity(BasicEntity* entity);

		virtual void render() const;
		virtual void update() const;
		
		//lightSetup
		virtual void setLightSetup(LightSetup* lightSetup);
		virtual LightSetup* getLightSetup(void);
	};
}}
