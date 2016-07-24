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

	//
	//Render
	//
	void Renderer::Render(Model* model)
	{ s_Instance->render(model); }
	void Renderer::RenderModelArray(const std::vector<Model*>& models)
	{
		for (uint i = 0; i < models.size(); i++)
		{
			s_Instance->render(models[i]);
		}
	}

	//
	//Setters
	//
	void Renderer::SetCamera(Camera* camera)
	{ s_Instance->setCamera(camera); }

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

}}