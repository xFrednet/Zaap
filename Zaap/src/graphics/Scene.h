#pragma once

#include <common.h>
#include <types.h>

#include <entity/Entity.h>
#include <graphics/light/LightSetup.h>
#include <scene/terrain/Terrain.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		std::vector<BasicEntity*> m_Entities;

		LightSetup *m_LightSetup = nullptr;
		scene::Terrain *m_Terrain;
	public:
		~Scene(void);

		virtual void addEntity(BasicEntity* entity);
		virtual void removeEntity(BasicEntity* entity);

		virtual void render() const;
		virtual void update() const;
		
		//lightSetup
		virtual void setLightSetup(LightSetup* lightSetup);
		virtual LightSetup* getLightSetup(void);

		//terrain
		virtual void setTerrain(scene::Terrain* terrain);
		virtual scene::Terrain* getTerrain(void);
	};
}}
