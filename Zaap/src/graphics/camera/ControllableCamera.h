#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/camera/Camera.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API ControllableCamera : public Camera
	{
	private:
		float m_Speed = 0.1f;
		float m_MouseSensitivity = 0.2f;
	public:
		ControllableCamera(math::Vec3 &position = math::Vec3(), float yaw = 0, float pitch = 0, float fovX = DEFAULT_FOV, float fovY = DEFAULT_FOV);

		void update() override;

		float getSpeed() const;
		void setSpeed(float speed);
	};

}}