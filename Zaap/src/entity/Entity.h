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
		Vec3 m_Rotation;
		Vec3 m_Scale;
	public:
		Entity(graphics::Mesh *mesh, Vec3 position, Vec3 rotation = Vec3(0.0f, 0.0f, 0.0f), Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));
		Entity();

		//rotation
		void setRotation(const Vec3 &rotation);
		void increaseRotation(const Vec3 &rotation);
		Vec3 getRotation(void) const;
		Vec3* getRotationP(void);

		//Scale
		void setScale(float scale);
		void setScale(Vec3 scale);
		void increaseScale(float scale);
		void increaseScale(Vec3 scale);
		Vec3 getScale(void) const;
		Vec3* getScaleP(void);

		//Getters
		graphics::Mesh* getMesh(void);
		void getTransformationMatrix(Mat4& result) const;
		
		//util
		virtual void render() override;
	};
}