#pragma once

#include <graphics/API/DX/DXCommon.h>
#include <maths/MathUtil.h>
#include "ViewFrustum.h"

namespace zaap { namespace graphics {
		
	class ZAAP_API Camera
	{
	protected:
		Vec3 m_Position;

		float m_Yaw;
		float m_Pitch;

		ViewFrustum m_Frustum;
		
	public:
		virtual ~Camera()
		{
		}

		Camera(const Vec3 &position = Vec3(), const float& yaw = 0, const float& pitch = 0);
		Camera(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up);

		virtual void update();
		virtual Mat4 getViewMatrix();
		inline void calculateViewFrustum();
		// This function returns the last calculated ViewFrustum use calculateViewFrustum()
		// to calculate the frustum
		inline ViewFrustum getViewFrustum() const;

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