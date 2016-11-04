#pragma once

#include <common.h>
#include <types.h>

#include <entity/Entity.h>
#include <entity/light/LightSetup.h>
#include <scene/terrain/Terrain.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		std::vector<Entity*> m_Entities;

		LightSetup *m_LightSetup = nullptr;
		scene::Terrain *m_Terrain;
	public:
		~Scene(void);

		virtual void addEntity(Entity* entity);
		virtual void removeEntity(Entity* entity);

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
