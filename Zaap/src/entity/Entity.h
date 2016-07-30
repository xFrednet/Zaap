#pragma once
#include "BasicEntity.h"

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <maths/Maths.h>

namespace zaap
{
	class ZAAP_API Entity : public BasicEntity
	{
	protected:
		graphics::Mesh* m_Mesh;
		math::Vec3 m_Rotation;
		math::Vec3 m_Scale;
	public:
		Entity(graphics::Mesh *mesh, math::Vec3 position, math::Vec3 rotation = math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3 scale = math::Vec3(1.0f, 1.0f, 1.0f));
		Entity();

		//rotation
		void setRotation(const math::Vec3 &rotation);
		void increaseRotation(const math::Vec3 &rotation);
		math::Vec3 getRotation(void) const;
		math::Vec3* getRotationP(void);

		//Scale
		void setScale(float scale);
		void setScale(math::Vec3 scale);
		void increaseScale(float scale);
		void increaseScale(math::Vec3 scale);
		math::Vec3 getScale(void) const;
		math::Vec3* getScaleP(void);

		//Getters
		graphics::Mesh* getMesh(void);
		void getTransformationMatrix(math::Mat4& result) const;
		
		//util
		virtual void render() override;
	};
}