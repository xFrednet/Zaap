#include "Renderer.h"

#include "DX/DXRenderer.h"
#include "util/Console.h"

namespace zaap { namespace graphics {
		
	Renderer* Renderer::s_Instance = nullptr;

	//
	//Init
	//
	void Renderer::Init()
	{
		s_Instance = new DX::DXRenderer();

		s_Instance->init();
	}

	void Renderer::Render(const scene::Terrain const *terrainTile)
	{
		s_Instance->render(terrainTile);
	}

	//
	//Render
	//
	void Renderer::Render(Entity* entity)
	{ s_Instance->render(entity); }
	void Renderer::RenderEntityArray(const std::vector<Entity*>& Entities)
	{
		for (uint i = 0; i < Entities.size(); i++)
		{
			s_Instance->render(Entities[i]);
		}
	}

	//
	//Setters
	//
	void Renderer::SetCamera(Camera* camera)
	{ s_Instance->setCamera(camera); }

	void Renderer::LoadLightSetup(LightSetup* lightSetup)
	{
		s_Instance->loadLightSetup(lightSetup);
	}

	//
	//Util
	//
	void Renderer::Prepare()
	{ s_Instance->prepare(); }
	void Renderer::Cleanup()
	{
		s_Instance->cleanup();
		delete s_Instance;
		ZAAP_CLEANUP_LOG("Renderer");
	}
	void Renderer::Resize(uint width, uint height)
	{
		if (s_Instance) s_Instance->resize(width, height);
	}

	bool Renderer::IsVisible(const math::Vec3 &point)
	{
		return s_Instance->isVisible(point);
	}
}}