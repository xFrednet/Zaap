#pragma once

#include <ZaapCLI.h>

#include <graphics/Scene.h>
#include "..\entity\Entity.h"
#include <scene\Terrain.h>

namespace ZaapCLI {

	public ref class Scene : public ManagedClass<zaap::graphics::Scene>
	{
	private:
	public:
		Scene();
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
