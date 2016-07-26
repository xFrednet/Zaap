#pragma once
#include <Common.h>
#include <Types.h>

#include <entity/BasicEntity.h>

#include <maths/Maths.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Light : public BasicEntity
	{
	protected:
		math::Vec3 m_Color;
	public:
		Light(math::Vec3 position = math::Vec3(0, 0, 0), math::Vec3 color = math::Vec3(1, 1, 1));

		//color
		void setColor(math::Vec3 color);
		void increaseColor(math::Vec3 color);
		math::Vec3 getColor(void) const;
		math::Vec3* getColorP(void);
	};

}}