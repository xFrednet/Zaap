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

		void addEntity(Entity* entity);
		void removeEntity(Entity* entity);

		void render() const;
		void update() const;
		
		//lightSetup
		virtual void setLightSetup(LightSetup* lightSetup);
		virtual LightSetup* getLightSetup();

		//terrain
		void setTerrain(scene::Terrain* terrain);
		scene::Terrain* getTerrain();
	};
}}
