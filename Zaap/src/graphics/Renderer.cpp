#include "Renderer.h"


#include "util/Console.h"
#include "API/DX/DXRenderer.h"
#include "API/DX/shader/types/DXFontShader2D.h"
#include "API/DX/shader/types/DXTextureShader.h"
#include "API/DX/shader/types/DXMaterialShader.h"
#include "API/DX/shader/types/DXTerrainShader.h"
#include <events/Input.h>


namespace zaap { namespace graphics {
		
	Renderer* Renderer::s_Instance = nullptr;

	Renderer::Renderer()
	{
		Input::AddWindowCallback(METHOD_1(&Renderer::windowCallback));
	}

	void Renderer::caluclateProjectionMatrix()
	{
		if (m_Size.Y == 0) //TODO add Error Message if y == 0 and get the size from the window
		{
			m_Size.X = 16;
			m_Size.Y = 9;
		}
		m_ProjectionMatrix = CreateProjectionMatrix(m_FOV, (m_Size.X / m_Size.Y), m_NearPlane, m_FarPlane);
	}


	//
	//Init
	//
	void Renderer::Init()
	{
		s_Instance = new DX::DXRenderer();

		//Shader init
		s_Instance->m_FontShader2D = new DX::DXFontShader2D();
		s_Instance->m_TextureShader = new DX::DXTextureShader();
		s_Instance->m_MaterialShader = new DX::DXMaterialShader();
		s_Instance->m_TerrainShader = new DX::DXTerrainShader();

		s_Instance->caluclateProjectionMatrix();

		s_Instance->init();

	}

	void Renderer::StartFontShader2D()
	{
		s_Instance->m_FontShader2D->start();
	}

	FontShader2D* Renderer::GetFontShader2D()
	{
		return s_Instance->m_FontShader2D;
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
	//Camera
	//
	void Renderer::SetCamera(Camera* camera)
	{ s_Instance->setCamera(camera); }

	Camera* Renderer::GetCamera()
	{
		return s_Instance->getCamera();
	}

	//
	//Setters
	//
	void Renderer::LoadLightSetup(LightSetup* lightSetup)
	{
		s_Instance->m_TerrainShader->loadLightSetup(lightSetup);
		s_Instance->m_TextureShader->loadLightSetup(lightSetup);
		s_Instance->m_MaterialShader->loadLightSetup(lightSetup);
	}

	//
	// Render options
	//
	void Renderer::SetDepthTestState(bool enable)
	{
		s_Instance->setDepthTestState(enable);
	}
	void Renderer::SetAlphaChanelState(bool enable)
	{
		s_Instance->setAlphaChanelState(enable);
	}

	//
	//Util
	//
	void Renderer::PrepareFrame()
	{ s_Instance->prepareFrame(); }
	void Renderer::Cleanup()
	{
		s_Instance->cleanup();
		
		//fontShader
		s_Instance->m_FontShader2D->cleanup();
		delete s_Instance->m_FontShader2D;

		delete s_Instance;
		ZAAP_CLEANUP_LOG("Renderer");
	}
	void Renderer::windowCallback(const Event& windowEvent) const
	{
		if (windowEvent.getEventType() == WINDOW_RESIZE_EVENT)
		{
			if (!s_Instance) return;
			WindowResizeEvent* event = (WindowResizeEvent*)&windowEvent;
			uint width = event->getWidth();
			uint height = event->getHeight();

			s_Instance->m_Size = Vec2((float)width, (float)height); //TODO add a separation option to set the Size
			s_Instance->caluclateProjectionMatrix();

			s_Instance->resize(width, height);
		}

	}

	ViewFrustum Renderer::GetViewFrustum()
	{
		return s_Instance->getViewFrustum();
	}

	Mat4 Renderer::GetProjectionMatrix()
	{
		if (s_Instance)
			return s_Instance->m_ProjectionMatrix;

		return Mat4();
	}
}}
