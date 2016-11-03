#pragma once

#include <ZaapCLI.h>

#include <graphics/camera/Camera.h>
#include "ViewFrustum.h"
#include <maths\Matrix4.h>
#include <maths\Vector3.h>

namespace ZaapCLI {

	//Use ZaapCLI::BaseCamera to cerate a own functional camera

	public ref class Camera
	{
	protected:
		zaap::graphics::Camera* m_Instance;
		
		Camera(zaap::graphics::Camera* instance);
	public:
		~Camera();
		!Camera();

		virtual void update();
		virtual Matrix4^ getViewMatrix();
		void calculateViewFrustum();
		ViewFrustum^ getViewFrustum();

		//position
		virtual void setPosition(Vector3^ position);
		virtual void addToPosition(Vector3^ position);
		Vector3^ getPosition();

		//rotation
		void setRotation(float yaw, float pitch);
		void addToRotation(float yaw, float pitch);
		void addToYaw(float yaw);
		void addToPitch(float pitch);
		float getPitch();
		float getYaw();

		zaap::graphics::Camera* getHandle()
		{
			return m_Instance;
		}
	};
}
