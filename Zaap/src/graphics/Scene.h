#pragma once

#include <common.h>
#include <types.h>

#include <entity/Entity.h>
#include <entity/light/LightSetup.h>
#include <scene/terrain/Terrain.h>
#include "camera/Camera.h"

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		//environment 
		std::vector<Entity*> m_Entities;
		scene::Terrain *m_Terrain;
		LightSetup *m_LightSetup = nullptr;

		// Rendering
		Camera *m_Camera;


	public:
		virtual ~Scene(void);

		//
		// The Environment 
		//
		//entitys
		virtual void addEntity(Entity* entity);
		virtual void removeEntity(Entity* entity);
		
		//terrain
		inline virtual void setTerrain(scene::Terrain* terrain);
		inline virtual scene::Terrain* getTerrain() const;

		//lightSetup
		inline virtual void setLightSetup(LightSetup* lightSetup);
		inline virtual LightSetup* getLightSetup() const;
		
		//
		// Rendering
		//
		//Camera
		inline virtual void setCamera(Camera* camera);
		inline virtual Mat4 getViewMatrix() const;
		inline virtual Camera* getCamera() const;
		inline virtual ViewFrustum getViewFrustum() const;

		//
		// Util
		//
		virtual void render() const;
		virtual void update();
		

	};
}}
