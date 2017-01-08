#pragma once

#include <ZaapCLI.h>

#include "Camera.h"
#include <graphics/camera/ControllableCamera.h>

namespace ZaapCLI {

	public ref class ControllableCamera : public Camera
	{
	private:
		zaap::graphics::ControllableCamera* getInstance();
	public:
		ControllableCamera();
		ControllableCamera(Vector3^ position, float yaw, float pitch);

		float getSpeed();
		void setSpeed(float speed);
	};
}
