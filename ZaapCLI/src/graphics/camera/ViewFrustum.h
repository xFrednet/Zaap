#pragma once

#include <ZaapCLI.h>

#include <graphics/camera/ViewFrustum.h>

#include <maths\Vector3.h>
#include <maths/Matrix4.h>

namespace ZaapCLI {

	public ref class ViewFrustum : public ManagedClass<zaap::graphics::ViewFrustum>
	{
	private:
	public:
		ViewFrustum();
		ViewFrustum(zaap::graphics::ViewFrustum* instance);
		ViewFrustum(float angle, float ratio, float nearPlane, float farPlane);

		void setInternals(float angle, float ratio, float nearPlane, float farPlane);
		void calculateFrustum(Matrix4^ projectionMatrix, Matrix4^ viewMatrix);

		bool isVisible(Vector3^ point);
		bool isCuboidVisible(Vector3^ min, Vector3^ max);
	};
}
