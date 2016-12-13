#include "Renderer3D.h"
#include <app/Window.h>

#include "Scene.h"

namespace zaap { namespace graphics {

	Renderer3D* Renderer3D::Init()
	{
		//TODO create a D3D instance
	}

	// The shaders should be internalized by API renderer
	//
	Renderer3D::Renderer3D()
		: m_Rendertarget(nullptr),
		m_ActiveShaderType(ZA_SHADER_UNKNOWN),
		m_TextureShader(nullptr),
		m_MaterialShader(nullptr),
		m_TerrainShader(nullptr),
		m_FontShader2D(nullptr)
	{
		m_Width = Window::GetWidth();
		m_Height = Window::GetWidth();
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
		Mat4 viewMat;
		viewMat = scene->getCamera()->getViewMatrix();
		
		//view matrix
		if (m_TextureShader)
			m_TextureShader->setViewMatrix(viewMat);
		if (m_MaterialShader)
		{
			m_MaterialShader->setViewMatrix(viewMat);
			m_MaterialShader->setCameraPosition(scene->getCamera()->getPosition());
		}
		if (m_TerrainShader)
			m_TerrainShader->setViewMatrix(viewMat);

		//view frustum
		m_ViewFrustum = scene->getCamera()->getViewFrustum();
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
		calulateProjectionMatrix();
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
		calulateProjectionMatrix();
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
		calulateProjectionMatrix();
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
			aspect = m_Width / m_Height;

		CreateProjectionMatrix(&m_ProjectionMatrix, m_FOV, aspect, m_NearPlane, m_FarPlane);
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
