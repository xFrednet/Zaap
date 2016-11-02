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
		Camera(const Vec3 &position = Vec3(), const float &yaw = 0, const float & pitch = 0, const float & fov = DEFAULT_FOV, const float & fovRatio = 1.775f);
		Camera(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up);

		virtual void update();
		Mat4 getViewMatrix() const;
		void calculateViewFrustum();
		ViewFrustum getViewFrustum() const;

		//position
		virtual void setPosition(Vec3 &position);
		virtual void addToPosition(Vec3 &position);
		Vec3 getPosition() const;

		//rotation
		virtual void setRotation(float yaw, float pitch);
		virtual void addToRotation(float yaw, float pitch);
		virtual void addToYaw(float yaw);
		virtual void addToPitch(float pitch);
		virtual float getPitch() const;
		virtual float getYaw() const;
	};
}}