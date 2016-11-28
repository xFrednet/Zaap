#include "Renderer.h"

namespace ZaapCLI {
	//Init
	void Renderer::Init()
	{
		zaap::graphics::Renderer::Init();
	}

	//Shader stuff
	//static void StartShader(ZA_SHADER_TYPE shader);
	//static Shader* GetShader(ZA_SHADER_TYPE shader);

	//Render
	void Renderer::Render(Terrain^ terrainTile)
	{
		zaap::graphics::Renderer::Render(terrainTile->getHandle());
	}
	void Renderer::Render(Entity^ model)
	{
		zaap::graphics::Renderer::Render(model->getHandle());
	}

	//Camera
	void Renderer::SetCamera(Camera^ camera)
	{
		zaap::graphics::Renderer::SetCamera(camera->getHandle());
	}
	void Renderer::SetCamera(Camera^ camera, bool deleteOldCamera)
	{
		zaap::graphics::Renderer::SetCamera(camera->getHandle(), deleteOldCamera);
	}
	Camera^ Renderer::GetCamera()
	{
		return gcnew Camera(zaap::graphics::Renderer::GetCamera());
	}
	ViewFrustum^ Renderer::GetViewFrustum()
	{
		return gcnew ViewFrustum(&zaap::graphics::Renderer::GetViewFrustum());
	}

	//Setters
	void Renderer::LoadLightSetup(LightSetup^ lightSetup)
	{
		zaap::graphics::Renderer::LoadLightSetup(lightSetup->getHandle());
	}

	//Render options 
	void Renderer::SetDepthTestState(bool enable)
	{
		zaap::graphics::Renderer::SetDepthTestState(enable);
	}
	void Renderer::SetAlphaChanelState(bool enable)
	{
		zaap::graphics::Renderer::SetAlphaChanelState(enable);
	}

	//Util
	void Renderer::PrepareFrame()
	{
		zaap::graphics::Renderer::PrepareFrame();
	}
	void Renderer::Cleanup()
	{
		zaap::graphics::Renderer::Cleanup();
	}

	//getters
	Matrix4^ Renderer::GetProjectionMatrix()
	{
		return gcnew Matrix4(&zaap::graphics::Renderer::GetProjectionMatrix());
	}
}
