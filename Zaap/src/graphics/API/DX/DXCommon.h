#pragma once

#pragma warning(push, 0)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#pragma warning(pop)

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "d3dcompiler.lib")

//DXRelease
#define ZA_DXRELEASE(x)       \
	if (x)                 \
	{                      \
		x->Release();      \
		x = nullptr;        \
	}


#ifdef ZAAP_DIRECTX_DEBUG
	
	/*x is the DX object, y is the name*/
#	define ZA_DXNAME(x, y)                                                   \
		if (x) { /* nullptr == false */                                        \
			String s(y);                                                       \
			x->SetPrivateData(WKPDID_D3DDebugObjectName, s.size(), s.c_str()); \
		}                                                                      \
	
#else // ZAAP_DEBUG
#	define ZA_DXNAME(x, y)
#endif // ZAAP_DEBUG