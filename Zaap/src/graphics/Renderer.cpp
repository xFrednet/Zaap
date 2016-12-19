#include "Renderer.h"


#include "util/Console.h"
#include "API/DX/DXRenderer.h"
#include "API/DX/shader/types/DXFontShader2D.h"
#include "API/DX/shader/types/DXTextureShader.h"
#include "API/DX/shader/types/DXMaterialShader.h"
#include "API/DX/shader/types/DXTerrainShader.h"
#include <events/Input.h>
#include "camera/ControllableCamera.h"


namespace zaap { namespace graphics {

	Renderer* Renderer::s_Instance = nullptr;

	Renderer::Renderer()
		: m_ActiveShaderType(ZA_SHADER_UNKNOWN)
	{
		Input::AddWindowCallback(ZA_METHOD_1(Renderer::windowCallback));
	}

	void Renderer::startShader(ZA_SHADER_TYPE shader)
	{
		if (shader == m_ActiveShaderType || shader == ZA_SHADER_UNKNOWN) return;
		
		Shader* cShader = getShader(m_ActiveShaderType);
		if (cShader)
			cShader->stop();

		m_ActiveShaderType = shader;
		
		cShader = getShader(m_ActiveShaderType);
		if (cShader)
			cShader->start();
	}
	Shader* Renderer::getShader(ZA_SHADER_TYPE shader)
	{
		switch (shader)
		{
		case ZA_SHADER_TEXTURE_SHADER:
			return m_TextureShader;
		case ZA_SHADER_MATERIAL_SHADER:
			return m_MaterialShader;
		case ZA_SHADER_TERRAIN_SHADER:
			return m_TerrainShader;
		case ZA_SHADER_FONT_SHADER_2D:
			return m_FontShader2D;
		case ZA_SHADER_UNKNOWN:
		default:
			return nullptr;
		}
	}

	void Renderer::setTransformationMatrix(const Mat4& matrix)
	{
		switch (m_ActiveShaderType)
		{
		case ZA_SHADER_TEXTURE_SHADER:
			m_TextureShader->setTransformationMatrix(matrix);
			return;
		case ZA_SHADER_MATERIAL_SHADER:
			m_MaterialShader->setTransformationMatrix(matrix);
			return;
		case ZA_SHADER_TERRAIN_SHADER:
			m_TerrainShader->setTransformationMatrix(matrix);
			return;
		case ZA_SHADER_FONT_SHADER_2D:
		case ZA_SHADER_UNKNOWN:
		default:
			return;
		}
	}

	void Renderer::setViewMatrix(const Mat4& mat)
	{
		m_MaterialShader->setViewMatrix(mat);
		m_TextureShader->setViewMatrix(mat);
		m_TerrainShader->setViewMatrix(mat);
	}

	//
	// private Util
	//
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
	void Renderer::caluclateProjectionMatrix()
	{
		if (m_Size.Y == 0) //TODO add Error Message if y == 0 and get the size from the window
		{
			m_Size.X = 16;
			m_Size.Y = 9;
		}
		CreateProjectionMatrix(&m_ProjectionMatrix, m_FOV, (m_Size.X / m_Size.Y), m_NearPlane, m_FarPlane);
	}

}}

//
// Static members
//
namespace zaap { namespace graphics {
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

	//
	// Shader stuff
	//
	void Renderer::StartShader(ZA_SHADER_TYPE shader)
	{
		s_Instance->startShader(shader);
	}
	Shader* Renderer::GetShader(ZA_SHADER_TYPE shader)
	{
		return s_Instance->getShader(shader);
	}

	void Renderer::SetTransformationMatrix(const Mat4& matrix)
	{
		s_Instance->setTransformationMatrix(matrix);
	}

	//
	//Render
	//
	void Renderer::Render(const scene::Terrain const *terrainTile)
	{
		s_Instance->render(terrainTile);
	}
	void Renderer::Render(Entity* entity)
	{ }
	void Renderer::RenderEntityArray(const std::vector<Entity*>& Entities)
	{

	}

	//
	//Camera
	//
	void Renderer::SetViewMatrix(const Mat4& mat)
	{
		if (s_Instance)
			s_Instance->setViewMatrix(mat);
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
	{
		s_Instance->prepareFrame();
	}
	void Renderer::Cleanup()
	{
		s_Instance->cleanup();
		
		//fontShader
		s_Instance->m_FontShader2D->cleanup();
		delete s_Instance->m_FontShader2D;

		//if (s_Instance->m_Camera) delete s_Instance->m_Camera;

		delete s_Instance;
		ZAAP_CLEANUP_INFO();
	}

	//
	//getters
	//
	Mat4 Renderer::GetProjectionMatrix()
	{
		if (s_Instance)
			return s_Instance->m_ProjectionMatrix;

		return Mat4();
	}
}}
