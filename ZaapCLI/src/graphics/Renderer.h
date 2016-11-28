#pragma once

#include <ZaapCLI.h>

#include <graphics/Renderer.h>

#include "../entity/Entity.h"
#include "scene.h"
#include "camera\Camera.h"
#include "camera\ViewFrustum.h"
#include "../entity/light/LightSetup.h"
#include <maths/Matrix4.h>

namespace ZaapCLI {

	public ref class Renderer
	{
	private:
	public:
		//Init
		static void Init();

		//Shader stuff
		//static void StartShader(ZA_SHADER_TYPE shader);
		//static Shader* GetShader(ZA_SHADER_TYPE shader);

		//Render
		static void Render(Terrain^ terrainTile);
		static void Render(Entity^ model);

		//Camera
		static void SetCamera(Camera^ camera); //deleteOldCamera = true
		static void SetCamera(Camera^ camera, bool deleteOldCamera);
		static Camera^ GetCamera();
		static ViewFrustum^ GetViewFrustum();

		//Setters
		static void LoadLightSetup(LightSetup^ lightSetup);

		//Render options 
		static void SetDepthTestState(bool enable);
		static void SetAlphaChanelState(bool enable);

		//Util
		static void PrepareFrame();
		static void Cleanup();

		//getters
		static Matrix4^ GetProjectionMatrix();
	};
}
