#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace events {
	
	class ZAAP_API Event
	{
	protected:
		time_t m_TimeStamp;
		int32 m_Modifiers;

		Event(int32 modifiers);
	public:
		virtual String getEventName(void) = 0;
		String getTimeStampString();
		
		inline int32 getModifiers(void) const { return m_Modifiers; };
		inline time_t getTimeStamp(void) const { return m_TimeStamp; };
	};

}}