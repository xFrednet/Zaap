#pragma once

#include <Common.h>
#include <Types.h>
#include <functional>

namespace zaap {
	
	typedef ZAAP_API enum EVENT_TYPE_
	{
		UNKNOWN_EVENT_TYPE = 0,
		WINDOW_RESIZE_EVENT = 1

	} EVENT_TYPE;

	class ZAAP_API Event
	{
	protected:
		time_t m_TimeStamp;
		int32 m_Modifiers;
		EVENT_TYPE m_EventType;

		Event(int32 modifiers, EVENT_TYPE eventType);
		virtual ~Event() {}
	public:
		virtual String getEventName() const = 0;
		virtual String toString() const = 0;
		
		String getTimeStampString() const;
		int32 getModifiers(void) const;
		time_t getTimeStamp(void) const;

		EVENT_TYPE getEventType() const;
	};

}
