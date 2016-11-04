#pragma once
#include <Common.h>
#include <Types.h>

#include <graphics/Color.h>
#include <maths/Maths.h>

namespace zaap {
	
	class ZAAP_API Light
	{
	protected:
		graphics::Color m_Color;

		Vec3 m_Position;
	public:
		Light(const Vec3& position = Vec3(0, 0, 0), const graphics::Color& color = graphics::Color(1.0f, 1.0f, 1.0f));

		//color
		void setColor(const graphics::Color& color);
		graphics::Color getColor(void) const;
		graphics::Color* getColorP(void);

		//position
		void setPosition(const Vec3 &position);
		void increasePosition(const Vec3 &position);
		Vec3 getPosition() const;
		Vec3* getPositionP();

		virtual void update();
	};

}