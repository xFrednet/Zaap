#pragma once
#include <Common.h>
#include <Types.h>

#include <graphics/Color.h>
#include <maths/Maths.h>
#include <util/UUID.h>

namespace zaap {
	
	class ZAAP_API Light
	{
	protected:
		graphics::Color m_Color;

		UUID m_UUID;

		Vec3 m_Position;
	public:
		Light(const Vec3& position = Vec3(0, 0, 0), const graphics::Color& color = graphics::Color(1.0f, 1.0f, 1.0f));

		//color
		void setColor(const graphics::Color& color);
		graphics::Color getColor() const;
		graphics::Color* getColorP();

		//position
		void setPosition(const Vec3 &position);
		void increasePosition(const Vec3 &position);
		Vec3 getPosition() const;
		Vec3* getPositionP();

		bool equal(const Light* other) const;

		virtual void update();
	};

}
