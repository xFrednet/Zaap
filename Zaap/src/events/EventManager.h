#pragma once

#include <Common.h>
#include <Types.h>

#include <events/Event.h>

namespace zaap { namespace events {
		
	class ZAAP_API EventManager
	{
	private:
		static std::vector<Event> events;
	public:

	};

}}
