#include "WindowEvent.h"

namespace zaap
{
	WindowResizeEvent::WindowResizeEvent(uint width, uint height)
		: Event(0, WINDOW_RESIZE_EVENT), //TODO add a modifier getter
		m_Width(width),
		m_Height(height)
	{
	}

	//
	// Getters
	//
	uint WindowResizeEvent::getWidth() const
	{
		return m_Width;
	}
	uint WindowResizeEvent::getHeight() const
	{
		return m_Height;
	}

	//
	// String getters
	//
	String WindowResizeEvent::getEventName() const
	{
		return "WindowResizeEvent";
	}
	String WindowResizeEvent::toString() const
	{
		return "WindowResizeEvent(s_Width: " + std::to_string(m_Width) +
			", s_Height: " + std::to_string(m_Height) + ")";
	}
}
