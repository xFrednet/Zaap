#pragma once

#include "Types.h"
#include "Common.h"
#include "graphics/TexturedMesh.h"
#include "maths/Maths.h"

namespace zaap { namespace graphics {
	
	class ZAAP_API Model
	{
	private:
		TexturedMesh m_TMesh;
		math::Vec3 m_Position;
		math::Vec3 m_Rotation;
		float m_Scale;
	public:
		Model(TexturedMesh &mesh, math::Vec3 &position, math::Vec3 &rotation = math::Vec3(), float scale = 1.0f);
		Model();

		//position
		void setPosition(math::Vec3 &position);
		void addToPosition(math::Vec3 &position);
		math::Vec3 getPosition() const;
		
		//rotation
		void setRotation(math::Vec3 &rotation);
		void addToRotation(math::Vec3 &rotation);
		math::Vec3 getRotation() const;

		//Scale
		void setScale(float scale);
		void addToScale(float scale);
		float getScale() const;
		
		//Getters
		TexturedMesh* getTexturedMesh(void);
		void getTransformationMatrix(math::Mat4& result) const;

	};
}}