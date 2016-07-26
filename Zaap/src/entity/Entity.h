#pragma once
#include "BasicEntity.h"

#include <Common.h>
#include <Types.h>

#include <graphics/TexturedMesh.h>
#include <maths/Maths.h>

namespace zaap
{
	class ZAAP_API Entity : public BasicEntity
	{
	protected:
		graphics::TexturedMesh m_TMesh;
		math::Vec3 m_Rotation;
		float m_Scale;
	public:
		Entity(graphics::TexturedMesh &mesh, math::Vec3 &position, math::Vec3 &rotation = math::Vec3(), float scale = 1.0f);
		Entity();

		//rotation
		void setRotation(const math::Vec3 &rotation);
		void increaseRotation(const math::Vec3 &rotation);
		math::Vec3 getRotation(void) const;
		math::Vec3* getRotationP(void);

		//Scale
		void setScale(float scale);
		void addToScale(float scale);
		float getScale() const;

		//Getters
		graphics::TexturedMesh* getTexturedMesh(void);
		void getTransformationMatrix(math::Mat4& result) const;
		
		//util
		virtual void render() override;
	};
}