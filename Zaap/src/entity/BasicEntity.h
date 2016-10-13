#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Maths.h>

namespace zaap
{
	class ZAAP_API BasicEntity
	{
	protected:
		Vec3 m_Position;

		BasicEntity(Vec3 position = Vec3(0, 0, 0));
	public:
		//position
		virtual void setPosition(const Vec3 &position);
		virtual void increasePosition(const Vec3 &position);
		virtual Vec3 getPosition() const;
		virtual Vec3* getPositionP();

		//util
		virtual void update();
		virtual void render();
	};
}