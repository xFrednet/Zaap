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
		float m_MouseSensitivity = 0.05f;

	public:
		ControllableCamera(const Vec3 &position = Vec3(), float yaw = 0, float pitch = 0, float fov = DEFAULT_FOV, float fovRatio = 1.775f);

		void update() override;

		float getSpeed() const;
		void setSpeed(float speed);
	};

}}