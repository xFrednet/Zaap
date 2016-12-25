#include "Renderer3D.h"
#include <app/Window.h>

#include "Scene.h"
#include <events/EventManager.h>
#include <events/WindowEvent.h>

#ifdef ZAAP_INCLUDE_DIRECTX
#	include "API/DX/DXRenderer3D.h"
#endif
namespace zaap { namespace graphics {

	Renderer3D* Renderer3D::CreateNewInstance()
	{
#ifdef ZAAP_INCLUDE_DIRECTX
		return new DX::DXRenderer3D();
#endif
		return nullptr;
	}

	void Renderer3D::windowCallback(const Event& windowEvent)
	{
		if (windowEvent.getEventType() != WINDOW_RESIZE_EVENT) return;
		
		WindowResizeEvent* event = (WindowResizeEvent*)&windowEvent;
		m_Width = event->getWidth();
		m_Height = event->getHeight();

		calulateProjectionMatrix();

		resize(m_Width, m_Height);

	}

	// The shaders should be internalized by API renderer
	//
	Renderer3D::Renderer3D()
		: m_RenderTarget(nullptr),
		m_DepthStencil(nullptr), 
		m_ActiveShaderType(ZA_SHADER_UNKNOWN),
		m_TextureShader(nullptr),
		m_MaterialShader(nullptr),
		m_TerrainShader(nullptr),
		m_FontShader2D(nullptr)
	{
		m_Width = Window::GetWidth();
		m_Height = Window::GetWidth();

		updateProjectionMatrix();
	}

	void Renderer3D::cleanupBaseRenderer3D()
	{
		if (m_TextureShader)
		{
			m_TextureShader->cleanup();
			delete m_TextureShader;
			m_TextureShader = nullptr;
		}
		if (m_MaterialShader)
		{
			m_MaterialShader->cleanup();
			delete m_MaterialShader;
			m_MaterialShader = nullptr;
		}
		if (m_TerrainShader)
		{
			m_TerrainShader->cleanup();
			delete m_TerrainShader;
			m_TerrainShader = nullptr;
		}
		if (m_FontShader2D)
		{
			m_FontShader2D->cleanup();
			delete m_FontShader2D;
			m_FontShader2D = nullptr;
		}
		if (m_RenderTarget)
		{
			//TODO use the Texture::Delete method when it exist
		}

	}

	void Renderer3D::cleanup()
	{
		cleanupAPIRenderer();
		cleanupBaseRenderer3D();
	}

	void Renderer3D::loadTransformationMatrix(const Mat4& transformationMatrix) const
	{
		switch (m_ActiveShaderType)
		{
		case ZA_SHADER_TEXTURE_SHADER:
			if (m_TextureShader)
				m_TextureShader->setTransformationMatrix(transformationMatrix);
			return;
		case ZA_SHADER_MATERIAL_SHADER:
			if (m_MaterialShader)
				m_MaterialShader->setTransformationMatrix(transformationMatrix);
			return;
		case ZA_SHADER_TERRAIN_SHADER:
			if (m_TerrainShader)
				m_TerrainShader->setTransformationMatrix(transformationMatrix);
			return;
		case ZA_SHADER_FONT_SHADER_2D:
		case ZA_SHADER_UNKNOWN:
		default:
			return;
		}
	}

	void Renderer3D::loadLightSetup(const LightSetup& LightSetup)
	{
		if (m_TextureShader)
			m_TextureShader->loadLightSetup(&LightSetup);
		if (m_MaterialShader)
			m_MaterialShader->loadLightSetup(&LightSetup);
		if (m_TerrainShader)
			m_TerrainShader->loadLightSetup(&LightSetup);
		//TODO all shaders still use pointers instead of the object (change that)
	}

	void Renderer3D::loadScene(const Scene* scene)
	{
		if (!scene)
		{
			//TODO add error message
			return;
		}
		
		if (scene->getCamera())
		{
			Camera* camera = scene->getCamera();
			Mat4 viewMat = camera->getViewMatrix();
		
			//view matrix
			if (m_TextureShader)
				m_TextureShader->setViewMatrix(viewMat);
			if (m_MaterialShader)
			{
				m_MaterialShader->setViewMatrix(viewMat);
				m_MaterialShader->setCameraPosition(camera->getPosition());
			}
			if (m_TerrainShader)
				m_TerrainShader->setViewMatrix(viewMat);

			//view frustum
			camera->calculateViewFrustum(getProjectionMatrix());
			m_ViewFrustum = camera->getViewFrustum();
		}

	}

	void Renderer3D::startShader(ZA_SHADER_TYPE shader)
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

	Shader* Renderer3D::getShader(ZA_SHADER_TYPE shader)
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

	//
	// Alpha testing
	//
	void Renderer3D::enableAlphaTesting() const
	{
		setAlphaTestingState(true);
	}
	void Renderer3D::disableAlphaTesting() const
	{
		setAlphaTestingState(false);
	}

	//
	// Depth testing
	//
	void Renderer3D::enableDepthTesting() const
	{
		setDepthTestingState(true);
	}
	void Renderer3D::disableDepthTesting() const
	{
		setDepthTestingState(false);
	}

	//
	// FOV
	//
	float Renderer3D::getFOV() const
	{
		return m_FOV;
	}
	void Renderer3D::setFOV(const float& fov)
	{
		m_FOV = fov;
		updateProjectionMatrix();
	}
	
	//
	// NearPlane
	//
	float Renderer3D::getNearPlane() const
	{
		return m_NearPlane;
	}
	void Renderer3D::setNearPlane(const float& nearPlane)
	{
		m_NearPlane = nearPlane;
		updateProjectionMatrix();
	}

	//
	// FarPlane
	// 
	float Renderer3D::getFarPlane() const
	{
		return m_FarPlane;
	}
	void Renderer3D::setFarPlane(const float& farPlane)
	{
		m_FarPlane = farPlane;
		updateProjectionMatrix();
	}

	//
	// ProjectionMatrix
	//
	void Renderer3D::calulateProjectionMatrix()
	{
		float aspect;

		if (m_Height == 0) // TODO add a error message
			aspect = 1.0f;
		else
			aspect = (float)m_Width / (float)m_Height;

		CreateProjectionMatrix(&m_ProjectionMatrix, m_FOV, aspect, m_NearPlane, m_FarPlane);
	}
	void Renderer3D::updateProjectionMatrix()
	{
		calulateProjectionMatrix();

		if (m_TextureShader)
			m_TextureShader->setProjectionMatrix(m_ProjectionMatrix);
		if (m_MaterialShader)
			m_MaterialShader->setProjectionMatrix(m_ProjectionMatrix);
		if (m_TerrainShader)
			m_TerrainShader->setProjectionMatrix(m_ProjectionMatrix);

		if (m_FontShader2D)
			m_FontShader2D->setTargetSize(m_Width, m_Height);
	}
	Mat4 Renderer3D::getProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}
	void Renderer3D::setProjectionmatrix(const Mat4& projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;
	}

	//
	// ViewFrustum
	//
	ViewFrustum Renderer3D::getViewFrustum() const
	{
		return m_ViewFrustum;
	}
}}
