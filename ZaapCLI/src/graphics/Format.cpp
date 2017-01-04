#include "Format.h"

namespace ZaapCLI {
	
	//
	// Format class
	//
	uint Format::GetFormatSize(ZA_FORMAT format)
	{
		return zaap::GetFormatSize(to_CPP_ZAFormat(format));
	}

	//
	// Red
	//
	bool Format::Format_is_R_Readable(ZA_FORMAT format)
	{
		return zaap::Format_is_R_Readable(to_CPP_ZAFormat(format));
	}
	bool Format::Format_is_R_Setable(ZA_FORMAT format)
	{
		return zaap::Format_is_R_Setable(to_CPP_ZAFormat(format));
	}
	
	//
	// Green
	//
	bool Format::Format_is_G_Readable(ZA_FORMAT format)
	{
		return zaap::Format_is_G_Readable(to_CPP_ZAFormat(format));
	}
	bool Format::Format_is_G_Setable(ZA_FORMAT format)
	{
		return zaap::Format_is_G_Setable(to_CPP_ZAFormat(format));
	}

	//
	// Blue
	//
	bool Format::Format_is_B_Readable(ZA_FORMAT format)
	{
		return zaap::Format_is_B_Readable(to_CPP_ZAFormat(format));
	}
	bool Format::Format_is_B_Setable(ZA_FORMAT format)
	{
		return zaap::Format_is_B_Setable(to_CPP_ZAFormat(format));
	}
	
	//
	// Alpha
	//
	bool Format::Format_is_A_Readable(ZA_FORMAT format)
	{
		return zaap::Format_is_A_Readable(to_CPP_ZAFormat(format));
	}
	bool Format::Format_is_A_Setable(ZA_FORMAT format)
	{
		return zaap::Format_is_A_Setable(to_CPP_ZAFormat(format));
	}
}
