#pragma once

#include <Common.h>
#include <Types.h>

#include <util/StringUtil.h>

#ifndef ZAAP_LOG_LEVEL
#	define ZAAP_LOG_LEVEL 0
#endif

#define ZAAP_LOG_CLEANUP 3
#define ZAAP_LOG_ERROR 2
#define ZAAP_LOG_ALERT 1
#define ZAAP_LOG_INFO 0


namespace zaap
{
	namespace console
	{
		ZAAP_API void Println_(void* hr, String message = "", int messageType = ZAAP_LOG_INFO);
		ZAAP_API void Println(String message, int messageType = ZAAP_LOG_INFO);
		ZAAP_API void PrintLastError(String message = "");

		ZAAP_API void SetColor(int color);
	}
}

#ifndef ZAAP_ERROR
#	if (ZAAP_LOG_ERROR >= ZAAP_LOG_LEVEL)
#		define ZAAP_ERROR(x) zaap::console::Println(x, ZAAP_LOG_ERROR); 
#		define ZAAP_ERROR_(x, y) zaap::console::Println_(x, y, ZAAP_LOG_ERROR);
#	else 
#		define ZAAP_ERROR(x)
#		define ZAAP_ERROR_(x, y)
#	endif
#endif

#ifndef ZAAP_ALERT
#	if (ZAAP_LOG_INFO >= ZAAP_LOG_LEVEL)
#		define ZAAP_ALERT(x) zaap::console::Println(x, ZAAP_LOG_ALERT); 
#		define ZAAP_ALERT_(x, y) zaap::console::Println_(x, y, ZAAP_LOG_ALERT);
#	else 
#		define ZAAP_ALERT(x)
#		define ZAAP_ALERT_(x, y)
#	endif
#endif

#ifndef ZAAP_INFO
#	if (ZAAP_LOG_INFO >= ZAAP_LOG_LEVEL)
#		define ZAAP_INFO(x) zaap::console::Println(x, ZAAP_LOG_INFO); 
#		define ZAAP_INFO_(x, y) zaap::console::Println_(x, y, ZAAP_LOG_INFO);
#	else 
#		define ZAAP_INFO(x)
#		define ZAAP_INFO_(x, y)
#	endif
#endif

#ifndef ZAAP_CLEANUP_LOG
#	if (ZAAP_LOG_INFO >= ZAAP_LOG_LEVEL)
#		define ZAAP_CLEANUP_LOG(x) zaap::console::Println(x, ZAAP_LOG_CLEANUP); 
#	else 
#		define ZAAP_CLEANUP_LOG(x)
#	endif
#endif