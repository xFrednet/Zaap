#pragma once

#ifndef ZAAP_API
#	define ZAAP_API __declspec(dllexport)
#endif

#ifndef ZAAP_DEBUG
#	define ZAAP_DEBUG 1
#endif

// TODO remove __WIN32__ definition
#ifndef __WIN32__ 
#define __WIN32__
#endif

#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>