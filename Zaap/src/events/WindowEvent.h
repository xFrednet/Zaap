#pragma once

#include <Common.h>
#include <Types.h>
#include "EventManager.h"

namespace zaap
{
	class WindowResizeEvent : public Event
	{
	private:
		uint m_Width;
		uint m_Height;
	public:
		WindowResizeEvent(uint width, uint height);

		uint getWidth() const;
		uint getHeight() const;

		String getEventName() const override;
		String toString() const override;
	};
	
}
