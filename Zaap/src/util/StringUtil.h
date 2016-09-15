#pragma once

#pragma warning( disable : 4114)

#include <Common.h>

#include <string>

typedef std::string String;

namespace zaap {

	class ZAAP_API StringUtil
	{
	public:
		static String to_string(const float &f);
		static String getDateString(const time_t const time = time(0));
	};

}
