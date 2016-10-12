#include "Format.h"

namespace zaap
{
#ifdef ZA_INCLUDE_DIRECTX
	
	uint GetFormatSize(ZA_FORMAT format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return 4;
		case ZA_FORMAT_R8G8B8_UINT:
			return 3;
		case ZA_FORMAT_R8_UINT:
			return 1;
		default:
			return 0;
		}
	}

	DXGI_FORMAT GetDirectXFormat(ZA_FORMAT format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ZA_FORMAT_R8G8B8_UINT:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ZA_FORMAT_R8_UINT:
			return DXGI_FORMAT_R8_UNORM;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}
#endif
}
