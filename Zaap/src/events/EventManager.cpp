#include "EventManager.h"
#include <util/StringUtil.h>

namespace zaap {
	
	Event::Event(int32 modifiers, EVENT_TYPE eventType)
		: m_TimeStamp(time(nullptr)),
		m_Modifiers(modifiers),
		m_EventType(eventType)
	{
		
	}

	String Event::getTimeStampString() const
	{
		return StringUtil::getDateString(m_TimeStamp) ;
	}

	int32 Event::getModifiers() const
	{
		return m_Modifiers;
	}

	time_t Event::getTimeStamp() const
	{
		return m_TimeStamp;
	}

	EVENT_TYPE Event::getEventType() const
	{
		return m_EventType;
	}
}
