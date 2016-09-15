#include "StringUtil.h"

using namespace zaap;

String StringUtil::to_string(const float &f)
{
	return std::to_string(f);
}

String StringUtil::getDateString(const time_t const time)
{
	char buffer[22];
	strftime(buffer, 22, "[%d-%m-%Y %I:%M:%S]", localtime(&time));
	return String(buffer);
}
