#pragma once

#include <common.h>
#include <types.h>

#include <entity/Entity.h>
#include <entity/light/LightSetup.h>
#include <scene/terrain/Terrain.h>
#include "camera/Camera.h"
#include "Renderer3D.h"

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		//environment 
		std::vector<Entity*> m_Entities;
		scene::Terrain* m_Terrain;
		LightSetup* m_LightSetup;

		// Rendering
		Renderer3D* m_Renderer;
		Camera* m_Camera;


	public:
		
		// <Constructor>
		//      Scene
		//
		// <Descripton>
		//      This creates a new instance of the scene class.
		//
		// <Note>
		//      init is called by the Application class. The init method
		//      should still be called in case of a unconventional use.
		Scene();

		// <Deconstructor>
		//      Scene
		//
		// <Description>
		//      This deletes all valid pointers.
		//
		virtual ~Scene(void);

		// <Function>
		//      init
		// 
		// <Description>
		//      This internalizes some values that are based on the 
		//      initialization of the API.
		//
		void init();

		////////////////////////////////////////////////////////////////////////////////
		// The Environment //
		////////////////////////////////////////////////////////////////////////////////

		//entitys
		virtual void addEntity(Entity* entity);
		virtual void removeEntity(Entity* entity);
		
		//terrain
		inline virtual void setTerrain(scene::Terrain* terrain);
		inline virtual scene::Terrain* getTerrain() const;

		//lightSetup
		inline virtual void setLightSetup(LightSetup* lightSetup);
		inline virtual LightSetup* getLightSetup() const;
		
		////////////////////////////////////////////////////////////////////////////////
		// Rendering //
		////////////////////////////////////////////////////////////////////////////////
		
		//Camera
		inline virtual void setCamera(Camera* camera);
		inline virtual Mat4 getViewMatrix() const;
		inline virtual Camera* getCamera() const;
		inline virtual ViewFrustum getViewFrustum() const;

		////////////////////////////////////////////////////////////////////////////////
		// Util //
		////////////////////////////////////////////////////////////////////////////////
		virtual void render() const;
		virtual void update();
		inline Renderer3D* getRenderer();
	};
}}
