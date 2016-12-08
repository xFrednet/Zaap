#include "ControllableCamera.h"

#include <events/Input.h>
#include <util/Console.h>

namespace zaap { namespace graphics {
	
	ControllableCamera::ControllableCamera(const Vec3& position, float yaw, float pitch, float fov, float fovRatio)
		: Camera(position, yaw, pitch, fov, fovRatio)
	{
	}

	void ControllableCamera::update()
	{
		if (Input::IsButtonPressed(ZAAP_MOUSE_LEFT))
		{
			Vec2 m = Input::GetMouseMotion();
			addToYaw(m.X * m_MouseSensitivity);
			addToPitch(m.Y * m_MouseSensitivity);
		}

		Vec3 v(0.0f, 0.0f, 0.0f);

		if (Input::IsKeyDown(ZAAP_VK_W))		v.Z -= m_Speed;
		if (Input::IsKeyDown(ZAAP_VK_A))		v.X -= m_Speed;
		if (Input::IsKeyDown(ZAAP_VK_S))		v.Z += m_Speed;
		if (Input::IsKeyDown(ZAAP_VK_D))		v.X += m_Speed;
		if (Input::IsKeyDown(ZAAP_VK_SPACE))	v.Y += m_Speed;
		if (Input::IsKeyDown(ZAAP_VK_SHIFT))	v.Y -= m_Speed;
		if (Input::IsKeyDown(ZAAP_VK_E))		v *= 4;

		float angle = (PI / 180.0f) * m_Yaw;

		m_Position.X += v.Z * sin(-angle);
		m_Position.Z += v.Z * cos(angle);

		m_Position.X += v.X * cos(-angle);
		m_Position.Z += v.X * sin(angle);

		m_Position.Y += v.Y;

		//info
		if (Input::IsKeyPressed(ZAAP_VK_I))
		{
			ZAAP_INFO("Position: " + m_Position.toString());
		}

		//reset
		if (Input::IsKeyPressed(ZAAP_VK_R))
		{
			m_Position = Vec3(12.0f, 12.0f, -1.0f);
			m_Yaw = -90.0;
			m_Pitch = 30.0;
		}
		calculateViewFrustum();
	}

	float ControllableCamera::getSpeed() const
	{
		return m_Speed;
	}

	void ControllableCamera::setSpeed(float speed)
	{
		m_Speed = speed;
	}
}}
