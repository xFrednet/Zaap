#pragma once

#include <Common.h>
#include <Types.h>

#ifdef ZA_INCLUDE_DIRECTX
#include <graphics/API/DX/DXCommon.h>
#endif

namespace zaap
{
	typedef ZAAP_API enum {
		ZA_FORMAT_UNKNOWN       = 0,
		ZA_FORMAT_R8G8B8A8_UINT = 1,
		ZA_FORMAT_R8G8B8_UINT   = 2,
		ZA_FORMAT_R8_UINT       = 3,
		ZA_FORMAT_A8_UINT       = 4
	} ZA_FORMAT;

	//returns the size of the format in bytes
	ZAAP_API uint GetFormatSize(ZA_FORMAT format);

#ifdef ZA_INCLUDE_DIRECTX
	//returns the corresponding DXGI_FORMAT to the ZA_FORMAT
	ZAAP_API DXGI_FORMAT GetDirectXFormat(ZA_FORMAT format);
#endif

}