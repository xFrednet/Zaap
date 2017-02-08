#include "StringUtil.h"

namespace zaap
{
	String StringUtil::getDateString(const time_t& time)
	{
		char buffer[22];
		strftime(buffer, 22, "[%d-%m-%Y %I:%M:%S]", localtime(&time));
		return String(buffer);
	}

	std::vector<String> StringUtil::Split(String baseString, const String& delimiters)
	{
		std::vector<std::string> splitString;

		size_t pos = 0;
		while ((pos = baseString.find(delimiters)) != std::string::npos)
		{
			splitString.push_back(baseString.substr(0, pos));
			baseString.erase(0, pos + delimiters.length());
		}
		splitString.push_back(baseString);
		return splitString;
	}

	bool StringUtil::StartsWith(const String& baseString, const String& str2)
	{
		if (str2.length() > baseString.length() || 
			str2.size() > baseString.size())
			return false;

		return memcmp(baseString.c_str(), str2.c_str(), str2.size()) == 0;
	}

	String StringUtil::Replace(String baseString, const String& oldString, const String& newString)
	{
		if (baseString.empty() || oldString.empty())
			return baseString;

		size_t offset = 0;
		size_t pos;

		//tests if the oldString can be replaced directly
		while((pos = baseString.find(oldString, offset)) != baseString.npos)
		{
			baseString.replace(pos, oldString.size(), newString);

			offset = pos + newString.size(); // move one more maybe
		}

		return baseString;
	}
}
