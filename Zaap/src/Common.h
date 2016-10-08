#pragma once

#ifndef ZAAP_API
#	define ZAAP_API __declspec(dllexport)
#endif

#define ZAAP_DEBUG 1

#ifdef ZA_OS_WINDOWS
#define ZA_OS_WIN
#define ZA_OS_WIN32
#else 
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
