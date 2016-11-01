#pragma once

#define ZAAP_API __declspec(dllexport)

#define ZAAP_DEBUG 1

//OS selection
#ifdef ZA_OS_WINDOWS
	#define ZA_OS_WIN
	#define ZA_OS_WIN32
	#define ZA_INCLUDE_DIRECTX
#else //!ZA_OS_WINDOWS
	#pragma message("Zaap ERROR : The targeted operating system isn't specified. Use ZA_OS_WINDOWS")
#endif

#pragma warning(push)
#pragma warning(disable: 4251)

#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <vector>
#include <map>
#include <list>
#include <unordered_map>

#include <time.h>
#include <ctime>

#include <cmath>

#include "Types.h"

#define METHOD_1(x) std::bind(&x, this, std::placeholders::_1)
#define METHOD_0(x) std::bind(&x, this)
