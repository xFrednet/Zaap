#pragma once

#include <ZaapCLI.h>

#include <graphics/Scene.h>
#include "..\scene\Terrain.h"
#include "..\graphics\camera\Camera.h"
#include "..\graphics\camera\ViewFrustum.h"
#include "..\entity\light\LightSetup.h"

namespace ZaapCLI {

	ref class Entity;

	public ref class Scene : public ManagedClass<zaap::graphics::Scene>
	{
	public:
		// <Constructor>
		//      Scene
		//
		// <Descripton>
		//      This creates a new instance of the @Scene class.
		//
		Scene();
		
		// <Constructor>
		//      Scene
		//
		// <Descripton>
		//      This creates a CLIScene using the given instance.
		//
		Scene(zaap::graphics::Scene* instance);

		// <Deconstructor>
		//      Scene
		//
		// <Description>
		//      This deconstructor sets m_Instance to null do stop the ManagedClass
		//      from deleting is. This is done in the application class.
		//
		// <Note>
		//      Please ignore it and don't kill me. I know that this is stupid.
		//
		~Scene();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // The Environment //
		/* //////////////////////////////////////////////////////////////////////////////// */
		
		// <Function>
		//      addEntity
		//
		// <Description>
		//      This method adds the given entity to the entity list.
		//      
		// <Input>
		//      entity : the entity that is added to the list.
		//      
		void addEntity(Entity^ entity);

		// <Function>
		//      removeEntity
		//
		// <Description>
		//      This method removes the given entity from the entity list.
		//      
		// <Input>
		//      entity : The entity that should be removed from the list.
		//      
		void removeEntity(Entity^ entity);

		// <Function>
		//      setTerrain
		//
		// <Description>
		//      This method is used to set the terrain.
		//
		// <Input>
		//      terrain : the new terrain that should be used.
		//
		void setTerrain(Terrain^ terrain);

		// <Function>
		//      getTerrain
		//
		// <Description>
		//      This method returns the current terrain.
		//
		// <Output>
		//      The current terrain or a nullptr.
		//
		Terrain^ getTerrain();

		// <Function>
		//      setLightSetup
		//
		// <Description>
		//      This method is used to set the current @LightSetup
		//
		// <Input>
		//      lightSetup : The new LightSetup.
		//
		void setLightSetup(LightSetup^ lightSetup);

		// <Function>
		//      getLightSetup
		//
		// <Description>
		//      This method returns the current @LightSetup
		//
		// <Return>
		//      Returns the current @LightSetup.
		//
		LightSetup^ getLightSetup();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Rendering //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Function>
		//      setCamera
		//
		// <Description>
		//      This sets the current Camera.
		//      The @Camera is used to create the ViewMatrix, calculate the
		//      @ViewFrustum and for rendering effects by the @Renderer3D.
		//      
		// <Input>
		//      camera : The new @Camera.
		//      
		void setCamera(Camera^ camera);

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
		Matrix4^ getViewMatrix();

		// <Function>
		//      getCamera
		//
		// <Description>
		//      This returns the value of the current @Camera:
		//
		// <Return>
		//      This returns the value of the current @Camera.
		//
		Camera^ getCamera();

		// <Function>
		//      getViewFrustum
		//
		// <Description>
		//      This Returns a ViewFrustum from the current @Camera.
		//
		// <Returns>
		//      This Returns a ViewFrustum from the current @Camera.
		//
		ViewFrustum^ getViewFrustum();

		void presentFrame();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */
		void render();
		void update();
	};
}
