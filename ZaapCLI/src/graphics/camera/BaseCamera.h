#pragma once

#include <ZaapCLI.h>

#include "Camera.h"

#include <maths\Mat4.h>

namespace ZaapCLI {

	ref class BaseCamera;

	class CameraRedirector : public zaap::graphics::Camera {
	private:
		gcroot<ZaapCLI::BaseCamera^> m_Owner;
	public:
		//Value Methods to excess the protected Values directly
		zaap::Vec3 getPositionValue();
		float getYawValue();
		float getPitchValue();
		float getFOVValue();
		float getFOVRatioValue();

		void setPositionValue(zaap::Vec3 position);
		void setYawValue(float yaw);
		void setPitchValue(float pitch);
		void setFOVValue(float fov);
		void setFOVRatioValue(float fovRatio);

		//Actual class
		CameraRedirector(ZaapCLI::BaseCamera^ owner);
		CameraRedirector(ZaapCLI::BaseCamera^ owner, zaap::Vec3 position, float yaw, float pitch, float fov, float fovRatio);
		CameraRedirector(ZaapCLI::BaseCamera^ owner, zaap::Vec3 position, zaap::Vec3 lookAt, zaap::Vec3 up);

		//
		// Virtual methods
		//
		void update() override;
		void callDefault_update();

		void setPosition(const zaap::Vec3 &position) override;
		void callDefault_setPosition(const zaap::Vec3 &position);
		
		void addToPosition(const zaap::Vec3 &position) override;
		void callDefault_addToPosition(const zaap::Vec3 &position);

		zaap::Mat4 getViewMatrix() override;
		zaap::Mat4 callDefault_getViewMatrix();
	};

	public ref class BaseCamera : public Camera
	{
	private:
		CameraRedirector* getInstance();
	protected:
// __FILE__ is always defined
#ifdef __FILE__
			property Vector3^ m_Position {
				Vector3^ get()
				{
					return gcnew Vector3(&getInstance()->getPositionValue());
				}
				void set(Vector3^ position)
				{
					getInstance()->setPositionValue(*position->getHandle());
				}
			}
			property float m_Yaw {
				float get()
				{
					return getInstance()->getYawValue();
				}
				void set(float yaw)
				{
					getInstance()->setYawValue(yaw);
				}
			}
			property float m_Pitch {
				float get()
				{
					return getInstance()->getPitchValue();
				}
				void set(float pitch)
				{
					getInstance()->setPitchValue(pitch);
				}
			}
			property float m_FOV {
				float get()
				{
					return getInstance()->getFOVValue();
				}
				void set(float fov)
				{
					getInstance()->setFOVValue(fov);
				}
			}
			property float m_FOVRatio {
				float get()
				{
					return getInstance()->getFOVRatioValue();
				}
				void set(float FOVRatio)
				{
					getInstance()->setFOVRatioValue(FOVRatio);
				}
			}
#endif
	public:
		BaseCamera();
		BaseCamera(Vector3^ position, float yaw, float pitch, float fov, float fovRatio);
		BaseCamera(Vector3^ position, Vector3^ lookAt, Vector3^ up);

		virtual void update() override;
		virtual void setPosition(Vector3^ position) override;
		virtual void addToPosition(Vector3^ position) override;

		virtual Matrix4^ getViewMatrix() override;
	};
}
