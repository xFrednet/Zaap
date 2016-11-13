#pragma once

#include <Types.h>
#include <util/StringUtil.h>
#include <Common.h>

#ifndef ZAAP_LOG_LEVEL
#	define ZAAP_LOG_LEVEL 0
#endif


typedef ZAAP_API enum ZA_CON_MESSAGE_TYPE_ {
	ZA_CON_MESSAGE_INFO = 0,
	ZA_CON_MESSAGE_ALERT = 1,
	ZA_CON_MESSAGE_ERROR = 2,
	ZA_CON_MESSAGE_CLEANUP = 3
} ZA_CON_MESSAGE_TYPE;

namespace zaap { namespace console {
	
	ZAAP_API void PrintCleanup(String fileName);
	ZAAP_API void Println(String fileName, int line, ZA_CON_MESSAGE_TYPE type, String message);
	ZAAP_API void PrintLastError(String message = "");

	ZAAP_API void SetColor(int color);

}}

#ifndef ZAAP_ERROR
#	if (ZA_CON_MESSAGE_ERROR >= ZAAP_LOG_LEVEL)
#		define ZAAP_ERROR(x) zaap::console::Println(__FILE__, __LINE__, ZA_CON_MESSAGE_ERROR, x)
#	else 
#		define ZAAP_ERROR(x)
#	endif
#endif

#ifndef ZAAP_ALERT
#	if (ZA_CON_MESSAGE_ALERT >= ZAAP_LOG_LEVEL)
#		define ZAAP_ALERT(x) zaap::console::Println(__FILE__, __LINE__, ZA_CON_MESSAGE_ALERT, x)
#	else 
#		define ZAAP_ALERT(x)
#	endif
#endif

#ifndef ZAAP_INFO
#	if (ZA_CON_MESSAGE_INFO >= ZAAP_LOG_LEVEL)
#		define ZAAP_INFO(x) zaap::console::Println(__FILE__, __LINE__, ZA_CON_MESSAGE_INFO, x)
#	else 
#		define ZAAP_INFO(x)
#	endif
#endif

#ifndef ZAAP_CLEANUP_INFO
#	if (ZA_CON_MESSAGE_ALERT >= ZAAP_LOG_LEVEL)
#		define ZAAP_CLEANUP_INFO() zaap::console::PrintCleanup(__FILE__)
#	else 
#		define ZAAP_CLEANUP_INFO()
#	endif
#endif