#include "DXContext.h"

#include <app/Window.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {

	DXContext::DXContext()
		: Context()
	{
		uint wWidth = Window::GetWidth();
		uint wHeight = Window::GetHeight();
		//
		// Swap chain
		//
		{
			UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#			ifdef ZAAP_DIRECTX_DEBUG
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#			endif

			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			scd.BufferCount = 1;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferDesc.Width = UINT(wWidth);
			scd.BufferDesc.Height = UINT(wHeight);
			scd.BufferDesc.RefreshRate.Numerator = 60;
			scd.BufferDesc.RefreshRate.Denominator = 1;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow = Window::GetHWND();
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

			ZAAP_DXNAME(m_SwapChain, "DXContext::m_SwapChain");
			ZAAP_DXNAME(m_Dev, "DXContext::m_Dev");
			ZAAP_DXNAME(m_Devcon, "DXContext::m_Devcon");
		}
		
	}

	void DXContext::cleanup(void)
	{
		ZAAP_DXRELEASE(m_SwapChain);

		ReportLiveObjects();

		ZAAP_DXRELEASE(m_Devcon);
		ZAAP_DXRELEASE(m_Dev);

		ZA_LOG_CLEANUP();
	}

	void DXContext::swapBuffers()
	{
		m_SwapChain->Present(0, 0);
	}

	//
	// debug util
	//
	void DXContext::ReportLiveObjects()
	{
#ifdef ZAAP_DIRECTX_DEBUG
		ID3D11Debug *debug;
		GetContext()->m_Dev->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
		debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		ZAAP_DXRELEASE(debug);
#endif
	}
}}}
