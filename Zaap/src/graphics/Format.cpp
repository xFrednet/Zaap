#include "Format.h"

namespace zaap
{
	
	uint GetFormatSize(ZA_FORMAT format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return 4;
		case ZA_FORMAT_R8G8B8_UINT:
			return 3;
		case ZA_FORMAT_R8_UINT:
		case ZA_FORMAT_A8_UINT:
			return 1;
		default:
			return 0;
		}
	}

	//
	// Red
	//
	bool Format_is_R_Readable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
		case ZA_FORMAT_R8G8B8_UINT:
		case ZA_FORMAT_R8_UINT:
		case ZA_FORMAT_A8_UINT:
			return true;
		default:
			return false;
		}
	}
	bool Format_is_R_Setable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
		case ZA_FORMAT_R8G8B8_UINT:
		case ZA_FORMAT_R8_UINT:
			return true;
		case ZA_FORMAT_A8_UINT:
		default:
			return false;
		}
	}

	//
	// Green
	// 
	bool Format_is_G_Readable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
		case ZA_FORMAT_R8G8B8_UINT:
			return true;
		case ZA_FORMAT_R8_UINT:
			return false;
		case ZA_FORMAT_A8_UINT:
			return true;
		default:
			return false;
		}
	}
	bool Format_is_G_Setable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
		case ZA_FORMAT_R8G8B8_UINT:
			return true;
		case ZA_FORMAT_R8_UINT:
		case ZA_FORMAT_A8_UINT:
		default:
			return false;
		}
	}

	//
	// Blue
	//
	bool Format_is_B_Readable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
		case ZA_FORMAT_R8G8B8_UINT:
			return true;
		case ZA_FORMAT_R8_UINT:
			return false;
		case ZA_FORMAT_A8_UINT:
			return true;
		default:
			return false;
		}
	}
	bool Format_is_B_Setable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
		case ZA_FORMAT_R8G8B8_UINT:
			return true;
		case ZA_FORMAT_R8_UINT:
		case ZA_FORMAT_A8_UINT:
		default:
			return false;
		}
	}

	//
	// Alpha
	//
	bool Format_is_A_Readable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return true;
		case ZA_FORMAT_R8G8B8_UINT:
		case ZA_FORMAT_R8_UINT:
			return false;
		case ZA_FORMAT_A8_UINT:
			return true;
		default:
			return false;
		}
	}
	bool Format_is_A_Setable(const ZA_FORMAT& format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return true;
		case ZA_FORMAT_R8G8B8_UINT:
		case ZA_FORMAT_R8_UINT:
			return false;
		case ZA_FORMAT_A8_UINT:
			return true;
		default:
			return false;
		}
	}

#ifdef ZA_INCLUDE_DIRECTX
	DXGI_FORMAT GetDirectXFormat(ZA_FORMAT format)
	{
		switch (format)
		{
		case ZA_FORMAT_R8G8B8A8_UINT:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case ZA_FORMAT_R8G8B8_UINT:
			return DXGI_FORMAT_R8G8B8A8_UNORM;//This format isn't supported by Direct3D
		case ZA_FORMAT_R8_UINT:
			return DXGI_FORMAT_R8_UNORM;
		case ZA_FORMAT_A8_UINT:
			return DXGI_FORMAT_A8_UNORM;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}
#endif
}
