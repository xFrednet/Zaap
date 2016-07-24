#include "Event.h"

namespace zaap { namespace events {
	
	Event::Event(int32 modifiers)
		: m_TimeStamp(time(nullptr)),
		m_Modifiers(modifiers)
	{
		
	}

	String Event::getTimeStampString()
	{
		return StringUtil::getDateString(m_TimeStamp);
	}


}}