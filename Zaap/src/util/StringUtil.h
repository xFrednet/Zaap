#pragma once

#pragma warning( disable : 4114)

#include <Common.h>

#include <string>

typedef std::string String;

namespace zaap {

	class ZAAP_API StringUtil
	{
	public:
		static String getDateString(const time_t const time = time(0));

		// <Function>
		//      Split
		//
		// <Description>
		//      This splits the string at the delimiters.
		//
		// <Note>
		//      The vector has a minimal length of 1 because the baseString
		//      is added if the string wasn't split.
		//
		// <Input>
		//      baseString:
		//          The String that is split at the specified delimiters.
		//      delimiters:
		//          The char sequence where the baseString is split.
		//
		// <Return>
		//      A vector that stores the split strings.
		//
		static std::vector<String> Split(String baseString, const String& delimiters);

		// <Function>
		//      StartsWith
		//
		// <Description>
		//      This Method tests if the baseString starts with the same
		//      like str2.
		//
		// <Note>
		//      This also returns false if str2 is longer than the baseString.
		//
		// <Input>
		//      baseString:
		//          The string where the start is test.
		//      str2:
		//          The sting that is compared to the start of the baseString.
		//
		// <Return>
		//      The test result.
		//
		static bool StartsWith(const String& baseString, const String& str2);

	};

}
