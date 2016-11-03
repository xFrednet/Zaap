﻿#include "ControllableCamera.h"

namespace ZaapCLI {

	zaap::graphics::ControllableCamera* ControllableCamera::getInstance()
	{
		return static_cast<zaap::graphics::ControllableCamera*>(m_Instance);
	}

	ControllableCamera::ControllableCamera()
		: Camera(new zaap::graphics::ControllableCamera())
	{
	}
	ControllableCamera::ControllableCamera(Vector3^ position, float yaw, float pitch, float fov, float fovRatio)
		: Camera(new zaap::graphics::ControllableCamera(*position->getHandle(), yaw, pitch, fov, fovRatio))
	{
	}

	float ControllableCamera::getSpeed()
	{
		return getInstance()->getSpeed();
	}
	void ControllableCamera::setSpeed(float speed)
	{
		getInstance()->setSpeed(speed);
	}
}
