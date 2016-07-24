#pragma once

#pragma warning(push, 0)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dcommon.h>
#pragma warning(pop)

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment( lib, "dxguid.lib")

//DXRelease
#define DXRELEASE_(x) if (x) x->Release(); 
	
#define DXRELEASE(x) \
	{ \
		DXRELEASE_(x) \
		x = nullptr; \
	}


#ifdef ZAAP_DEBUG
#define DXNAME(x, y) /*x is the DX object, y is the name*/ \
	if (x) { /* nullptr == false */  \
		String s(y); \
		x->SetPrivateData(WKPDID_D3DDebugObjectName, s.size(), s.c_str()); \
	}\
	
#else // ZAAP_DEBUG
#	define DXNAME(x, y)
#endif // ZAAP_DEBUG