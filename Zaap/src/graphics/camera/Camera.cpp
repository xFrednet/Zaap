#include "Camera.h"
#include <util/Console.h>
#include <events/Input.h>
#include <graphics/Renderer.h>

namespace zaap { namespace graphics {
	
	Camera::Camera(Vec3& position, float yaw, float pitch, float fov, float fovRatio)
		: m_Position(position),
		m_Yaw(yaw), m_Pitch(pitch),
		m_FOV(fov), m_FOVRatio(fovRatio)
	{}

	Camera::Camera(Vec3& position, Vec3 lookAt, Vec3 up)
		: m_Position(position),
		m_Yaw(0), m_Pitch(0),
		m_FOV(90), m_FOVRatio(1.775f)
	{

	}

	void Camera::update()
	{}

	Mat4 Camera::getViewMatrix()
	{
		return CreateViewMatrix(m_Position, m_Yaw, m_Pitch);
	}

	void Camera::calculateViewFrustum()
	{
		if (!events::Input::IsKeyDown(ZAAP_VK_V))
			m_Frustum.calculateFrustum(Renderer::GetProjectionMatrix(), getViewMatrix());
		
	}
	ViewFrustum Camera::getViewFrustum() const
	{
		return m_Frustum;
	}

	//
	//position
	//
	void Camera::setPosition(Vec3& position)
	{
		m_Position = position;
	}
	void Camera::addToPosition(Vec3& position)
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
