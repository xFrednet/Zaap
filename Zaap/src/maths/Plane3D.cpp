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
	String Plane3D::toString() const
	{
		return "Plane3D(N: " + N.toString() + ", D: " + std::to_string(D) + ")";
	}
	void Plane3D::normalize()
	{
		*this = Normalize(*this);
	}
	Vec3 Plane3D::getClosestPoint(const Vec3& point) const
	{
		return GetClosestPoint(*this, point);
	}
	float Plane3D::getSignedDistance(const Vec3& point) const
	{
		return GetSignedDistance(*this, point);
	}

	uint8 Plane3D::getRelation(const Vec3& point) const
	{
		return GetRelation(*this, point);
	}

	bool Plane3D::isPointOnPlane(const Vec3 &point) const
	{
		return IsPointOnPlane(*this, point);
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

}

namespace zaap {
	
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

	Vec3 GetClosestPoint(const Plane3D& a, const Vec3& p)
	{
		if (IsPointOnPlane(a, p)) return p;
		
		Vec3 d = a.N;
		// l=Adx+Bdy+Cdz!=0
		if (((a.A * d.X * p.X) + (a.B * d.Y * p.Y) + (a.C * d.Z * p.Z)) == 0)
			if (a.N != Vec3(0.0f, 1.0f, 0.0f))
				d = Vec3(0.0f, 1.0f, 0.0f);
			else 
				d = Vec3(1.0f, 0.0f, 0.0f);
		
		Vec3 b(p);
		b.X -= a.A * (a.A * d.X);
		b.Y -= a.B * (a.B * d.Y);
		b.Z -= a.C * (a.C * d.Z);
		return b;
		//return (p - (a.N * GetSignedDistance(a, p)));
	}

	float GetSignedDistance(const Plane3D& a, const Vec3& p)
	{
		return (a.A * p.X + a.B * p.Y + a.C * p.Z - a.D) / sqrtf(a.A * a.A + a.B * a.B + a.C * a.C);
	}

	bool IsPointOnPlane(const Plane3D& a, const Vec3& p)
	{
		return ((a.A * p.X + a.B * p.Y + a.C * p.Z + a.D) == 0);
	}

	uint8 GetRelation(const Plane3D& plane, const Vec3& point)
	{
		float d = plane.A * point.X + plane.B * point.Y + plane.C * point.Z + plane.D;
		
		if (d > 0) return ZAAP_POINT_ABOVE;
		if (d < 0) return ZAAP_POINT_BELOW;
		return ZAAP_POINT_ONPLANE;
	}
}