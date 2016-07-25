#pragma once
#include <Common.h>
#include <Types.h>

#include <graphics/TexturedMesh.h>
#include <maths/Maths.h>

namespace zaap
{
	class ZAAP_API Entity
	{
	private:
		graphics::TexturedMesh m_TMesh;
		math::Vec3 m_Position;
		math::Vec3 m_Rotation;
		float m_Scale;
	public:
		Entity(graphics::TexturedMesh &mesh, math::Vec3 &position, math::Vec3 &rotation = math::Vec3(), float scale = 1.0f);
		Entity();

		//position
		void setPosition(math::Vec3 &position);
		void increasePosition(math::Vec3 &position);
		math::Vec3 getPosition() const;

		//rotation
		void setRotation(math::Vec3 &rotation);
		void increaseRotation(math::Vec3 &rotation);
		math::Vec3 getRotation() const;

		//Scale
		void setScale(float scale);
		void addToScale(float scale);
		float getScale() const;

		//Getters
		graphics::TexturedMesh* getTexturedMesh(void);
		void getTransformationMatrix(math::Mat4& result) const;

	};
}