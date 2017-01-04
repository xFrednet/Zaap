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
			FRONT, //near
			BACK // far
		};

		Plane3D m_Sides[6];

		float m_Angle, m_Ratio, m_NearPlane, m_FarPlane;
		float m_NearPlaneWidth, m_NearPlaneHeight; 
		float m_FarPlaneWidth, m_FarPlaneHeight;
	public:
		ViewFrustum();
		ViewFrustum(const float& angle, const float& ratio, const float& nearPlane, const float& farPlane);

		void setInternals(const float& angle, const float& ratio, const float& nearPlane, const float& farPlane);
		void calculateFrustum(const Mat4& projectionMatrix, const Mat4& viewMatrix);

		bool isVisible(const Vec3& point) const;
		bool isCuboidVisible(const Vec3& min, const Vec3& max) const;
		bool isSphereVisible(const Vec3& position, const float& radius) const;
	};

}}
