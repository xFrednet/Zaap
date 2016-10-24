#pragma once

#include "Common.h"
#include "graphics/camera/Camera.h"
#include <entity/Entity.h>
#include <graphics/light/LightSetup.h>
#include <scene/terrain/Terrain.h>
#include <graphics/camera/ViewFrustum.h>
#include "shader/types/FontShader2D.h"
#include "shader/types/MaterialShader.h"
#include "shader/types/TextureShader.h"
#include "shader/types/TerrainShader.h"

namespace zaap { namespace graphics {

	class ZAAP_API Renderer
	{
	private:
		static Renderer* s_Instance;
	protected:
		Vec2 m_Size;
		float m_FOV = 90.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		Mat4 m_ProjectionMatrix;

		FontShader2D* m_FontShader2D;
		MaterialShader *m_MaterialShader;
		TextureShader *m_TextureShader;
		TerrainShader *m_TerrainShader;

		//Init
		Renderer();
		virtual void init() = 0;

		//Render
		virtual void render(const scene::Terrain const *terrainTile) = 0;
		virtual void render(Entity* model) = 0;

		//Camera
		virtual void setCamera(Camera* camera) = 0;
		virtual Camera* getCamera() = 0;

		//Render options
		virtual void setDepthTestState(bool enable) = 0;
		virtual void setAlphaChanelState(bool enable) = 0;

		//Util
		virtual void prepareFrame() = 0;
		virtual void cleanup() = 0;
		virtual void resize(uint width, uint height) = 0;
		virtual ViewFrustum getViewFrustum(void) = 0;
		
		void windowCallback(const Event& windowEvent) const;
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
		
		//Camera
		static void SetCamera(Camera* camera);
		static Camera* GetCamera();

		//Setters
		static void LoadLightSetup(LightSetup* lightSetup);

		//Render options 
		static void SetDepthTestState(bool enable);
		static void SetAlphaChanelState(bool enable);
		
		//Util
		static void PrepareFrame();
		static void Cleanup();

		//getters
		static ViewFrustum GetViewFrustum();
		static Mat4 GetProjectionMatrix();
	};

}}
