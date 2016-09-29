#include "Renderer.h"

#include "DX/DXRenderer.h"
#include "util/Console.h"
#include "shader/fontShader/DXFontShader2D.h"

namespace zaap { namespace graphics {
		
	Renderer* Renderer::s_Instance = nullptr;

	void Renderer::caluclateProjectionMatrix()
	{
		if (m_Size.Y == 0) //TODO add Error Message and get the size from the window
		{
			m_Size.X = 16;
			m_Size.Y = 9;
		}
		m_ProjectionMatrix = math::CreateProjectionMatrix(m_FOV, (m_Size.X / m_Size.Y), m_NearPlane, m_FarPlane);
	}

	//
	//Init
	//
	void Renderer::Init()
	{
		s_Instance = new DX::DXRenderer();
		s_Instance->m_FontShader2D = new DX::DXFontShader2D();

		s_Instance->caluclateProjectionMatrix();

		s_Instance->init();
	}

	void Renderer::StartFontShader2D()
	{
		((DX::DXFontShader2D*)s_Instance->m_FontShader2D)->start();
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
		
		//fontShader
		((DX::DXFontShader2D*)s_Instance->m_FontShader2D)->cleanup();
		delete ((DX::DXFontShader2D*)s_Instance->m_FontShader2D);

		delete s_Instance;
		ZAAP_CLEANUP_LOG("Renderer");
	}
	void Renderer::Resize(uint width, uint height)
	{
		if (s_Instance)
		{
			s_Instance->m_Size = math::Vec2((float)width, (float)height); //TODO add a seperate option to set the Size
			s_Instance->caluclateProjectionMatrix();

			s_Instance->resize(width, height);
		}
	}

	ViewFrustum Renderer::GetViewFrustum()
	{
		return s_Instance->getViewFrustum();
	}

	math::Mat4 Renderer::GetProjectionMatrix()
	{
		if (s_Instance)
			return s_Instance->m_ProjectionMatrix;

		return math::Mat4();
	}
}}
