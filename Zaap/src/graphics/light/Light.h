#pragma once
#include <Common.h>
#include <Types.h>

#include <entity/BasicEntity.h>

#include <graphics/Color.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Light : public BasicEntity
	{
	protected:
		Color m_Color;
	public:
		Light(Vec3 position = Vec3(0, 0, 0), Color color = Color(1.0f, 1.0f, 1.0f));

		//color
		void setColor(Color color);
		Color getColor(void) const;
		Color* getColorP(void);
	};

}}