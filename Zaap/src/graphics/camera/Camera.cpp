#include "Camera.h"
#include <util/Console.h>
#include <events/Input.h>
#include <graphics/Renderer.h>

namespace zaap { namespace graphics {
	
	Camera::Camera(const Vec3 &position, const float &yaw, const float &pitch, const float &fov, const float &fovRatio)
		: m_Position(position),
		m_Yaw(yaw), m_Pitch(pitch),
		m_FOV(fov), m_FOVRatio(fovRatio)
	{
		calculateViewFrustum();
	}
	Camera::Camera(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up)
		: m_Position(position),
		m_Yaw(0), m_Pitch(0),
		m_FOV(90), m_FOVRatio(1.775f)
	{
		calculateViewFrustum();
	}

	void Camera::update()
	{}
	Mat4 Camera::getViewMatrix()
	{
		return CreateViewMatrix(m_Position, m_Yaw, m_Pitch);
	}
	void Camera::calculateViewFrustum()
	{
		m_Frustum.calculateFrustum(Renderer::GetProjectionMatrix(), getViewMatrix());
	}
	ViewFrustum Camera::getViewFrustum() const
	{
		return m_Frustum;
	}

	//
	//position
	//
	void Camera::setPosition(const Vec3& position)
	{
		m_Position = position;
	}
	void Camera::addToPosition(const Vec3& position)
	{
		m_Position += position;
	}
	Vec3 Camera::getPosition() const
	{
		return m_Position;
	}

	//
	//rotation
	//
	void Camera::setRotation(const float &yaw, const float &pitch)
	{
		m_Yaw = yaw;
		m_Pitch = pitch;
	}
	void Camera::addToRotation(const float &yaw, const float &pitch)
	{
		addToYaw(yaw);
		addToPitch(pitch);
	}

	void Camera::addToYaw(const float& yaw)
	{
		m_Yaw += yaw;
	}
	void Camera::addToPitch(const float& pitch)
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
			return;
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
