#pragma once

#include <ZaapCLI.h>

#include <graphics/camera/Camera.h>
#include "ViewFrustum.h"
#include <maths\Matrix4.h>
#include <maths\Vector3.h>

namespace ZaapCLI {

	//TODO add a Redirector Class

	public ref class Camera : public ManagedClass<zaap::graphics::Camera>
	{
	private:
	public:
		Camera();
		Camera(Vector3^ position, float yaw, float pitch, float fov, float fovRatio);
		Camera(Vector3^ position, Vector3^ lookAt, Vector3^ up);

		virtual void update();
		Matrix4^ getViewMatrix();
		void calculateViewFrustum();
		ViewFrustum^ getViewFrustum();

		//position
		virtual void setPosition(Vector3^ position);
		virtual void addToPosition(Vector3^ position);
		Vector3^ getPosition();

		//rotation
		virtual void setRotation(float yaw, float pitch);
		virtual void addToRotation(float yaw, float pitch);
		virtual void addToYaw(float yaw);
		virtual void addToPitch(float pitch);
		virtual float getPitch();
		virtual float getYaw();
	};
}
