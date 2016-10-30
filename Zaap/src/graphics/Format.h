#pragma once

#include <Common.h>

#ifdef ZA_INCLUDE_DIRECTX
#include <graphics/API/DX/DXCommon.h>
#endif

namespace zaap {
	
	typedef ZAAP_API enum {
		ZA_FORMAT_UNKNOWN       = 0,
		ZA_FORMAT_R8G8B8A8_UINT = 1,
		ZA_FORMAT_R8G8B8_UINT   = 2,
		ZA_FORMAT_R8_UINT       = 3,
		ZA_FORMAT_A8_UINT       = 4
	} ZA_FORMAT;

	//returns the size of the format in bytes
	ZAAP_API uint GetFormatSize(ZA_FORMAT format);
	
	//returns if the red value can be read in the format
	ZAAP_API bool Format_is_R_Readable(const ZA_FORMAT &format);
	//returns if the red value can be set in the format
	ZAAP_API bool Format_is_R_Setable(const ZA_FORMAT &format);
	//returns if the green value can be read in the format
	ZAAP_API bool Format_is_G_Readable(const ZA_FORMAT &format);
	//returns if the green value can be set in the format
	ZAAP_API bool Format_is_G_Setable(const ZA_FORMAT &format);
	//returns if the blue value can be read in the format
	ZAAP_API bool Format_is_B_Readable(const ZA_FORMAT &format);
	//returns if the blue value can be set in the format
	ZAAP_API bool Format_is_B_Setable(const ZA_FORMAT &format);
	//returns if the alpha value can be read in the format
	ZAAP_API bool Format_is_A_Readable(const ZA_FORMAT &format);
	//returns if the alpha value can be set in the format
	ZAAP_API bool Format_is_A_Setable(const ZA_FORMAT &format);

#ifdef ZA_INCLUDE_DIRECTX
	//returns the corresponding DXGI_FORMAT to the ZA_FORMAT
	ZAAP_API DXGI_FORMAT GetDirectXFormat(ZA_FORMAT format);
#endif

}