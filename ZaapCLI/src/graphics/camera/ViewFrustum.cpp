#include "ViewFrustum.h"

namespace ZaapCLI {
	ViewFrustum::ViewFrustum()
		: ManagedClass(new zaap::graphics::ViewFrustum())
	{
	}
	ViewFrustum::ViewFrustum(zaap::graphics::ViewFrustum* instance)
		: ManagedClass(instance)
	{
	}
	ViewFrustum::ViewFrustum(float angle, float ratio, float nearPlane, float farPlane)
		: ManagedClass(new zaap::graphics::ViewFrustum(angle, ratio, nearPlane, farPlane))
	{
	}

	void ViewFrustum::setInternals(float angle, float ratio, float nearPlane, float farPlane)
	{
		m_Instance->setInternals(angle, ratio, nearPlane, farPlane);
	}
	void ViewFrustum::calculateFrustum(Matrix4^ projectionMatrix, Matrix4^ viewMatrix)
	{
		m_Instance->calculateFrustum(*projectionMatrix->getHandle(), *viewMatrix->getHandle());
	}

	bool ViewFrustum::isVisible(Vector3^ point)
	{
		return m_Instance->isVisible(*point->getHandle());
	}
	bool ViewFrustum::isCuboidVisible(Vector3^ min, Vector3^ max)
	{
		return m_Instance->isCuboidVisible(*min->getHandle(), *max->getHandle());
	}
}
