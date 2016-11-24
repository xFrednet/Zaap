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
typedef short								ZA_RESULT;

////////////////////////////////////////////////////////////////////////////////
// OPERATIONS //
////////////////////////////////////////////////////////////////////////////////
#define ZAAP_TYPEDEF_ZARESULT(x)			short(x)

#define ZA_FAILLED(x)  (x < 0)
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

#define ZA_RESULT_ERROR						ZAAP_TYPEDEF_ZARESULT(0x8000)
#define ZA_RESULT_SUCCESS					ZAAP_TYPEDEF_ZARESULT(0x0000)
#define ZA_OK								ZAAP_TYPEDEF_ZARESULT(0x0000)

////////////////////////////////////////////////////////////////////////////////
// Sources //
////////////////////////////////////////////////////////////////////////////////
#define ZA_RESULT_SOURCE_MATH				ZAAP_TYPEDEF_ZARESULT(0x0100)
#define ZA_RESULT_SOURCE_API				ZAAP_TYPEDEF_ZARESULT(0x0200) //API said NO!!!
#define ZA_RESULT_SOURCE_API_DIRECTX		ZAAP_TYPEDEF_ZARESULT(0x0300)

////////////////////////////////////////////////////////////////////////////////
// ZA_RESULT_SOURCE_MATH codes //
////////////////////////////////////////////////////////////////////////////////
#define ZA_ERROR_DIVISION_BY_ZERO			ZAAP_TYPEDEF_ZARESULT(0x8101)
#define ZA_ERROR_MATH_WRONG_CLAMP_VALUES	ZAAP_TYPEDEF_ZARESULT(0x8102)