#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Maths.h>

namespace zaap
{
	class ZAAP_API BasicEntity
	{
	protected:
		math::Vec3 m_Position;

		BasicEntity(math::Vec3 position = math::Vec3(0, 0, 0));
	public:
		//position
		virtual void setPosition(const math::Vec3 &position);
		virtual void increasePosition(const math::Vec3 &position);
		virtual math::Vec3 getPosition() const;
		virtual math::Vec3* getPositionP();

		//util
		virtual void update();
		virtual void render();
	};
}