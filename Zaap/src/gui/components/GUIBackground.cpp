﻿#include "GUIBackground.h"
#include <gui/VertexBufferHelper.h>

namespace zaap { namespace gui {
	
	void GUIBackground::updateVertexBuffer()
	{
		VertexBufferHelper helper(&m_VertexBuffer);
		helper.start();

		helper.drawRectangle(getGlobalPosition(), getWidth(), getHeight(), m_Color);

		helper.stop();
	}

	uint GUIBackground::getWrappedWidth() const
	{
		return 0;
	}
	uint GUIBackground::getWrappedHeight() const
	{
		return 0;
	}

	GUIBackground::GUIBackground(GUIComponent* parent)
		: GUIComponent(4, 6, parent)
	{
		setPreferredSize(ZA_GUI_SIZE_MATCH_PARENT, ZA_GUI_SIZE_MATCH_PARENT);
	}
	GUIBackground::GUIBackground(Point pos, uint width, uint height, graphics::Color color)
		: GUIComponent(4, 6, nullptr)
	{
		setColor(color);
		setPosition(pos);
		setPreferredSize(width, height);
	}

	void GUIBackground::setColor(graphics::Color color)
	{
		m_Color = color;
		requestRedraw();
	}
	graphics::Color GUIBackground::getColor() const
	{
		return m_Color;
	}
}}
