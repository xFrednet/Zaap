#include "ViewFrustum.h"

#include <graphics/camera/Camera.h>

namespace zaap { namespace graphics {
	
	//
	// Constrictors
	//
	ViewFrustum::ViewFrustum()
		: m_Angle(0), m_Ratio(0), m_NearPlane(0), m_FarPlane(0),
		m_NearPlaneWidth(0), m_NearPlaneHeight(0),
		m_FarPlaneWidth(0), m_FarPlaneHeight(0)
	{
	}

	ViewFrustum::ViewFrustum(float angle, float ratio, float nearPlane, float farPlane)
	{
		setInternals(angle, ratio, nearPlane, farPlane);
	}

	//
	// Setters
	//
	void ViewFrustum::setInternals(float angle, float ratio, float nearPlane, float farPlane)
	{

		m_Angle = angle;
		m_Ratio = ratio;
		m_NearPlane = nearPlane;
		m_FarPlane = farPlane;

		float tang = tan(math::toRadians(m_Angle) / 2.0f);

		//nearPlane
		m_NearPlaneHeight = tang * m_NearPlane;
		m_NearPlaneWidth = m_NearPlaneHeight * m_Ratio;

		//farPlane
		m_FarPlaneHeight = tang * m_FarPlane;
		m_FarPlaneWidth = m_FarPlaneHeight * m_Ratio;
	}

	void ViewFrustum::calculateFrustum(math::Mat4 projectionMatrix, math::Mat4 viewMatrix)
	{
		float zMinimum, r;
		math::Mat4 matrix;

		// Calculate the minimum Z distance in the frustum.
		float screenDepth = m_FarPlane - m_NearPlane;
		zMinimum = -projectionMatrix.m43 / projectionMatrix.m33;
		r = screenDepth / (screenDepth - zMinimum);
		projectionMatrix.m33 = r;
		projectionMatrix.m43 = -r * zMinimum;

		// Create the frustum matrix from the view matrix and updated projection matrix.
		matrix = viewMatrix * projectionMatrix;

		// Calculate near plane of frustum.
		m_Sides[FRONT].A = matrix.m14 + matrix.m13;
		m_Sides[FRONT].B = matrix.m24 + matrix.m23;
		m_Sides[FRONT].C = matrix.m34 + matrix.m33;
		m_Sides[FRONT].D = matrix.m44 + matrix.m43;
		m_Sides[FRONT].normalize();

		// Calculate far plane of frustum.
		m_Sides[BACK].A = matrix.m14 - matrix.m13;
		m_Sides[BACK].B = matrix.m24 - matrix.m23;
		m_Sides[BACK].C = matrix.m34 - matrix.m33;
		m_Sides[BACK].D = matrix.m44 - matrix.m43;
		m_Sides[BACK].normalize();

		// Calculate left plane of frustum.
		m_Sides[LEFT].A = matrix.m14 + matrix.m11;
		m_Sides[LEFT].B = matrix.m24 + matrix.m21;
		m_Sides[LEFT].C = matrix.m34 + matrix.m31;
		m_Sides[LEFT].D = matrix.m44 + matrix.m41;
		m_Sides[LEFT].normalize();

		// Calculate right plane of frustum.
		m_Sides[RIGHT].A = matrix.m14 - matrix.m11;
		m_Sides[RIGHT].B = matrix.m24 - matrix.m21;
		m_Sides[RIGHT].C = matrix.m34 - matrix.m31;
		m_Sides[RIGHT].D = matrix.m44 - matrix.m41;
		m_Sides[RIGHT].normalize();

		// Calculate top plane of frustum.
		m_Sides[TOP].A = matrix.m14 - matrix.m12;
		m_Sides[TOP].B = matrix.m24 - matrix.m22;
		m_Sides[TOP].C = matrix.m34 - matrix.m32;
		m_Sides[TOP].D = matrix.m44 - matrix.m42;
		m_Sides[TOP].normalize();

		// Calculate bottom plane of frustum.
		m_Sides[BOTTOM].A = matrix.m14 + matrix.m12;
		m_Sides[BOTTOM].B = matrix.m24 + matrix.m22;
		m_Sides[BOTTOM].C = matrix.m34 + matrix.m32;
		m_Sides[BOTTOM].D = matrix.m44 + matrix.m42;
		m_Sides[BOTTOM].normalize();
	}

	bool ViewFrustum::isVisible(const math::Vec3& point) const
	{
		for (uint i = 0; i < 6; i++)
		{
			if (m_Sides[i].getRelation(point) == ZAAP_POINT_BELOW)
				return true;
		}
		return false;
	}
}}