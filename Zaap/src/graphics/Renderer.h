#pragma once

#include "Common.h"
#include "graphics/camera/Camera.h"
#include <entity/Entity.h>
#include <graphics/light/LightSetup.h>
#include <scene/terrain/Terrain.h>
#include <graphics/camera/ViewFrustum.h>
#include "shader/fontShader/FontShader2D.h"

namespace zaap { namespace graphics {

	class ZAAP_API Renderer
	{
	private:
		static Renderer* s_Instance;
	protected:
		math::Vec2 m_Size;
		float m_FOV = 90.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		math::Mat4 m_ProjectionMatrix;

		FontShader2D* m_FontShader2D;

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
		virtual ViewFrustum getViewFrustum(void) = 0;
		
		void caluclateProjectionMatrix();

	public:
		//Init
		static void Init();

		//Shader stuff
		static void StartFontShader2D();
		static FontShader2D* GetFontShader2D();

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

		//getters
		static ViewFrustum GetViewFrustum();
		static math::Mat4 GetProjectionMatrix();
	};

}}
