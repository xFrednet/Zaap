#pragma once

#include "Common.h"
#include "Types.h"
#include "maths\MathHelper.h"

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
		
		float m_FOVX;
		float m_FOVY;
	public:
		Camera(math::Vec3 &position = math::Vec3(), float yaw = 0, float pitch = 0, float fovX = DEFAULT_FOV, float fovY = DEFAULT_FOV);

		virtual void update();
		math::Mat4 getViewMatrix(void);

		//position
		void setPosition(math::Vec3 &position);
		void addToPosition(math::Vec3 &position);
		math::Vec3 getPosition(void) const;
		
		//rotation
		void setRotation(float yaw, float pitch);
		void addToRotation(float yaw, float pitch);
		void addToYaw(float yaw);
		void addToPitch(float pitch);
		float getPitch(void) const;
		float getYaw(void) const;
	};
}}