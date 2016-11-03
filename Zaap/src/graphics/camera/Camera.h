#pragma once

#include <graphics/API/DX/DXCommon.h>
#include <maths/MathHelper.h>
#include "ViewFrustum.h"

#ifndef DEFAULT_FOV
#	define DEFAULT_FOV 90.0f
#endif

namespace zaap { namespace graphics {
		
	class ZAAP_API Camera
	{
	protected:
		Vec3 m_Position;

		float m_Yaw;
		float m_Pitch;
		
		float m_FOV;
		float m_FOVRatio;

		ViewFrustum m_Frustum;
	public:
		virtual ~Camera()
		{
		}

		Camera(const Vec3 &position = Vec3(), const float &yaw = 0, const float & pitch = 0, const float & fov = DEFAULT_FOV, const float & fovRatio = 1.775f);
		Camera(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up);

		virtual void update();
		virtual Mat4 getViewMatrix();
		void calculateViewFrustum();
		ViewFrustum getViewFrustum() const;

		//position
		virtual void setPosition(const Vec3 &position);
		virtual void addToPosition(const Vec3 &position);
		Vec3 getPosition() const;

		//rotation
		virtual void setRotation(const float& yaw, const float& pitch);
		virtual void addToRotation(const float& yaw, const float& pitch);
		virtual void addToYaw(const float& yaw);
		virtual void addToPitch(const float& pitch);
		virtual float getPitch() const;
		virtual float getYaw() const;
	};
}}