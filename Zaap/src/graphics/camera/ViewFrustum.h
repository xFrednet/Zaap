#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {
	class Camera;

	class ZAAP_API ViewFrustum
	{
	private:
		enum {
			LEFT = 0, RIGHT,
			TOP, BOTTOM,
			FRONT, BACK
		};

		math::Plane3D m_Sides[6];

		float m_Angle, m_Ratio, m_NearPlane, m_FarPlane;
		float m_NearPlaneWidth, m_NearPlaneHeight; 
		float m_FarPlaneWidth, m_FarPlaneHeight;
	public:
		ViewFrustum();
		ViewFrustum(float angle, float ratio, float nearPlane, float farPlane);

		void setInternals(float angle, float ratio, float nearPlane, float farPlane);
		void calculateFrustum(math::Mat4 projectionMatrix, math::Mat4 viewMatrix);

		bool isVisible(const math::Vec3 &point) const;
	};

}}
