#include "DXContext.h"

#include <graphics/shader/DXShader/DXTextureShader.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace DX {

	DXContext::DXContext(Window &window)
		: Context(),
		m_Loader()
	{
		SIZE *size = window.getSize();
		//
		// Swap chain
		//
		{
			UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef ZAAP_DEBUG
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			scd.BufferCount = 1;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferDesc.Width = UINT(size->Width);
			scd.BufferDesc.Height = UINT(size->Height);
			scd.BufferDesc.RefreshRate.Numerator = 60;
			scd.BufferDesc.RefreshRate.Denominator = 1;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow = window.getHWND();
			scd.SampleDesc.Count = 1;//TODO add option
			scd.SampleDesc.Quality = 0;
			scd.Windowed = true;
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			
			D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;
			D3D_FEATURE_LEVEL FeatureLevel;

			D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				creationFlags,
				&FeatureLevels,
				1,
				D3D11_SDK_VERSION,
				&scd,
				&m_SwapChain,
				&m_Dev,
				&FeatureLevel,
				&m_Devcon);

			DXNAME(m_SwapChain, "DXContext::m_SwapChain");
			DXNAME(m_Dev, "DXContext::m_Dev");
			DXNAME(m_Devcon, "DXContext::m_Devcon");
		}
		
	}

	void DXContext::resize(uint width, uint height)
	{
		
	}

	void DXContext::cleanup(void)
	{
		m_Loader.cleanup();

		DXRELEASE(m_SwapChain);

		ReportLiveObjects();

		DXRELEASE(m_Devcon);
		DXRELEASE(m_Dev);

		ZAAP_CLEANUP_LOG("DXContext");
	}

	void DXContext::swapBuffers()
	{
		m_SwapChain->Present(0, 0);
	}

	//
	// Getters
	//
	DXContext* DXContext::GetContext()
	{
		return (DXContext*)s_Context;
	}
	Loader* DXContext::getLoader()
	{
		return &m_Loader;
	}
	ID3D11Device* DXContext::GetDevice()
	{
		return GetContext()->m_Dev;
	}
	ID3D11DeviceContext* DXContext::GetDevContext()
	{
		return GetContext()->m_Devcon;
	}

	IDXGISwapChain* DXContext::GetSwapChain()
	{
		return GetContext()->m_SwapChain;
	}

	Loader* DXContext::GetLoader()
	{
		return &GetContext()->m_Loader;
	}

	//
	// debug util
	//
	void DXContext::ReportLiveObjects()
	{
#ifdef ZAAP_DEBUG
		ID3D11Debug *debug;
		GetContext()->m_Dev->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
		debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		DXRELEASE(debug);
#endif
	}
}}}
