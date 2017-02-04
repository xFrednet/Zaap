#pragma once
#include "Common.h"

#ifndef ZA_MULTI_RESULT_SIZE
#	define ZA_MULTI_RESULT_SIZE 8
#else
#	if (ZA_MULTI_RESULT_SIZE <= 2) 
#		pragma message("Zaap ERROR : ZA_MULTI_RESULT_SIZE should be above 2")
#		undef ZA_MULTI_RESULT_SIZE
#		define ZA_MULTI_RESULT_SIZE 8
#	endif
#endif



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

#define ZA_RESULT_RESULT_MASK					ZA_RESULT(0x8000)
#define ZA_RESULT_SOURCE_MASK					ZA_RESULT(0x7F00)
#define ZA_RESULT_CODE_MASK						ZA_RESULT(0x00ff)


/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_MULTI_RESULT //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap {
	
	// <Name>
	//      ZA_MULTI_RESULT
	//
	// <Description>
	//      This value combines multiple ZA_RESULT. New results are added at the 
	//      start of the array. ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
	//      indicates that there are too many ZA_RESULTS for ZA_MULTI_RESULT.
	//
	// <Members>
	//      Results::
	//			A array that can contain several ZA_RESULTs.;;
	//
	typedef struct ZAAP_API ZA_MULTI_RESULT_ {
		ZA_RESULT Results[ZA_MULTI_RESULT_SIZE];

		ZA_MULTI_RESULT_();

		// <Constructor>
		//		ZA_MULTI_RESULT_
		//
		// <Description>
		//		This creates a ZA_MULTI_RESULT from a single ZA_RESULT.
		//
		// <Input>
		//		result::
		//			The result that is added at the front;;
		//
		ZA_MULTI_RESULT_(ZA_RESULT result);

		uint size() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Operators // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Function>
		//      operator[]
		//
		// <Description>
		//      This enables the user to access the Results 
		//      through the square brackets.
		//      
		// <Input>
		//      index: 
		//         The index of the requested @ZA_RESULT.
		//
		// <Return>
		//      The @ZA_RESULT for the given index.
		//
		ZA_RESULT& operator[](int index);

		// <Function>
		//      operator[]
		//
		// <Description>
		//      This enables the user to access the Results through
		//      the square brackets. This method can be used by
		//      a constant @ZA_MULTI_RESULT.
		//      
		// <Input>
		//      index: 
		//          The index of the requested ZA_RESULT.
		//
		// <Return>
		//      The ZA_RESULT for the given index.
		//
		const ZA_RESULT& operator[] (const int index) const;

		// <Function>
		//      operator+=
		//
		// <Descritpion>
		//      This operator adds the given ZA_RESULT to the start of this 
		//      ZA_MULTI_RESULT. 
		//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
		//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
		//      in the last ZA_RESULT. The given arguments are still 
		//      added in the right order.
		//
		// <Note>
		//      This operator is just a link to AddZAResult()
		//
		// <Input>
		//      other : The ZA_RESULT on the other side of the += operator.
		//
		// <Return>
		//      This returns this instance of the ZA_MULTI_RESULT.
		//
		ZA_MULTI_RESULT_& operator+=(const ZA_RESULT& other);

		// <Function>
		//      operator+=
		//
		// <Descritpion>
		//      This operator adds the given ZA_MULTI_RESULT to the start of this 
		//      ZA_MULTI_RESULT. 
		//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
		//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
		//      in the last ZA_RESULT. The given arguments are still 
		//      added in the right order.
		//
		// <Note>
		//      This operator is just a link to AddZAResult()
		//
		// <Input>
		//      other : The ZA_MULTI_RESULT on the other side of the += operator.
		//
		// <Return>
		//      This returns this instance of the ZA_MULTI_RESULT.
		//
		ZA_MULTI_RESULT_& operator+=(const ZA_MULTI_RESULT_& other);

		// <Function>
		//      operator+
		//
		// <Descritpion>
		//      This operator adds the given ZA_RESULT to the start of this 
		//      ZA_MULTI_RESULT. 
		//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
		//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
		//      in the last ZA_RESULT. The given arguments are still 
		//      added in the right order.
		//
		// <Note>
		//      This operator is just a link to AddZAResult()
		//
		// <Input>
		//      other : The ZA_RESULT on the other side of the + operator.
		//
		// <Return>
		//      This returns the combined results.
		//
		inline ZA_MULTI_RESULT_ operator+(const ZA_RESULT& other) const;

		// <Function>
		//      operator+
		//
		// <Descritpion>
		//      This operator adds the given ZA_MULTI_RESULT to the start of this 
		//      ZA_MULTI_RESULT. 
		//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
		//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
		//      in the last ZA_RESULT. The given arguments are still 
		//      added in the right order.
		//
		// <Note>
		//      This operator is just a link to AddZAResult()
		//
		// <Input>
		//      other : The ZA_MULTI_RESULT on the other side of the + operator.
		//
		// <Return>
		//      This returns the combined results.
		//
		inline ZA_MULTI_RESULT_ operator+(const ZA_MULTI_RESULT_& other) const;

		// <Function>
		//      operator==
		//
		// <Description>
		//      This operator performs the requested operation with
		//      the first result in the array. This is a quicker excess
		//      for the first ZA_RESULT.
		//      This is also important for the test macros.
		//      
		// <Note>
		//      Yes. Yes! I wrote it in a way that I could just copy and past
		//      it for the other operators
		//      
		// <Input>
		//      other : The ZA_RESULT on the right of the operator
		//
		// <Return>
		//      Returns the test result.
		//
		inline bool operator==(const ZA_RESULT& other) const;

		// <Function>
		//      operator!=
		//
		// <Description>
		//      This operator performs the requested operation with
		//      the first result in the array. This is a quicker excess
		//      for the first ZA_RESULT.
		//      This is also important for the test macros.
		//      
		// <Note>
		//      Yes. Yes! I wrote it in a way that I could just copy and past
		//      it for the other operators
		//      
		// <Input>
		//      other : The ZA_RESULT on the right of the operator
		//
		// <Return>
		//      Returns the test result.
		//
		inline bool operator!=(const ZA_RESULT& other) const;

		// <Function>
		//      operator<
		//
		// <Description>
		//      This operator performs the requested operation with
		//      the first result in the array. This is a quicker excess
		//      for the first ZA_RESULT.
		//      This is also important for the test macros.
		//      
		// <Note>
		//      Yes. Yes! I wrote it in a way that I could just copy and past
		//      it for the other operators
		//      
		// <Input>
		//      other : The ZA_RESULT on the right of the operator
		//
		// <Return>
		//      Returns the test result.
		//
		inline bool operator<(const ZA_RESULT& other) const;

		// <Function>
		//      operator>
		//
		// <Description>
		//      This operator performs the requested operation with
		//      the first result in the array. This is a quicker excess
		//      for the first ZA_RESULT.
		//      This is also important for the test macros.
		//      
		// <Note>
		//      Yes. Yes! I wrote it in a way that I could just copy and past
		//      it for the other operators
		//      
		// <Input>
		//      other : The ZA_RESULT on the right of the operator
		//
		// <Return>
		//      Returns the test result.
		//
		inline bool operator>(const ZA_RESULT& other) const;

		// <Function>
		//      operator<=
		//
		// <Description>
		//      This operator performs the requested operation with
		//      the first result in the array. This is a quicker excess
		//      for the first ZA_RESULT.
		//      This is also important for the test macros.
		//      
		// <Note>
		//      Yes. Yes! I wrote it in a way that I could just copy and past
		//      it for the other operators
		//      
		// <Input>
		//      other : The ZA_RESULT on the right of the operator
		//
		// <Return>
		//      Returns the test result.
		//
		inline bool operator<=(const ZA_RESULT& other) const;

		// <Function>
		//      operator>=
		//
		// <Description>
		//      This operator performs the requested operation with
		//      the first result in the array. This is a quicker excess
		//      for the first ZA_RESULT.
		//      This is also important for the test macros.
		//      
		// <Note>
		//      Yes. Yes! I wrote it in a way that I could just copy and past
		//      it for the other operators
		//      
		// <Input>
		//      other : The ZA_RESULT on the right of the operator
		//
		// <Return>
		//      Returns the test result.
		//
		inline bool operator>=(const ZA_RESULT& other) const;


	} ZA_MULTI_RESULT;
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // OPERATIONS //
/* //////////////////////////////////////////////////////////////////////////////// */
#define ZAAP_TYPEDEF_ZARESULT(x)				ZA_RESULT(x)

#define ZA_FAILED(x)   (x < 0)
#define ZA_SUCCEDED(x) (x >= 0)

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT util //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap {
	ZAAP_API void SubmitZAResult(ZA_RESULT result);

	// <Function>
	//		SubmitZAResult
	//
	// <Description>
	//		This prints the error message to the console.
	//
	// <Input>
	//		result::
	//			The result that should be printed.;;
	//		file::
	//			The file is filled in by the ZA_SUBMIT_ERROR macro. <\n>
	//			The file is added to the console for more information.;;
	//		line:
	//			The line is also added by the ZA_SUBMIT_ERROR macro. <\n>
	//			It is added to the console.
	//
	ZAAP_API void SubmitZAResult(const ZA_RESULT& result, const String& file, const uint& line);

	// <Function>
	//      CombineZAResults
	//
	// <Descripion>
	//      This method combines the given ZA_RESULTs into a 
	//      ZA_MULTI_RESULT. 
	//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
	//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
	//      in the last ZA_RESULT the given arguments are still 
	//      added in the right order.
	//
	// <Note>
	//      Use CombineZAResults({result_0, result_1, result_2}) to combine
	//      multiple ZA_RESULTS.
	//      
	// <Input>
	//      results::
	//			This is a list that can take in multiple ZA_RESULT.;;
	//
	// <Return>
	//      The combined sub-results in from of a ZA_MULTI_RESULT.
	//
	ZAAP_API ZA_MULTI_RESULT CombineZAResults(std::initializer_list<ZA_RESULT> results);

	// <Function>
	//      AddZAResult
	//
	// <Descripion>
	//      This method adds the given ZA_RESULT to the start of the 
	//      ZA_MULTI_RESULT. 
	//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
	//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
	//      in the last ZA_RESULT the given arguments are still 
	//      added in the right order.
	//      
	// <Examples>
	//      Example 1:
	//          ZA_MULTI_RESULT(Result_1, Result_2, Result_3, 0x0000)
	//           + 
	//          Result_4
	//           = 
	//          ZA_MULTI_RESULT(Result_4, Result_1, Result_2, Result_3)
	//      
	//      Example 2:
	//          ZA_MULTI_RESULT(Result_1, Result_2, Result_3, Result_4)
	//           + 
	//          Result_5
	//           = 
	//          ZA_MULTI_RESULT(Result_5, Result_1, Result_2, ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT)
	//      
	// <Note>
	//      Use AddZAResults(ZA_MULTI_RESULT, {result_0, result_1, result_2})
	//      to add multiple ZA_RESULTS.
	//      
	// <Input>
	//      srcResult   : The main ZA_MULTI_RESULT. The results are
	//                    added at the start of the ZA_MULTI_RESULT.
	//      result      : The result that should be added to the srcResult.
	//
	// <Return>
	//      The combined results in from of a ZA_MULTI_RESULT.
	//
	ZAAP_API ZA_MULTI_RESULT AddZAResult(ZA_MULTI_RESULT srcResult, ZA_RESULT result);

	// <Function>
	//      AddZAResults
	//
	// <Descripion>
	//      This method adds the given ZA_RESULTs to the start of the 
	//      ZA_MULTI_RESULT. 
	//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
	//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
	//      in the last ZA_RESULT the given arguments are still 
	//      added in the right order.
	//      
	// <Examples>
	//      Example 1:
	//          ZA_MULTI_RESULT(Result_1, Result_2, Result_3, 0x0000)
	//           + 
	//          results(Result_4)
	//           = 
	//          ZA_MULTI_RESULT(Result_4, Result_1, Result_2, Result_3)
	//      
	//      
	//      Example 2:
	//          ZA_MULTI_RESULT(0x0000, 0x0000, 0x0000, 0x0000)
	//           + 
	//          results(Result_1, Result_2)
	//           = 
	//          ZA_MULTI_RESULT(Result_1, Result_2, 0x0000, 0x0000)
	//      
	//      
	//      Example 3:
	//          ZA_MULTI_RESULT(Result_1, Result_2, Result_3, 0x0000)
	//           + 
	//          results(Result_4, Result_5)
	//           = 
	//          ZA_MULTI_RESULT(Result_4, Result_5, Result_1, ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT)
	//      
	// <Note>
	//      Use AddZAResults(ZA_MULTI_RESULT, {result_0, result_1, result_2})
	//      to add multiple ZA_RESULTS.
	//      
	// <Input>
	//      srcResult::
	//			The main ZA_MULTI_RESULT. The results are added at the
	//			start of the ZA_MULTI_RESULT.;;
	//      results:: 
	//			The results that are added to the srcResult. This is a list
	//			that can take in multiple ZA_RESULT.
	//
	// <Return>
	//      The combined results in from of a ZA_MULTI_RESULT.
	//
	ZAAP_API ZA_MULTI_RESULT AddZAResults(ZA_MULTI_RESULT srcResult, std::initializer_list<ZA_RESULT> results);

	// <Function>
	//      CombineZAResult
	//
	// <Description>
	//      This method combines two ZA_MULTI_RESULTS. This is done by
	//      adding the results from the second ZA_MULTI_RESULTS to the
	//      start of the new ZA_MULTI_RESULTS. 
	//      A overflow (more ZA_RESULTS than ZA_MULTI_RESULT_SIZE)
	//      is indicated by ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT
	//      in the last ZA_RESULT the given arguments are still 
	//      added in the right order.
	//      
	// <Examples>
	//      Example 1:
	//          ZA_MULTI_RESULT(Result_1, Result_2, Result_3, 0x0000)
	//           + 
	//          ZA_MULTI_RESULT(Result_4, 0x0000, 0x0000, 0x0000)
	//           = 
	//          ZA_MULTI_RESULT(Result_4, Result_1, Result_2, Result_3)
	//      
	//      
	//      Example 2:
	//          ZA_MULTI_RESULT(0x0000, 0x0000, 0x0000, 0x0000)
	//           + 
	//          ZA_MULTI_RESULT(Result_1, Result_2, 0x0000, 0x0000)
	//           = 
	//          ZA_MULTI_RESULT(Result_1, Result_2, 0x0000, 0x0000)
	//      
	//      
	//      Example 3:
	//          ZA_MULTI_RESULT(Result_1, Result_2, Result_3, 0x0000)
	//           + 
	//          ZA_MULTI_RESULT(Result_4, Result_5, 0x0000, 0x0000)
	//           = 
	//          ZA_MULTI_RESULT(Result_4, Result_5, Result_1, ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT)
	//      
	//      
	// <Input>
	//      mResult1    : The base ZA_MULTI_RESULT
	//      
	//      mResult2    : The second ZA_MULTI_RESULT that gets added to
	//                    the base ZA_MULTI_RESULT.
	//      
	// <Return>
	//      The combined ZA_MULTI_RESULT in from of single a ZA_MULTI_RESULT.
	//
	ZAAP_API ZA_MULTI_RESULT CombineZAResults(ZA_MULTI_RESULT mResult1, 
		ZA_MULTI_RESULT mResult2);
}
#ifndef ZA_SUBMIT_ERROR
#	define ZA_SUBMIT_ERROR(x) zaap::SubmitZAResult(x, __FILE__, __LINE__)
#endif

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT messages //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap
{
	// <Function>
	//		GetResultSource
	//
	// <Description>
	//		This returns the source of the submitted result.
	//
	// <Input>
	//		result::
	//			The base result.;;
	//
	// <Return>
	//		This returns the source result.
	//
	ZAAP_API inline ZA_RESULT GetResultSource(const ZA_RESULT& result);

	// <Function>
	//		GetZAResultMessage
	//
	// <Description>
	//		This returns the messages of the ZA_RESULT that
	//		are inside the ZA_MULTI_RESULT.
	//
	// <Input>
	//		result::
	//			The ZA_MULTI_RESULT of the requested messages.;;
	//
	// <Return>
	//		The message of the ZA_MULTI_RESULT or a default
	//		"missing message" message.
	//
	ZAAP_API String GetZAResultMessage(const ZA_MULTI_RESULT& result);

	// <Function>
	//		GetZAResultMessage
	//
	// <Description>
	//		This returns the message of the submitted ZA_RESULT. </n>
	//
	// <Input>
	//		result::
	//			The ZA_RESULT of the requested message.;;
	//
	// <Return>
	//		The message of the ZA_RESULT or a default
	//		"missing message" message.
	//
	ZAAP_API String GetZAResultMessage(const ZA_RESULT& result);
}



/* //////////////////////////////////////////////////////////////////////////////// */
// // Results //
/* //////////////////////////////////////////////////////////////////////////////// */
#define ZA_RESULT_ERROR							ZAAP_TYPEDEF_ZARESULT(0x8000)
#define ZA_RESULT_SUCCESS						ZAAP_TYPEDEF_ZARESULT(0x0000)
#define ZA_OK									ZAAP_TYPEDEF_ZARESULT(0x0000)





/* //////////////////////////////////////////////////////////////////////////////// */
// // Sources //
/* //////////////////////////////////////////////////////////////////////////////// */
#define ZA_RESULT_SOURCE_NO_SOURCE				ZAAP_TYPEDEF_ZARESULT(0x0000)
#define ZA_RESULT_SOURCE_MATH					ZAAP_TYPEDEF_ZARESULT(0x0100)
#define ZA_RESULT_SOURCE_SYSTEM					ZAAP_TYPEDEF_ZARESULT(0x0200)
#define ZA_RESULT_SOURCE_API					ZAAP_TYPEDEF_ZARESULT(0x0D00) //API said NO!!!
#define ZA_RESULT_SOURCE_DIRECTX				ZAAP_TYPEDEF_ZARESULT(0x0E00)
#define ZA_RESULT_SOURCE_OPENGL					ZAAP_TYPEDEF_ZARESULT(0x0F00) //I'll do that. Some dark day.





/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT_SOURCE_NO_SOURCE //
/* //////////////////////////////////////////////////////////////////////////////// */
#define ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT ZAAP_TYPEDEF_ZARESULT(0x8001)




/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT_SOURCE_MATH codes //
/* //////////////////////////////////////////////////////////////////////////////// */
#define ZA_ERROR_DIVISION_BY_ZERO				ZAAP_TYPEDEF_ZARESULT(0x8101)
#define ZA_ERROR_MATH_WRONG_CLAMP_VALUES		ZAAP_TYPEDEF_ZARESULT(0x8102)





/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT_SOURCE_SYSTEM codes //
/* //////////////////////////////////////////////////////////////////////////////// */
//     - File stuff (input/output)
//     - Memory management
/* ********************************************************* */
// * File stuff *
/* ********************************************************* */
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

/* ********************************************************* */
// * Memory management *
/* ********************************************************* */





/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT_SOURCE_API //
/* //////////////////////////////////////////////////////////////////////////////// */
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
#define ZA_ERROR_API_ERROR							ZAAP_TYPEDEF_ZARESULT(0x8D00)

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

/* ********************************************************* */
// * API Components *
/* ********************************************************* */

/* ##################################### */
// # Shader (0x8D1x) #
/* ##################################### */

// <Macro>
//		ZA_ERROR_API_SHADER_ERROR
//
// <Message>
//		The shader threw a Error.
//
#define ZA_ERROR_API_SHADER_ERROR				ZAAP_TYPEDEF_ZARESULT(0x8D10)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~ COMPILATION_ERROR ~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// <Macro>
//		ZA_ERROR_API_SHADER_VERTEX_SHADER_COMPILATION_ERROR
//
// <Description>
//		The vertex shader couldn't be compiled. The error message should be
//		printed to the console.
//
// <Message>
//		The vertex shader couldn't be compiled.
//
#define ZA_ERROR_API_SHADER_VERTEX_SHADER_COMPILATION_ERROR			ZAAP_TYPEDEF_ZARESULT(0x8D11)

// <Macro>
//		ZA_ERROR_API_SHADER_GEOMETRY_SHADER_COMPILATION_ERROR
//
// <Description>
//		The geometry shader couldn't be compiled. The error message should be
//		printed to the console.
//
// <Message>
//		The geometry shader couldn't be compiled.
//
#define ZA_ERROR_API_SHADER_GEOMETRY_SHADER_COMPILATION_ERROR		ZAAP_TYPEDEF_ZARESULT(0x8D12)

// <Macro>
//		ZA_ERROR_API_SHADER_PIXEL_SHADER_COMPILATION_ERROR
//
// <Description>
//		The pixel shader couldn't be compiled. The error message should be
//		printed to the console.
//
// <Message>
//		The pixel shader couldn't be compiled.
//
#define ZA_ERROR_API_SHADER_PIXEL_SHADER_COMPILATION_ERROR			ZAAP_TYPEDEF_ZARESULT(0x8D13)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~ CBUFFER_ERROR ~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* ##################################### */
// # API Texture (0x8D2x) #
/* ##################################### */

// <Name>
//      ZA_ERROR_API_TEXTURE_ERROR
//
// <Description>
//      A error general concerning a texture from the selected API.
//
// <Message>
//     A texture from the current API caused an Error.
// 
#define ZA_ERROR_API_TEXTURE_ERROR							ZAAP_TYPEDEF_ZARESULT(0x8D20)

// <Name>
//      ZA_ERROR_API_TEXTURE1D_CREATION_ERROR
//
// <Description>
//      The Texture1D could not be created for some reason.
//
// <Message>
//      Failed to create a texture1D object for the current API.
//
#define ZA_ERROR_API_TEXTURE1D_CREATION_ERROR				ZAAP_TYPEDEF_ZARESULT(0x8D21)

// <Name>
//      ZA_ERROR_API_TEXTURE2D_CREATION_ERROR
//
// <Description>
//      The Texture2D could not be created for some reason.
//
// <Message>
//      Failed to create a texture2D object for the current API.
//
#define ZA_ERROR_API_TEXTURE2D_CREATION_ERROR				ZAAP_TYPEDEF_ZARESULT(0x8D22)

// <Name>
//      ZA_ERROR_API_TEXTURE3D_CREATION_ERROR
//
// <Description>
//      The Texture3D could not be created for some reason.
//
// <Message>
//      Failed to create a texture3D object for the current API.
//
#define ZA_ERROR_API_TEXTURE3D_CREATION_ERROR				ZAAP_TYPEDEF_ZARESULT(0x8D23)

// <Name>
//      ZA_ERROR_API_TEXTURE_FILE_ERROR
//
// <Description>
//      The file given to Texture2D caused a error.
//
// <Note>
//      The file error might also be included in a ZA_MULTI_RESULT.
//      
// <Message>
//      The file given texture file caused an error.
//
#define ZA_ERROR_API_TEXTURE_FILE_ERROR						ZAAP_TYPEDEF_ZARESULT(0x8D24)

// <Name>
//      ZA_ERROR_API_TEXTURE_INVALID_COMPONENTS
// 
// <Message>
//      The texture has invalid components.
//      
#define ZA_ERROR_API_TEXTURE_INVALID_COMPONENTS				ZAAP_TYPEDEF_ZARESULT(0x8D25)

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT_SOURCE_API_DIRECTX //
/* //////////////////////////////////////////////////////////////////////////////// */

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
#define ZA_ERROR_DIRECTX_ERROR									ZAAP_TYPEDEF_ZARESULT(0x8E00)

// <Name>
//      ZA_ERROR_DIRECTX_UNSUPPORTED_FORMAT
//      
// <Description>
//      This error indicates that the ZA_FORMAT has no equal DXGI_FORMAT.
//      
// <Message>
//      A error accord somewhere within a Direct X object.
//
#define ZA_ERROR_DIRECTX_UNSUPPORTED_FORMAT						ZAAP_TYPEDEF_ZARESULT(0x8E01)

/* ********************************************************* */
// * Direct X component stuff *
/* ********************************************************* */

/* ##################################### */
// # Direct X BlendState #
/* ##################################### */

// <Name>
//      ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR
//
// <Message>
//      Direct X failed to create a BlendState with the requested options.
//
#define ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR				ZAAP_TYPEDEF_ZARESULT(0x8E21)

// <Name>
//      ZA_ERROR_DIRECTX_DEPTH_STENCIL_STATE_CREATION_ERROR
//
// <Message>
//      Direct X failed to create a DepthStencilState with the requested options.
//
#define ZA_ERROR_DIRECTX_DEPTH_STENCIL_STATE_CREATION_ERROR		ZAAP_TYPEDEF_ZARESULT(0x8E21)
