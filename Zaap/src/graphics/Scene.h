#pragma once

#include <common.h>
#include <types.h>

#include <entity/Entity.h>
#include <entity/light/LightSetup.h>
#include <scene/terrain/Terrain.h>
#include "camera/Camera.h"
#include "Renderer3D.h"

namespace zaap
{
	namespace scene
	{
		class Terrain;
	}
}

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

		// <Value>
		//      m_Camera
		//
		// <Description>
		//      This is the current @Camera. 
		//      The @Camera is used to create the ViewMatrix, calculate the
		//      @ViewFrustum and for rendering effects by the @Renderer3D.
		//
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

		// <Function>
		//      addEntity
		//
		// <Description>
		//      This method adds the given entity to the entity list.
		//      
		// <Input>
		//      entity : the entity that is added to the list.
		//      
		virtual void addEntity(Entity* entity);
		
		// <Function>
		//      removeEntity
		//
		// <Description>
		//      This method removes the given entity from the entity list.
		//      
		// <Input>
		//      entity : The entity that should be removed from the list.
		//      
		virtual void removeEntity(Entity* entity);
		
		// <Function>
		//      setTerrain
		//
		// <Description>
		//      This method is used to set the terrain.
		//
		// <Input>
		//      terrain : the new terrain that should be used.
		//
		inline virtual void setTerrain(scene::Terrain* terrain);
		
		// <Function>
		//      getTerrain
		//
		// <Description>
		//      This method returns the current terrain.
		//
		// <Return>
		//      The current terrain or a nullptr.
		//
		inline virtual scene::Terrain* getTerrain() const;

		// <Function>
		//      setLightSetup
		//
		// <Description>
		//      This method is used to set the current @LightSetup
		//
		// <Input>
		//      lightSetup : The new LightSetup.
		//
		inline virtual void setLightSetup(LightSetup* lightSetup);

		// <Function>
		//      getLightSetup
		//
		// <Description>
		//      This method returns the current @LightSetup
		//
		// <Return>
		//      Returns the current @LightSetup.
		//
		inline virtual LightSetup* getLightSetup() const;
		
		////////////////////////////////////////////////////////////////////////////////
		// Rendering //
		////////////////////////////////////////////////////////////////////////////////
		
		// <Function>
		//      setCamera
		//
		// <Description>
		//      This sets the current Camera.
		//      The @Camera is used to create the ViewMatrix, calculate the
		//      @ViewFrustum and for rendering effects by the @Renderer3D.
		//      
		// <Input>
		//      camera : The new Camera.
		//      
		inline void setCamera(Camera* camera);

		// <Function>
		//      getViewMatrix
		//
		// <Description>
		//      This returns the ViewMatrix from the current @Camera.
		//
		// <Return>
		//      This return the ViewMatrix from the current @Camera or 
		//      a basic ViewMatrix if the @Camera is null.
		//
		inline Mat4 getViewMatrix() const;

		// <Function>
		//      getCamera
		//
		// <Description>
		//      This returns the value of the current @Camera:
		//
		// <Return>
		//      This returns the value of the current @Camera.
		//
		inline Camera* getCamera() const;

		// <Function>
		//      getViewFrustum
		//
		// <Description>
		//      This Returns a ViewFrustum from the current @Camera.
		//
		// <Returns>
		//      This Returns a ViewFrustum from the current @Camera.
		//
		inline ViewFrustum getViewFrustum() const;

		////////////////////////////////////////////////////////////////////////////////
		// Util //
		////////////////////////////////////////////////////////////////////////////////
		virtual void render() const;
		virtual void update();
		inline Renderer3D* getRenderer();
	};
}}
