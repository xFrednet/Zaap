#pragma once

#include <ZaapCLI.h>

#include <maths/Plane3D.h>
#include "Vector3.h"
#include "Vector4.h"

namespace ZaapCLI {

	public enum ZA_POINT_RELATION {
		ZA_POINT_ABOVE = zaap::ZA_POINT_ABOVE,
		ZA_POINT_ONPLANE = zaap::ZA_POINT_ONPLANE,
		ZA_POINT_BELOW = zaap::ZA_POINT_BELOW
	};

	public ref class Plane3D : public ManagedClass<zaap::Plane3D>
	{
	private:
	public:
		ZA_CLI_VALUE(float, A, a);
		ZA_CLI_VALUE(float, B, b);
		ZA_CLI_VALUE(float, C, c);
		ZA_CLI_VALUE(float, D, d);
		ZA_CLI_VECTOR3(N, n, N);


		Plane3D();
		Plane3D(float a, float b, float c, float d);
		Plane3D(Vector3^ n, float d);
		Plane3D(Vector4^ p);

		//util
		void  normalize();
		bool  isPointOnPlane(Vector3^ point);
		float getSignedDistance(Vector3^ point);
		ZA_POINT_RELATION getRelation(Vector3^ point);

		//operators
		bool operator==(Plane3D^ other);
		bool operator!=(Plane3D^ other);
	};
}
