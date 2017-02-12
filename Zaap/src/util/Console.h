#pragma once

#include <Common.h>

#ifndef ZA_LOG_LEVEL
#	define ZA_LOG_LEVEL 0
#endif

#include "Log.h"

namespace zaap { namespace console {

	ZAAP_API void PrintCleanup(String fileName);
	ZAAP_API void Println(String fileName, int line, ZA_LOG_MESSAGE_TYPE type, String message);
	ZAAP_API void PrintLastError(String message = "");

	ZAAP_API void SetColor(int color);

}}

#ifndef ZAAP_ERROR
#	if (ZA_LOG_MESSAGE_ERROR >= ZA_LOG_LEVEL)
#		define ZAAP_ERROR(x) zaap::console::Println(__FILE__, __LINE__, ZA_LOG_MESSAGE_ERROR, x)
#	else 
#		define ZAAP_ERROR(x)
#	endif
#endif

#ifndef ZAAP_ALERT
#	if (ZA_LOG_MESSAGE_ALERT >= ZA_LOG_LEVEL)
#		define ZAAP_ALERT(x) zaap::console::Println(__FILE__, __LINE__, ZA_LOG_MESSAGE_ALERT, x)
#	else 
#		define ZAAP_ALERT(x)
#	endif
#endif

#ifndef ZAAP_INFO
#	if (ZA_LOG_MESSAGE_INFO >= ZA_LOG_LEVEL)
#		define ZAAP_INFO(x) zaap::console::Println(__FILE__, __LINE__, ZA_LOG_MESSAGE_INFO, x)
#	else 
#		define ZAAP_INFO(x)
#	endif
#endif

#ifndef ZAAP_CLEANUP_INFO
#	if (ZA_LOG_MESSAGE_ALERT >= ZA_LOG_LEVEL)
#		define ZAAP_CLEANUP_INFO() zaap::console::PrintCleanup(__FILE__)
#	else 
#		define ZAAP_CLEANUP_INFO()
#	endif
#endif

#ifndef ZA_ASSERT
#	define ZA_ASSERT(x, ...)                                \
		if (!(x)) {                                                 \
			std::cout << "" << std::endl;                           \
			std::cout << "####################" << std::endl;       \
			std::cout << "# ZA_ASSERT FAILED #" << std::endl;       \
			std::cout << "####################" << std::endl;       \
			std::cout << "Assertion: " << (char*)#x << std::endl;   \
			std::cout << "File: " << __FILE__ << std::endl;         \
			std::cout << "Line: " << __LINE__ << std::endl;         \
			std::cout << __VA_ARGS__ << std::endl;                  \
			__debugbreak();                                         \
		}
#endif
