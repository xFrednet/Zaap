#pragma once

#include <ZaapCLI.h>

#include <entity/Entity.h>
#include <maths\Vector3.h>
#include <maths\Matrix4.h>

namespace ZaapCLI {

	public ref class Entity
	{
	private:
	protected:
		zaap::Entity* m_Instance;
	public:
		Entity(zaap::Entity* instance);
		~Entity();
		!Entity();

		//position
		virtual void setPosition(Vector3^ position);
		virtual void increasePosition(Vector3^ position);
		Vector3^ getPosition();

		//rotation
		virtual void setRotation(Vector3^ rotation);
		virtual void increaseRotation(Vector3^ rotation);
		Vector3^ getRotation();

		//Scale
		virtual void setScale(float scale);
		virtual void setScale(Vector3^ scale);
		virtual void increaseScale(float scale);
		virtual void increaseScale(Vector3^ scale);
		Vector3^ getScale();

		//Getters
		//virtual graphics::Mesh* getMesh();
		void getTransformationMatrix(Matrix4^ result);

		// GameLoop util
		virtual void update();
		virtual void render();

		zaap::Entity* getHandle();
	};
}
