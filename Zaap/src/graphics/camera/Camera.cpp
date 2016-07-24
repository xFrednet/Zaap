#include "Camera.h"
#include <util/Console.h>

namespace zaap { namespace graphics {
	
	Camera::Camera(math::Vec3& position, float yaw, float pitch, float fovX, float fovY)
		: m_Position(position),
		m_Yaw(yaw), m_Pitch(pitch),
		m_FOVX(fovX), m_FOVY(fovY)
	{}

	void Camera::update()
	{}

	math::Mat4 Camera::getViewMatrix()
	{
		return math::CreateViewMatrix(m_Position, getYaw(), getPitch());
	}

	//position
	void Camera::setPosition(math::Vec3& position)
	{
		m_Position = position;
	}
	void Camera::addToPosition(math::Vec3& position)
	{
		m_Position += position;
	}
	math::Vec3 Camera::getPosition() const
	{
		return m_Position;
	}

	//
	//rotation
	//
	void Camera::setRotation(float yaw, float pitch)
	{
		m_Yaw = yaw;
		m_Pitch = pitch;
	}
	void Camera::addToRotation(float yaw, float pitch)
	{
		addToYaw(yaw);
		addToPitch(pitch);
	}

	void Camera::addToYaw(float yaw)
	{
		m_Yaw += yaw;
	}
	void Camera::addToPitch(float pitch)
	{
		m_Pitch += pitch;
		
		if (m_Pitch > 90.0f)
		{
			m_Pitch = 90.0f;
			return;
		}
		if (m_Pitch < -90.0f)
		{
			m_Pitch = -90.0f;
		}

	}

	float Camera::getYaw() const
	{
		return m_Yaw;
	}
	float Camera::getPitch() const
	{
		return m_Pitch;
	}

}}
