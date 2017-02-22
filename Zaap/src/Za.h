#pragma once

#define ZAAP_API			__declspec(dllexport)

/* //////////////////////////////////////////////////////////////////////////////// */
// // OS Selection //
/* //////////////////////////////////////////////////////////////////////////////// */
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

/* //////////////////////////////////////////////////////////////////////////////// */
// // DEBUG stuff //
/* //////////////////////////////////////////////////////////////////////////////// */
//Do not enter!!!
#ifdef ZAAP_DEBUG 

#	ifdef ZAAP_INCLUDE_DIRECTX
#			define ZAAP_DIRECTX_DEBUG
#	endif

#endif

/* //////////////////////////////////////////////////////////////////////////////// */
// // Util stuff //
/* //////////////////////////////////////////////////////////////////////////////// */
#define ZA_METHOD_1(x) std::bind(&x, this, std::placeholders::_1)
#define ZA_METHOD_0(x) std::bind(&x, this)