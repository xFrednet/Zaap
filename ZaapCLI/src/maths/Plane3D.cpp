#include "Plane3D.h"

namespace ZaapCLI {
	
	Plane3D::Plane3D()
		: ManagedClass(new zaap::Plane3D())
	{
	}
	Plane3D::Plane3D(float a, float b, float c, float d)
		: ManagedClass(new zaap::Plane3D(a, b, c, d))
	{
	}
	Plane3D::Plane3D(Vector3^ n, float d)
		: ManagedClass(new zaap::Plane3D(*n->getHandle(), d))
	{
	}
	Plane3D::Plane3D(Vector4^ p) 
		: ManagedClass(new zaap::Plane3D(*p->getHandle()))
	{
	}

	//util
	void  Plane3D::normalize()
	{
		m_Instance->normalize();
	}
	bool  Plane3D::isPointOnPlane(Vector3^ point)
	{
		return m_Instance->isPointOnPlane(*point->getHandle());
	}
	float Plane3D::getSignedDistance(Vector3^ point)
	{
		return m_Instance->getSignedDistance(*point->getHandle());
	}
	ZA_POINT_RELATION Plane3D::getRelation(Vector3^ point)
	{
		return static_cast<ZA_POINT_RELATION>(m_Instance->getRelation(*point->getHandle()));
	}

	//operators
	bool Plane3D::operator==(Plane3D^ other)
	{
		return Equal(*m_Instance, *other->getHandle());
	}
	bool Plane3D::operator!=(Plane3D^ other)
	{
		return !Equal(*m_Instance, *other->getHandle());
	}
}
