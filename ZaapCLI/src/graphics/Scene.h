#pragma once

#include <ZaapCLI.h>

#include <graphics/Scene.h>
#include "..\entity\Entity.h"
#include <scene\Terrain.h>

namespace ZaapCLI {

	public ref class Scene : public ManagedClass<zaap::graphics::Scene>
	{
	public:
		
		// <Constructor>
		//      Scene
		//
		// <Descripton>
		//      This creates a new instance of the scene class.
		//
		Scene();
		
		// <Constructor>
		//      Scene
		//
		// <Descripton>
		//      This creates a CLIScene using the given instance.
		//
		Scene(zaap::graphics::Scene* instance);

		void addEntity(Entity^ entity);
		void removeEntity(Entity^ entity);

		void render();
		void update();

		//terrain
		void setTerrain(Terrain^ terrain);
		Terrain^ getTerrain();
	};
}
