#pragma once
#include "Common.h"

//ZA_RESULT
//  
//   1 1 1 1 1 1 1
//   6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1
//  +-+-------------+---------------+
//  |R|---Source----|-----Code------|
//  +-+-------------+---------------+
//
//  R      - Result: 
//             0: success
//             1: error
//
//  Source - Indicates the source (128 possible sources)
//
//  Code   - The error code (256 possible codes)
//
typedef short									ZA_RESULT;

////////////////////////////////////////////////////////////////////////////////
// OPERATIONS //
////////////////////////////////////////////////////////////////////////////////
#define ZAAP_TYPEDEF_ZARESULT(x)				short(x)

#define ZA_FAILED(x)  (x < 0)
#define ZA_SUCCEDED(x) (x >= 0)

//submit result
namespace zaap {
	ZAAP_API void SubmitZAResult(ZA_RESULT result);
}
#ifndef ZA_SUBMIT_ERROR
#	define ZA_SUBMIT_ERROR(x) zaap::SubmitZAResult(x)
#endif
////////////////////////////////////////////////////////////////////////////////
// Results //
////////////////////////////////////////////////////////////////////////////////

#define ZA_RESULT_ERROR							ZAAP_TYPEDEF_ZARESULT(0x8000)
#define ZA_RESULT_SUCCESS						ZAAP_TYPEDEF_ZARESULT(0x0000)
#define ZA_OK									ZAAP_TYPEDEF_ZARESULT(0x0000)

////////////////////////////////////////////////////////////////////////////////
// Sources //
////////////////////////////////////////////////////////////////////////////////
#define ZA_RESULT_SOURCE_MATH					ZAAP_TYPEDEF_ZARESULT(0x0100)
#define ZA_RESULT_SOURCE_SYSTEM					ZAAP_TYPEDEF_ZARESULT(0x0200)
#define ZA_RESULT_SOURCE_API					ZAAP_TYPEDEF_ZARESULT(0x0E00) //API said NO!!!
#define ZA_RESULT_SOURCE_API_DIRECTX			ZAAP_TYPEDEF_ZARESULT(0x0F00)

////////////////////////////////////////////////////////////////////////////////
// ZA_RESULT_SOURCE_MATH codes //
////////////////////////////////////////////////////////////////////////////////
#define ZA_ERROR_DIVISION_BY_ZERO				ZAAP_TYPEDEF_ZARESULT(0x8101)
#define ZA_ERROR_MATH_WRONG_CLAMP_VALUES		ZAAP_TYPEDEF_ZARESULT(0x8102)

////////////////////////////////////////////////////////////////////////////////
// ZA_RESULT_SOURCE_SYSTEM codes //
////////////////////////////////////////////////////////////////////////////////
//     - File stuff (input/output)
//     - Memory management
// ******************************
// File stuff
// ******************************
#define ZA_ERROR_DIRECTORY_DOES_NOT_EXIST		ZAAP_TYPEDEF_ZARESULT(0x8201)
#define ZA_ERROR_DIRECTORY_FAILED_TO_OPEN		ZAAP_TYPEDEF_ZARESULT(0x8202)
#define ZA_ERROR_DIRECTORY_FAILED_TO_CREATE		ZAAP_TYPEDEF_ZARESULT(0x8203)
#define ZA_ERROR_DIRECTORY_FAILED_TO_DELETE		ZAAP_TYPEDEF_ZARESULT(0x8204)
#define ZA_ERROR_DIRECTORY_FAILED_TO_RENAME		ZAAP_TYPEDEF_ZARESULT(0x8205)
#define ZA_ERROR_DIRECTORY_PATH_INVALID			ZAAP_TYPEDEF_ZARESULT(0x8206)

//The real name would be ZA_ERROR_FILE_DOES_NOT_EXISTS but StackExchange listed "imaginary" as a opposite of "to exist" so they have to be right. Right?
#define ZA_ERROR_FILE_IS_IMAGINARY				ZAAP_TYPEDEF_ZARESULT(0x8211) 
#define ZA_ERROR_FILE_DOES_NOT_EXIST			ZA_ERROR_FILE_IS_IMAGINARY
#define ZA_ERROR_FILE_IS_LOCKED					ZAAP_TYPEDEF_ZARESULT(0x8212)
#define ZA_ERROR_FILE_FAILED_TO_OPEN			ZAAP_TYPEDEF_ZARESULT(0x8213)
#define ZA_ERROR_FILE_FAILED_TO_LOAD_CONTENT	ZAAP_TYPEDEF_ZARESULT(0x8213)
#define ZA_ERROR_FILE_FAILED_TO_CREATE			ZAAP_TYPEDEF_ZARESULT(0x8214)
#define ZA_ERROR_FILE_FAILED_TO_DELETE			ZAAP_TYPEDEF_ZARESULT(0x8215)
#define ZA_ERROR_FILE_FAILED_TO_RENAME			ZAAP_TYPEDEF_ZARESULT(0x8216)
#define ZA_ERROR_FILE_NAME_INVALID				ZAAP_TYPEDEF_ZARESULT(0x8217)

#define ZA_ERROR_FILE_TYPE_UNKNOWN				ZAAP_TYPEDEF_ZARESULT(0x821A)
#define ZA_ERROR_FILE_TYPE_UNSUPPORTED			ZAAP_TYPEDEF_ZARESULT(0x821B)
#define ZA_ERROR_FILE_TYPE_UNEXPECTED			ZAAP_TYPEDEF_ZARESULT(0x821C)

// ******************************
// Memory management
// ******************************