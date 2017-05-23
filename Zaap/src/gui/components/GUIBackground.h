﻿#pragma once

#include <Common.h>

#include "..\GUIComponent.h"

namespace zaap { namespace gui {
		
	class ZAAP_API GUIBackground : public GUIComponent
	{
	protected:
		void updateVertexBuffer() override;
		uint getWrappedWidth() const override;
		uint getWrappedHeight() const override;

		graphics::Color m_Color;

	public:
		GUIBackground(GUIComponent* parent = nullptr);
		GUIBackground(Point pos, int width, int height, graphics::Color color = graphics::Color());

		inline void setColor(graphics::Color color);
		inline graphics::Color getColor() const;
	};
}}
