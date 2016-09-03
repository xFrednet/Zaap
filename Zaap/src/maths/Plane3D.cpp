#include "Plane3D.h"

// source: https://graphics.stanford.edu/~mdfisher/Code/Engine/Plane.cpp.html

namespace zaap { namespace math {
	
	//
	// Constructor
	//
	Plane3D::Plane3D()
		: N(0.0f, 1.0f, 0.0f), 
		D(1.0f)
	{
	}
	Plane3D::Plane3D(float a, float b, float c, float d)
		: N(a, b, c), D(d)
	{
	}
	Plane3D::Plane3D(Vec3 n, float d)
		: N(n), D(d)
	{
	}
	Plane3D::Plane3D(Vec4 p)
		: N(p.X, p.Y, p.Z), D(p.W)
	{
	}

	//
	// Util
	//
	void Plane3D::normalize()
	{
		*this = Normalize(*this);
	}
	uint8 Plane3D::getRelation(const Vec3& point) const
	{
		return GetRelation(*this, point);
	}

	//
	//Operators
	//
	bool Plane3D::operator==(const Plane3D& other) const
	{
		return (N == other.N) && (D == other.D);
	}
	bool Plane3D::operator!=(const Plane3D& other) const
	{
		return !(*this == other);
	}

}}

namespace zaap { namespace math {
	
	Plane3D Normalize(const Plane3D& a)
	{
		Plane3D b;
		float distance = a.N.getLength();
		b.A = a.A / distance;
		b.B = a.B / distance;
		b.C = a.C / distance;
		b.D = a.D / distance;

		return b;
	}

	uint8 GetRelation(const Plane3D& plane, const Vec3& point)
	{
		float temp = Dot(plane.N, point) - plane.D;
		
		if (temp > 0) return ZAAP_POINT_ABOVE;
		if (temp < 0) return ZAAP_POINT_BELOW;
		return ZAAP_POINT_ONPLANE;
	}
}}