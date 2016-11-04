#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <maths/Maths.h>

namespace zaap
{
	class ZAAP_API Entity
	{
	protected:
		graphics::Mesh* m_Mesh;
		Vec3 m_Position;
		Vec3 m_Rotation;
		Vec3 m_Scale;
	public:
		Entity(graphics::Mesh *mesh, 
			const Vec3& position = Vec3(0.0f, 0.0f, 0.0f),
			const Vec3& rotation = Vec3(0.0f, 0.0f, 0.0f), 
			const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f));
		Entity();
		~Entity() {}

		//position
		virtual void setPosition(const Vec3 &position);
		virtual void increasePosition(const Vec3 &position);
		virtual Vec3 getPosition() const;
		virtual Vec3* getPositionP();

		//rotation
		virtual void setRotation(const Vec3 &rotation);
		virtual void increaseRotation(const Vec3 &rotation);
		virtual Vec3 getRotation() const;
		virtual Vec3* getRotationP();

		//Scale
		virtual void setScale(const float& scale);
		virtual void setScale(const Vec3& scale);
		virtual void increaseScale(const float& scale);
		virtual void increaseScale(const Vec3& scale);
		virtual Vec3 getScale() const;
		virtual Vec3* getScaleP();

		//Getters
		virtual graphics::Mesh* getMesh();
		virtual void getTransformationMatrix(Mat4& result) const;
		
		// GameLoop util
		virtual void update();
		virtual void render();
	};
}