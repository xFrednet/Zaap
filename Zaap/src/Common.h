#pragma once

#define ZAAP_API __declspec(dllexport)

#define ZAAP_DEBUG 1

#ifdef ZA_OS_WINDOWS
#define ZA_OS_WIN
#define ZA_OS_WIN32
#define ZA_INCLUDE_DIRECTX
#else //!ZA_OS_WINDOWS
#pragma message("Zaap ERROR : The targeted operating system isn't specified. Use ZA_OS_WINDOWS")
#endif

#pragma warning(push)
#pragma warning(disable: 4251)

#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
