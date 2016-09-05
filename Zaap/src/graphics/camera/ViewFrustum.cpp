#include "ViewFrustum.h"

#include <graphics/camera/Camera.h>
#include <util/Console.h>

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
	uint log = 0;
	void ViewFrustum::calculateFrustum(math::Mat4 projectionMatrix, math::Mat4 viewMatrix)
	{
		//Source: http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf

		// comboMatrix
		math::Mat4 matrix = viewMatrix * projectionMatrix;

		//Left
		m_Sides[LEFT].A = matrix.m14 + matrix.m11;
		m_Sides[LEFT].B = matrix.m24 + matrix.m21;
		m_Sides[LEFT].C = matrix.m34 + matrix.m31;
		m_Sides[LEFT].D = matrix.m44 + matrix.m41;

		//Right
		m_Sides[RIGHT].A = matrix.m14 - matrix.m11;
		m_Sides[RIGHT].B = matrix.m24 - matrix.m21;
		m_Sides[RIGHT].C = matrix.m34 - matrix.m31;
		m_Sides[RIGHT].D = matrix.m44 - matrix.m41;

		//Top
		m_Sides[TOP].A = matrix.m14 - matrix.m12;
		m_Sides[TOP].B = matrix.m24 - matrix.m22;
		m_Sides[TOP].C = matrix.m34 - matrix.m32;
		m_Sides[TOP].D = matrix.m44 - matrix.m42;

		//Bottom
		m_Sides[BOTTOM].A = matrix.m14 + matrix.m12;
		m_Sides[BOTTOM].B = matrix.m24 + matrix.m22;
		m_Sides[BOTTOM].C = matrix.m34 + matrix.m32;
		m_Sides[BOTTOM].D = matrix.m44 + matrix.m42;

		//Near
		m_Sides[FRONT].A = matrix.m13;
		m_Sides[FRONT].B = matrix.m13;
		m_Sides[FRONT].C = matrix.m13;
		m_Sides[FRONT].D = matrix.m13;

		//Far
		m_Sides[BACK].A = matrix.m14 - matrix.m13;
		m_Sides[BACK].B = matrix.m24 - matrix.m23;
		m_Sides[BACK].C = matrix.m34 - matrix.m33;
		m_Sides[BACK].D = matrix.m44 - matrix.m43;
		
		for (uint i = 0; i < 6; i++)
			m_Sides[i].normalize();
	}

	bool ViewFrustum::isVisible(const math::Vec3& point) const
	{
		//add far and near plane
		float d;
		for (uint i = 0; i < 4; i++)
		{
			d = m_Sides[i].A * point.X + m_Sides[i].B * point.Y + m_Sides[i].C * point.Z + m_Sides[i].D;
			if (d < 0)
				return false;
		}
		return true;
	}
}}
