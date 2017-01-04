#pragma once

#include <ZaapCLI.h>

#include <graphics/Format.h>

namespace ZaapCLI {

	public enum ZA_FORMAT
	{
		ZA_FORMAT_UNKNOWN		= zaap::ZA_FORMAT_UNKNOWN,
		ZA_FORMAT_R8G8B8A8_UINT = zaap::ZA_FORMAT_R8G8B8A8_UINT,
		ZA_FORMAT_R8G8B8_UINT	= zaap::ZA_FORMAT_R8G8B8_UINT,
		ZA_FORMAT_R8_UINT		= zaap::ZA_FORMAT_R8_UINT,
		ZA_FORMAT_A8_UINT		= zaap::ZA_FORMAT_A8_UINT
	};

	static zaap::ZA_FORMAT to_CPP_ZAFormat(ZA_FORMAT format)
	{
		return static_cast<zaap::ZA_FORMAT>(format);
	}
	static ZA_FORMAT to_CLI_ZAFormat(zaap::ZA_FORMAT format)
	{
		return static_cast<ZA_FORMAT>(format);
	}

	public ref class Format
	{
		//returns the size of the format in bytes
		static uint GetFormatSize(ZA_FORMAT format);

		//returns if the red value can be read in the format
		static bool Format_is_R_Readable(ZA_FORMAT format);
		//returns if the red value can be set in the format
		static bool Format_is_R_Setable(ZA_FORMAT format);
		//returns if the green value can be read in the format
		static bool Format_is_G_Readable(ZA_FORMAT format);
		//returns if the green value can be set in the format
		static bool Format_is_G_Setable(ZA_FORMAT format);
		//returns if the blue value can be read in the format
		static bool Format_is_B_Readable(ZA_FORMAT format);
		//returns if the blue value can be set in the format
		static bool Format_is_B_Setable(ZA_FORMAT format);
		//returns if the alpha value can be read in the format
		static bool Format_is_A_Readable(ZA_FORMAT format);
		//returns if the alpha value can be set in the format
		static bool Format_is_A_Setable(ZA_FORMAT format);
	};
}
