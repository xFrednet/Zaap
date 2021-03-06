﻿#include "Renderer3D.h"
#include <app/Window.h>

#include "Scene.h"
#include <events/EventManager.h>
#include <events/WindowEvent.h>
#include <events/Input.h>

#ifdef ZAAP_INCLUDE_DIRECTX
#	include "API/DX/DXRenderer3D.h"
#endif
namespace zaap { namespace graphics {
	
	Renderer3D* Renderer3D::CreateNewInstance()
	{
		// the scene deletes it's own instance

#ifdef ZAAP_INCLUDE_DIRECTX
		return new DX::DXRenderer3D(); 
#endif
		return nullptr;
	}

	// The shaders should be internalized by API renderer
	//
	Renderer3D::Renderer3D(ZA_RENDERER_TARGET_TYPE renderTargetType)
		: m_RenderTarget(nullptr),
		m_DepthStencil(nullptr), 
		m_ActiveShaderType(ZA_SHADER_UNKNOWN),
		m_DefaultShader(nullptr),
		m_TerrainShader(nullptr)
	{

		if (renderTargetType == ZA_RENDERER_TARGET_DEFAULT)
			m_RenderTargetType = ZA_RENDERER_TARGET_CONTEXT_TARGET;
		else
			m_RenderTargetType = renderTargetType;

		if (m_RenderTargetType == ZA_RENDERER_TARGET_CONTEXT_TARGET)
		{
			m_RenderTarget = API::Context::GetRenderTarget();
			m_RenderTarget->addUpdateListener(ZA_METHOD_0(Renderer3D::renderTargetUpdated));

			updateProjectionMatrix();
		}
	}

	Renderer3D::~Renderer3D()
	{
		if (m_DefaultShader)
		{
			delete m_DefaultShader;
			m_DefaultShader = nullptr;
		}
		if (m_TerrainShader)
		{
			delete m_TerrainShader;
			m_TerrainShader = nullptr;
		}
	}

	void Renderer3D::loadTransformationMatrix(const Mat4& transformationMatrix) const
	{
		switch (m_ActiveShaderType)
		{
		case ZA_SHADER_DEFAULT_SHADER:
			if (m_DefaultShader)
				m_DefaultShader->setTransformationMatrix(transformationMatrix);
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
		if (m_DefaultShader)
			m_DefaultShader->loadLightSetup(LightSetup);
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
			m_DefaultShader->loadScene(scene);
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
		case ZA_SHADER_DEFAULT_SHADER:
			return m_DefaultShader;
		case ZA_SHADER_TERRAIN_SHADER:
			return m_TerrainShader;
		case ZA_SHADER_UNKNOWN:
		default:
			return nullptr;
		}
	}

	void Renderer3D::setCustomRenderTarget(API::RenderTarget* renderTarget)
	{
		m_RenderTarget = renderTarget;
		renderTargetUpdated();
		m_RenderTarget->addUpdateListener(ZA_METHOD_0(Renderer3D::renderTargetUpdated));
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

		if (m_RenderTarget->getWidth() == 0) // TODO add a error message
			aspect = 1.0f;
		else
			aspect = (float)m_RenderTarget->getWidth() / (float)m_RenderTarget->getHeight();

		CreateProjectionMatrix(&m_ProjectionMatrix, m_FOV, aspect, m_NearPlane, m_FarPlane);
	}
	void Renderer3D::updateProjectionMatrix()
	{
		calulateProjectionMatrix();

		if (m_DefaultShader)
			m_DefaultShader->setProjectionMatrix(m_ProjectionMatrix);
		if (m_TerrainShader)
			m_TerrainShader->setProjectionMatrix(m_ProjectionMatrix);
	}
	Mat4 Renderer3D::getProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}
	void Renderer3D::setProjectionMatrix(const Mat4& projectionMatrix)
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
