#pragma once

#include "Common.h"
#include "graphics/camera/Camera.h"
#include <entity/Entity.h>
#include <entity/light/LightSetup.h>
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

		Camera* m_Camera;

		ZA_SHADER_TYPE m_ActiveShader;
		FontShader2D* m_FontShader2D;
		MaterialShader *m_MaterialShader;
		TextureShader *m_TextureShader;
		TerrainShader *m_TerrainShader;

		//Init
		Renderer();
		virtual void init() = 0;

		//Shader stuff
		void startShader(ZA_SHADER_TYPE shader);
		Shader* getShader(ZA_SHADER_TYPE shader);

		//Render
		virtual void render(const scene::Terrain const *terrainTile) = 0;
		virtual void render(Entity* model) = 0;

		//Camera
		virtual void setViewMatrix(const Mat4& mat);
		virtual void setCamera(Camera* camera, bool deleteOldCamera = true);
		virtual Camera* getCamera();
		virtual ViewFrustum getViewFrustum();
		virtual Mat4 getViewMatrix();

		//Render options
		virtual void setDepthTestState(bool enable) = 0;
		virtual void setAlphaChanelState(bool enable) = 0;

		//Util
		virtual void prepareFrame() = 0;
		virtual void cleanup() = 0;
		virtual void resize(uint width, uint height) = 0;
		
		void windowCallback(const Event& windowEvent) const;
		void caluclateProjectionMatrix();

	public:
		//Init
		static void Init();

		//Shader stuff
		static void StartShader(ZA_SHADER_TYPE shader);
		static Shader* GetShader(ZA_SHADER_TYPE shader);

		//Render
		static void Render(const scene::Terrain const *terrainTile);
		static void Render(Entity* model);
		static void RenderEntityArray(const std::vector<Entity*>& models);
		
		//Camera
		static void SetViewMatrix(const Mat4& mat);
		static void SetCamera(Camera* camera, bool deleteOldCamera = true);
		static Camera* GetCamera();
		static ViewFrustum GetViewFrustum();

		//Setters
		static void LoadLightSetup(LightSetup* lightSetup);

		//Render options 
		static void SetDepthTestState(bool enable);
		static void SetAlphaChanelState(bool enable);
		
		//Util
		static void PrepareFrame();
		static void Cleanup();

		//getters
		static Mat4 GetProjectionMatrix();

	};

}}
