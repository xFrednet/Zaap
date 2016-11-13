#pragma once

#define ZAAP_API __declspec(dllexport)

//OS selection
#ifdef ZA_OS_WINDOWS
#	define ZAAP_OS_WIN
#	define ZAAP_OS_WIN32

	//ZA_DO_NOT_INCLUDE_DIRECTX use this macro to remove DirectX
	//This Macro isn't needed if a different ZA_OS is selected
#	ifndef ZA_DO_NOT_INCLUDE_DIRECTX 
#		define ZAAP_INCLUDE_DIRECTX
#	endif

#else //!ZA_OS_WINDOWS
#	pragma message("Zaap ERROR : The targeted operating system isn't specified. Use ZA_OS_WINDOWS")
#endif

#ifdef ZAAP_DEBUG 

#	ifdef ZAAP_INCLUDE_DIRECTX
#			define ZAAP_DIRECTX_DEBUG
#	endif

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
