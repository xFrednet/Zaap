#include "Plane3D.h"

// source: https://graphics.stanford.edu/~mdfisher/Code/Engine/Plane.cpp.html

namespace zaap {
	
	//
	// Constructor
	//
	Plane3D::Plane3D()
		: N(0.0f, 1.0f, 0.0f), 
		D(1.0f)
	{
	}
	Plane3D::Plane3D(const float & a, const float & b, const float & c, const float & d)
		: N(a, b, c), D(d)
	{
	}
	Plane3D::Plane3D(const Vec3 &n, const float & d)
		: N(n), D(d)
	{
	}
	Plane3D::Plane3D(const Vec4 &p)
		: N(p.X, p.Y, p.Z), D(p.W)
	{
	}

	String Plane3D::toString() const
	{
		return "Plane3D(N: " + N.toString() + ", D: " + std::to_string(D) + ")";
	}

	//
	// Util
	//
	void  Plane3D::normalize()
	{
		*this = Normalize(*this);
	}
	bool  Plane3D::isPointOnPlane(const Vec3 &point) const
	{
		return IsPointOnPlane(*this, point);
	}
	float Plane3D::getSignedDistance(const Vec3& point) const
	{
		return GetSignedDistance(*this, point);
	}
	ZA_POINT_RELATION Plane3D::getRelation(const Vec3& point) const
	{
		return GetRelation(*this, point);
	}

	//
	//Operators
	//
	bool Plane3D::operator==(const Plane3D& other) const
	{
		return Equal(*this, other);
	}
	bool Plane3D::operator!=(const Plane3D& other) const
	{
		return !Equal(*this, other);
	}

}

namespace zaap {
	
	bool Equal(const Plane3D &a, const Plane3D &b)
	{
		return (a.N == b.N) && (a.D == b.D);
	}

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
	bool    IsPointOnPlane(const Plane3D& a, const Vec3& p)
	{
		return ((a.A * p.X + a.B * p.Y + a.C * p.Z + a.D) == 0);
	}
	float   GetSignedDistance(const Plane3D& a, const Vec3& p)
	{
		return (a.A * p.X + a.B * p.Y + a.C * p.Z - a.D) / sqrtf(a.A * a.A + a.B * a.B + a.C * a.C);
	}
	ZA_POINT_RELATION GetRelation(const Plane3D& plane, const Vec3& point)
	{
		float d = plane.A * point.X + plane.B * point.Y + plane.C * point.Z + plane.D;
		
		if (d > 0) return ZA_POINT_ABOVE;
		if (d < 0) return ZA_POINT_BELOW;
		return ZA_POINT_ONPLANE;
	}
}