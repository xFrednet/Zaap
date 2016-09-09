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
		m_Sides[FRONT].B = matrix.m23;
		m_Sides[FRONT].C = matrix.m33;
		m_Sides[FRONT].D = matrix.m43;

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
		for (uint i = 0; i < 4; i++)
		{
			if (GetRelation(m_Sides[i], point) == ZAAP_POINT_BELOW)
				return false;
		}
		return true;
	}

	bool ViewFrustum::isCuboidVisible(math::Vec3 min, math::Vec3 max) const
	{

		float middle = (min.Y + max.Y) / 2;
		bool isVisible = false;
		uint i, j;
		
		// Layer 1 | Layer 2 |
		//  0   1  |  4   5  |
		//         |         |
		//  2   3  |  6   7  |
		math::Vec3 tPoints[]{
			math::Vec3(min.X, min.Y, min.Z), math::Vec3(max.X, min.Y, min.Z),
			math::Vec3(min.X, min.Y, max.Z), math::Vec3(max.X, min.Y, max.Z),
			math::Vec3(min.X, max.Y, min.Z), math::Vec3(max.X, max.Y, min.Z),
			math::Vec3(min.X, max.Y, max.Z), math::Vec3(max.X, max.Y, max.Z)
		};


		//in front
		{
			for (i = 0; i < 8; i++)
			{
				if (GetRelation(m_Sides[FRONT], tPoints[i]) != ZAAP_POINT_BELOW)
				{
					isVisible = true;
					break;
				}
			}
			
			if (!isVisible)
				return false; // behind the camera
		}

		isVisible = false;

		
		//left right test
		{
			//diagonal Test
			// Test 1 | Test 2 
			//        |        
			// i      |     i  
			//   \    |   /    
			//     j  | j      

			//first test
			for (i = 0; i < 4; i++)
			{
				j = 7 - i;

				//test if point is to the left
				if (GetRelation(m_Sides[LEFT], tPoints[i]) == ZAAP_POINT_BELOW)
				{
					// 1 \ view  2
					if (GetRelation(m_Sides[LEFT], tPoints[j]) == ZAAP_POINT_ABOVE)
					{
						isVisible = true;
						break;
					}

					//else test if point is to the right
				} else if (GetRelation(m_Sides[RIGHT], tPoints[i]) == ZAAP_POINT_ABOVE)
				{
					isVisible = true;
					break;
				} else if (GetRelation(m_Sides[RIGHT], tPoints[j]) == ZAAP_POINT_ABOVE)
				{
					isVisible = true;
					break;
				}
				
			}
		
			if (!isVisible) 
				return false; //
		}

		return true;
	}
}}
