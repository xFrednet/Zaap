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
#	pragma error("Zaap ERROR : The targeted operating system isn't specified. Use ZA_OS_WINDOWS")
#endif

/* //////////////////////////////////////////////////////////////////////////////// */
// // Bit count Selection //
/* //////////////////////////////////////////////////////////////////////////////// */

// Check windows
#if _WIN32 || _WIN64
#	if _WIN64
#		define ZA_64BIT
#	else
#		define ZA_32BIT
#	endif
#endif

// Check GCC
#if __GNUC__
#	if __x86_64__ || __ppc64__
#		define ZA_64BIT
#	else
#		define ZA_32BIT
#	endif
#endif

#if !(defined(ZA_32BIT) || defined(ZA_64BIT))
#	error Zaap ERROR : The bit count of the targeted platform could not be determined!!!
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
