#include "BaseCamera.h"

//
// CameraRedirector
//
namespace ZaapCLI {
	//Value Methods to excess the protected Values directly
	zaap::Vec3 CameraRedirector::getPositionValue()
	{
		return m_Position;
	}
	float CameraRedirector::getYawValue()
	{
		return m_Yaw;
	}
	float CameraRedirector::getPitchValue()
	{
		return m_Pitch;
	}

	void CameraRedirector::setPositionValue(zaap::Vec3 position)
	{
		m_Position = position;
	}
	void CameraRedirector::setYawValue(float yaw)
	{
		m_Yaw = yaw;
	}
	void CameraRedirector::setPitchValue(float pitch)
	{
		m_Pitch = pitch;
	}

	//Actual class
	CameraRedirector::CameraRedirector(ZaapCLI::BaseCamera^ owner)
		: zaap::graphics::Camera(),
		m_Owner(owner)
	{
	}
	CameraRedirector::CameraRedirector(ZaapCLI::BaseCamera^ owner, zaap::Vec3 position, float yaw, float pitch)
		: zaap::graphics::Camera(position, yaw, pitch),
		m_Owner(owner)
	{
	}
	CameraRedirector::CameraRedirector(ZaapCLI::BaseCamera^ owner, zaap::Vec3 position, zaap::Vec3 lookAt, zaap::Vec3 up)
		: zaap::graphics::Camera(position, lookAt, up),
		m_Owner(owner)
	{
	}

	void CameraRedirector::update()
	{
		m_Owner->update();
	}
	void CameraRedirector::callDefault_update()
	{
		zaap::graphics::Camera::update();
	}
	void CameraRedirector::setPosition(const zaap::Vec3 &position)
	{
		m_Owner->setPosition(gcnew Vector3(position.X, position.Y, position.Z));
	}
	void CameraRedirector::callDefault_setPosition(const zaap::Vec3 &position)
	{
		zaap::graphics::Camera::setPosition(position);
	}
	void CameraRedirector::addToPosition(const zaap::Vec3 &position)
	{
		m_Owner->addToPosition(gcnew Vector3(position.X, position.Y, position.Z));
	}
	void CameraRedirector::callDefault_addToPosition(const zaap::Vec3 &position)
	{
		zaap::graphics::Camera::setPosition(position);
	}

	zaap::Mat4 CameraRedirector::getViewMatrix()
	{
		return *m_Owner->getViewMatrix()->getHandle();
	}
	zaap::Mat4 CameraRedirector::callDefault_getViewMatrix()
	{
		return zaap::graphics::Camera::getViewMatrix();
	}
}

//
// BaseCamera
//
namespace ZaapCLI {

	CameraRedirector* BaseCamera::getInstance()
	{
		return static_cast<CameraRedirector*>(m_Instance);
	}

	BaseCamera::BaseCamera()
		: Camera(new CameraRedirector(this))
	{
	}
	BaseCamera::BaseCamera(Vector3^ position, float yaw, float pitch)
		: Camera(new CameraRedirector(this, *position->getHandle(), yaw, pitch))
	{
	}
	BaseCamera::BaseCamera(Vector3^ position, Vector3^ lookAt, Vector3^ up) 
		: Camera(new CameraRedirector(this, *position->getHandle(), *lookAt->getHandle(), *up->getHandle()))
	{
	}

	void BaseCamera::update()
	{
		getInstance()->callDefault_update();
	}
	void BaseCamera::setPosition(Vector3^ position)
	{
		getInstance()->callDefault_setPosition(*position->getHandle());
	}
	void BaseCamera::addToPosition(Vector3^ position)
	{
		getInstance()->callDefault_addToPosition(*position->getHandle());
	}
	
	Matrix4^ BaseCamera::getViewMatrix()
	{
		return gcnew Matrix4(&getInstance()->callDefault_getViewMatrix());
	}
}
