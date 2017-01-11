#include "Renderer3D.h"

#include "Scene.h"

namespace ZaapCLI
{
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructor //
	/* //////////////////////////////////////////////////////////////////////////////// */
	Renderer3D::Renderer3D()
		: ManagedClass(zaap::graphics::Renderer3D::CreateNewInstance())
	{
		
	}

	Renderer3D::Renderer3D(zaap::graphics::Renderer3D* instance)
		: ManagedClass(instance)
	{
		
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Shader stuff //
	/* //////////////////////////////////////////////////////////////////////////////// */

	void Renderer3D::loadTransformationMatrix(Matrix4^ transformationMatrix)
	{
		m_Instance->loadTransformationMatrix(*transformationMatrix->getHandle());
	}

	void Renderer3D::loadLightSetup(LightSetup^ lightSetup)
	{
		m_Instance->loadLightSetup(*lightSetup->getHandle());
	}

	void Renderer3D::loadScene(Scene^ scene)
	{
		m_Instance->loadScene(scene->getHandle());
	}

	void Renderer3D::startShader(ZA_SHADER_TYPE shader)
	{
		m_Instance->startShader(to_CPP_ZAShaderType(shader));
	}

	Shader^ Renderer3D::getShader(ZA_SHADER_TYPE shader)
	{
		return gcnew Shader(m_Instance->getShader(to_CPP_ZAShaderType(shader)));
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Frame related // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	void Renderer3D::setCustomRenderTarget(Texture2D^ target, uint width, uint height)
	{
		m_Instance->setCustomRenderTarget(target->getHandle(), width, height);
	}

	void Renderer3D::diableCustomRenderTarget()
	{
		m_Instance->setCustomRenderTarget(nullptr, 0, 0);
	}

	void Renderer3D::prepareFrame()
	{
		m_Instance->prepareFrame();
	}

	void Renderer3D::presentFrame()
	{
		m_Instance->prepareFrame();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Rendering options //
	/* //////////////////////////////////////////////////////////////////////////////// */

	void Renderer3D::setAlphaTestingState(bool enable)
	{
		m_Instance->setAlphaTestingState(enable);
	}
	void Renderer3D::enableAlphaTesting()
	{
		m_Instance->enableAlphaTesting();
	}
	void Renderer3D::disableAlphaTesting()
	{
		m_Instance->disableAlphaTesting();
	}

	void Renderer3D::setDepthTestingState(bool enable)
	{
		m_Instance->setDepthTestingState(enable);
	}
	void Renderer3D::enableDepthTesting()
	{
		m_Instance->enableDepthTesting();
	}
	void Renderer3D::disableDepthTesting()
	{
		m_Instance->disableDepthTesting();
	}

	void Renderer3D::resize(uint width, uint height)
	{
		m_Instance->resize(width, height);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Values //
	/* //////////////////////////////////////////////////////////////////////////////// */

	float Renderer3D::getFOV()
	{
		return m_Instance->getFOV();
	}
	void Renderer3D::setFOV(float fov)
	{
		m_Instance->setFOV(fov);
	}

	float Renderer3D::getNearPlane()
	{
		return m_Instance->getNearPlane();
	}
	void Renderer3D::setNearPlane(float nearPlane)
	{
		m_Instance->setNearPlane(nearPlane);
	}

	float Renderer3D::getFarPlane()
	{
		return m_Instance->getFarPlane();
	}
	void Renderer3D::setFarPlane(float farPlane)
	{
		m_Instance->setFarPlane(farPlane);
	}

	void Renderer3D::calulateProjectionMatrix()
	{
		m_Instance->calulateProjectionMatrix();
	}
	void Renderer3D::updateProjectionMatrix()
	{
		m_Instance->updateProjectionMatrix();
	}
	Matrix4^ Renderer3D::getProjectionMatrix()
	{
		return gcnew Matrix4(&m_Instance->getProjectionMatrix());
	}
	void Renderer3D::setProjectionMatrix(Matrix4^ projectionMatrix)
	{
		m_Instance->setProjectionMatrix(*projectionMatrix->getHandle());
	}

	ViewFrustum^ Renderer3D::getViewFrustum()
	{
		return gcnew ViewFrustum(&m_Instance->getViewFrustum());
	}
}