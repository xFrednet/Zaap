#include "ControllableCamera.h"

#include <events/Input.h>

namespace zaap { namespace graphics {
	
	ControllableCamera::ControllableCamera(math::Vec3& position, float yaw, float pitch, float fovX, float fovY)
		: Camera(position, yaw, pitch, fovX, fovY)
	{
		
	}

	void ControllableCamera::update()
	{
		if (events::Input::IsButtonPressed(ZAAP_MOUSE_LEFT))
		{
			math::Vec2 m = events::Input::GetMouseMotion();
			addToYaw(m.X * m_MouseSensitivity);
			addToPitch(m.Y * m_MouseSensitivity); 
		}
		math::Vec3 v(0.0f, 0.0f, 0.0f);

		if (events::Input::IsKeyDown(ZAAP_VK_W))		v.Z -= m_Speed;
		if (events::Input::IsKeyDown(ZAAP_VK_A))		v.X -= m_Speed;
		if (events::Input::IsKeyDown(ZAAP_VK_S))		v.Z += m_Speed;
		if (events::Input::IsKeyDown(ZAAP_VK_D))		v.X += m_Speed;
		if (events::Input::IsKeyDown(ZAAP_VK_SPACE))	v.Y += m_Speed;
		if (events::Input::IsKeyDown(ZAAP_VK_SHIFT))	v.Y -= m_Speed;

		float angle = (PI / 180.0f) * m_Yaw;

		m_Position.X += v.Z * sin(-angle);
		m_Position.Z += v.Z * cos(angle);

		m_Position.X += v.X * cos(-angle);
		m_Position.Z += v.X * sin(angle);

		m_Position.Y += v.Y;
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