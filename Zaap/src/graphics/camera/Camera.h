#pragma once

#include <graphics/API/DXCommon.h>
#include <maths/MathHelper.h>
#include "ViewFrustum.h"

#ifndef DEFAULT_FOV
#	define DEFAULT_FOV 90.0f
#endif

namespace zaap { namespace graphics {
		
	class ZAAP_API Camera
	{
	protected:
		math::Vec3 m_Position;

		float m_Yaw;
		float m_Pitch;
		
		float m_FOV;
		float m_FOVRatio;

		ViewFrustum m_Frustum;
	public:
		Camera(math::Vec3 &position = math::Vec3(), float yaw = 0, float pitch = 0, float fov = DEFAULT_FOV, float fovRatio = 1.775f);
		Camera(math::Vec3 &position, math::Vec3 lookAt, math::Vec3 up);

		virtual void update();
		math::Mat4 getViewMatrix(void);
		void calculateViewFrustum();
		ViewFrustum getViewFrustum() const;

		//position
		virtual void setPosition(math::Vec3 &position);
		virtual void addToPosition(math::Vec3 &position);
		math::Vec3 getPosition(void) const;

		//rotation
		virtual void setRotation(float yaw, float pitch);
		virtual void addToRotation(float yaw, float pitch);
		virtual void addToYaw(float yaw);
		virtual void addToPitch(float pitch);
		virtual float getPitch(void) const;
		virtual float getYaw(void) const;
	};
}}