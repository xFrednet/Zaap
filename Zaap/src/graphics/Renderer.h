#pragma once

#include "Common.h"
#include "graphics/camera/Camera.h"
#include <entity/Entity.h>
#include <graphics/light/LightSetup.h>
#include <scene/terrain/Terrain.h>

namespace zaap { namespace graphics {

	class ZAAP_API Renderer
	{
	private:
		static Renderer* s_Instance;
	protected:
		//Init
		virtual void init() = 0;

		//Render
		virtual void render(const scene::Terrain const *terrainTile) = 0;
		virtual void render(Entity* model) = 0;

		//Setters
		virtual void setCamera(Camera* camera) = 0;
		virtual void loadLightSetup(LightSetup* lightSetup) = 0;

		//Util
		virtual void prepare() = 0;
		virtual void cleanup() = 0;
		virtual void resize(uint width, uint height) = 0;

	public:
		//Init
		static void Init();

		//Render
		static void Render(const scene::Terrain const *terrainTile);
		static void Render(Entity* model);
		static void RenderEntityArray(const std::vector<Entity*>& models);
		
		//Setters
		static void SetCamera(Camera* camera);
		static void LoadLightSetup(LightSetup* lightSetup);

		//Util
		static void Prepare();
		static void Cleanup();
		static void Resize(uint width, uint height);
	};

}}
