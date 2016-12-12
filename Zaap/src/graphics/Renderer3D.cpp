#include "Renderer3D.h"
#include <app/Window.h>

#include "Scene.h"

namespace zaap { namespace graphics {

	Renderer3D* Renderer3D::Init()
	{
		//TODO create a D3D instance
	}

	Renderer3D::Renderer3D()
		: m_ActiveShaderType(ZA_SHADER_UNKNOWN)
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

	void Renderer3D::enableAlphaTesting()
	{
		setAlphaTestingState(true);
	}

	void Renderer3D::disableAlphaTesting()
	{
		setAlphaTestingState(false);
	}

}}
