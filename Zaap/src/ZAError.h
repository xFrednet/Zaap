#pragma once
#include "Common.h"

// <Name>
//      ZA_RESULT
//  
// <Structure>
//       1 1 1 1 1 1 1
//       6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1
//      +-+-------------+---------------+
//      |R|---Source----|-----Code------|
//      +-+-------------+---------------+
//    
//      R      - Result: 
//                 0: success
//                 1: error
//      
//      Source - Indicates the source (128 possible sources)
//      
//      Code   - The error code (256 possible codes)
//
typedef int16									ZA_RESULT;

// <Name>
//      ZA_MULTI_RESULT
//
// <Description>
//      This value combines up to four errors. The first error indicates
//      the main error the following errors are just better specifications.
//      The first error is put into the first two bytes to support the 
//      error specific macros like ZA_FAILED and ZA_SUCCEDED.
//
// <Structure>
//      bits:
//       6       5       4       4       3       2       1              
//       4       6       8       0       2       4       6       8      
//      | byte1 | byte2 | byte3 | byte4 | byte5 | byte6 | byte7 | byte8 |
//      |  ZA_RESULT 1  |  ZA_RESULT 2  |  ZA_RESULT 3  |  ZA_RESULT 3  |
//      +---------------+---------------+---------------+---------------+
//      |               |               |               |               |
//      +---------------+---------------+---------------+---------------+
//      
//      ZA_RESULT 1     - The first ZA_RESULT is the main result use
//                        ZA_FAILED and/or ZA_SUCCEDED to test if this 
//                        is an error or a success. (This one should always
//                        be filled the others are optional.)
//
//      ZA_RESULT 2     - This is the second result. This result is optional.
//
//      ZA_RESULT 3     - This is the third result. This result is optional.
//
//      ZA_RESULT 4     - This is the fourth result. This result 
//                        is also optional.
//
typedef int64									ZA_MULTI_RESULT;





////////////////////////////////////////////////////////////////////////////////
// OPERATIONS //
////////////////////////////////////////////////////////////////////////////////
#define ZAAP_TYPEDEF_ZARESULT(x)				ZA_RESULT(x)

#define ZA_FAILED(x)   (x < 0)
#define ZA_SUCCEDED(x) (x >= 0)

//submit result
namespace zaap {
	ZAAP_API void SubmitZAResult(ZA_RESULT result);

	// <Function>
	//      CombineZAResults
	//
	// <Descripion>
	//      This method combines the given ZA_RESULTs into a 
	//      ZA_MULTI_RESULT. The ZA_MULTI_RESULT can be split back into
	//      the single results.
	//
	// <Input>
	//      result1     : The first and main result. This indicates 
	//                    result type. (positive / negative)
	//
	//      result2     : The second result is optional and logically 
	//                    the second result.
	//
	//      result3     : The third result is optional and logically 
	//                    the third result.
	//
	//      result4     : The fourth result is optional and logically 
	//                    no not again it's a result okay!?!?!.
	//
	// <Return>
	//      The combined sub-results in from of a ZA_MULTI_RESULT.
	//
	ZAAP_API ZA_MULTI_RESULT CombineZAResults(ZA_RESULT result1, 
		ZA_RESULT result2 = 0x0000,
		ZA_RESULT result3 = 0x0000,
		ZA_RESULT result4 = 0x0000);

	// <Function>
	//      GetZAResults
	//
	// <Description>
	//      This method splits the ZA_MULTI_RESULT into the four
	//      sub-results.
	//
	// <Input>
	//      multiResult : The ZA_MULTI_RESULT for the requested 
	//                    sub-results
	//
	// <Return>
	//      This returns a ZA_RESULT array with the fixed size of four.
	//      The array is created in dynamic memory this means that it 
	//      should resolve it self after use. (Don't use delete)
	//      Array structure
	//          ZA_RESULT[0] = result1
	//          ZA_RESULT[1] = result2
	//          ZA_RESULT[2] = result3
	//          ZA_RESULT[3] = result4
	//
	ZAAP_API ZA_RESULT* GetZAResults(ZA_MULTI_RESULT multiResult);
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
#define ZA_RESULT_SOURCE_NO_SOURCE				ZAAP_TYPEDEF_ZARESULT(0x0000)
#define ZA_RESULT_SOURCE_MATH					ZAAP_TYPEDEF_ZARESULT(0x0100)
#define ZA_RESULT_SOURCE_SYSTEM					ZAAP_TYPEDEF_ZARESULT(0x0200)
#define ZA_RESULT_SOURCE_API					ZAAP_TYPEDEF_ZARESULT(0x0D00) //API said NO!!!
#define ZA_RESULT_SOURCE_DIRECTX				ZAAP_TYPEDEF_ZARESULT(0x0E00)
#define ZA_RESULT_SOURCE_OPENGL					ZAAP_TYPEDEF_ZARESULT(0x0F00) //I'll do that. Some dark day.





////////////////////////////////////////////////////////////////////////////////
// ZA_RESULT_SOURCE_NO_SOURCE //
////////////////////////////////////////////////////////////////////////////////
#define ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT ZAAP_TYPEDEF_ZARESULT(0x8001)





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

//The real name would be ZA_ERROR_FILE_DOES_NOT_EXISTS but 
//StackExchange listed "imaginary" as a opposite of "to exist" so 
//they have to be right. Right?
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





////////////////////////////////////////////////////////////////////////////////
// ZA_RESULT_SOURCE_API //
////////////////////////////////////////////////////////////////////////////////
// Anything that is API related. Some/Most APIs should have
// their own error source code, those are preferred.

// <Name>
//      ZA_ERROR_API_ERROR
//
// <Description>
//      A general error in the API. This isn't specified any closer.
//      Just pray for a new update that repairs this.
//
// <Message>
//      A error accord somewhere within the API construct.
//
#define ZA_ERROR_API_ERROR				ZAAP_TYPEDEF_ZARESULT(0x8D00)

// <Name>
//      ZA_ERROR_API_UNAVALIlABLE_API
//
// <Description>
//      This error indicates that the API chosen API is unavailable, do to
//      some unknown reason. This could be the case when you select an unknown 
//      API or a API that wasn't included during compilation.
//      
// <Message>
//     The chosen API is unavailable.
//
#define ZA_ERROR_API_UNAVALIlABLE_API				ZAAP_TYPEDEF_ZARESULT(0x8D01)

// <Name>
//      ZA_ERROR_API_MISSES_THIS_FEATURE
//
// <Description>
//      The chosen API exists but this feature is missing it should be added
//      later on. (Should is the important word in this sentence.)
//
// <Message>
//      This feature is missing from this API. (Sorry)
//
#define ZA_ERROR_API_MISSES_THIS_FEATURE			ZAAP_TYPEDEF_ZARESULT(0x8D02)





////////////////////////////////////////////////////////////////////////////////
// ZA_RESULT_SOURCE_API_DIRECTX //
////////////////////////////////////////////////////////////////////////////////

// <Name>
//      ZA_ERROR_DIRECTX_ERROR
//
// <Description>
//      A general error within a Direct X object. This isn't 
//      specified any closer.
//
// <Message>
//      A error accord somewhere within a Direct X object.
//
#define ZA_ERROR_DIRECTX_ERROR					ZAAP_TYPEDEF_ZARESULT(0x8E00)

// <Name>
//      ZA_ERROR_DIRECTX_UNSUPPORTED_FORMAT
//      
// <Description>
//      This error indicates that the ZA_FORMAT has no equal DXGI_FORMAT.
//      
// <Message>
//      A error accord somewhere within a Direct X object.
//

// ******************************
// Direct X component stuff
// ******************************

// <Name>
//      ZA_ERROR_DIRECTX_TEXTURE2D_FILE_ERROR
//
// <Description>
//      A error inside the DXTexture2D class concerning the given file.
//
// <Message>
//      DXTexture2D revived a error from the file loader.
//
#define ZA_ERROR_DIRECTX_TEXTURE2D_FILE_ERROR	ZAAP_TYPEDEF_ZARESULT(0x8E11)

// <Name>
//      ZA_ERROR_DIRECTX_TEXTURE2D_CREATION_ERROR
//
// <Description>
//      The DXTexture2D could not be created for some reason.
//
// <Message>
//      Failed to create a Direct X texture object.
//
#define ZA_ERROR_DIRECTX_TEXTURE2D_CREATION_ERROR	ZAAP_TYPEDEF_ZARESULT(0x8E12)

