#include "Camera.h"

namespace ZaapCLI {
	Camera::Camera(zaap::graphics::Camera* instance)
		: m_Instance(instance)
	{
		
	}

	Camera::~Camera()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	Camera::!Camera()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

	void Camera::update()
	{
		m_Instance->update();
	}
	Matrix4^ Camera::getViewMatrix()
	{
		return gcnew Matrix4(&m_Instance->getViewMatrix());
	}
	void Camera::calculateViewFrustum()
	{
		m_Instance->calculateViewFrustum();
	}
	ViewFrustum^ Camera::getViewFrustum()
	{
		return gcnew ViewFrustum(&m_Instance->getViewFrustum());
	}

	//position
	void Camera::setPosition(Vector3^ position)
	{
		m_Instance->setPosition(*position->getHandle());
	}
	void Camera::addToPosition(Vector3^ position)
	{
		m_Instance->addToPosition(*position->getHandle());
	}
	Vector3^ Camera::getPosition()
	{
		return gcnew Vector3(&m_Instance->getPosition());
	}

	//rotation
	void Camera::setRotation(float yaw, float pitch)
	{
		m_Instance->setRotation(yaw, pitch);
	}
	void Camera::addToRotation(float yaw, float pitch)
	{
		m_Instance->addToRotation(yaw, pitch);
	}
	void Camera::addToYaw(float yaw)
	{
		m_Instance->addToYaw(yaw);
	}
	void Camera::addToPitch(float pitch)
	{
		m_Instance->addToPitch(pitch);
	}
	float Camera::getPitch()
	{
		return m_Instance->getPitch();
	}
	float Camera::getYaw()
	{
		return m_Instance->getYaw();
	}
}
