#include "DXContext.h"

#include <app/Window.h>
#include <util/Log.h>
#include <graphics/Color.h>
#include <events/Input.h>

#include <graphics/API/DX/DXRenderTarget.h>

namespace zaap { namespace graphics { namespace DX {

	DXContext::DXContext()
		: Context(),
		m_RenderTarget(nullptr)
	{
		m_RenderTarget = new DXRenderTarget;
	}

	DXContext::~DXContext()
	{
		delete m_RenderTarget;
		m_RenderTarget = nullptr;

		ZA_DXRELEASE(m_SwapChain);

		ReportLiveObjects();

		ZA_DXRELEASE(m_Devcon);
		ZA_DXRELEASE(m_Dev);

		ZA_LOG_CLEANUP();
	}

	ZA_RESULT DXContext::init()
	{
		uint wWidth = Window::GetWidth();
		uint wHeight = Window::GetHeight();
		HRESULT hr;
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

			scd.BufferCount			= 1;
			scd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferDesc.Width	= UINT(wWidth);
			scd.BufferDesc.Height	= UINT(wHeight);
			scd.BufferDesc.RefreshRate.Numerator = 60;
			scd.BufferDesc.RefreshRate.Denominator = 1;
			scd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow		= Window::GetHWND();
			scd.SampleDesc.Count	= 1;//TODO add option
			scd.SampleDesc.Quality	= 0;
			scd.Windowed			= true;
			scd.Flags				= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;
			D3D_FEATURE_LEVEL FeatureLevel;

			hr = D3D11CreateDeviceAndSwapChain(NULL,
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
			ZA_DXNAME(m_SwapChain, "DXContext::m_SwapChain");
			ZA_DXNAME(m_Dev, "DXContext::m_Dev");
			ZA_DXNAME(m_Devcon, "DXContext::m_Devcon");

			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_INIT_ERROR;
		}
		//
		// RenderTarget
		//
		resize(wWidth, wHeight);
		Input::AddWindowCallback(ZA_METHOD_1(DXContext::windowCallback));

		return ZA_OK;
	}

	API::RenderTarget* DXContext::getRenderTarget()
	{
		return m_RenderTarget;
	}

	void DXContext::prepareFrame()
	{
		m_RenderTarget->clearRenderTarget(Color(1.0f, 1.0f, 1.0f, 1.0f));
	}
	void DXContext::presentFrame()
	{
		m_SwapChain->Present(0, 0);
	}

	void DXContext::windowCallback(const Event& windowEvent)
	{
		if (windowEvent.getEventType() != WINDOW_RESIZE_EVENT) return;

		WindowResizeEvent* event = (WindowResizeEvent*)&windowEvent;
		resize(event->getWidth(), event->getHeight());
	}
	void DXContext::resize(const uint& width, const uint& height)
	{
		//TODO add a error message for hr
		HRESULT hr;
		m_Devcon->OMSetRenderTargets(0, nullptr, nullptr);
		ZA_DXRELEASE(m_RenderTarget->m_RenderTargetView);
		ZA_DXRELEASE(m_RenderTarget->m_Texture);

		//resizing the backBuffer
		{
			ID3D11Texture2D* backBuffer;
			ID3D11RenderTargetView* rtView;

			hr = m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

			hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
			ZA_DXNAME(backBuffer, "DXContext::backBuffer");

			hr = m_Dev->CreateRenderTargetView(backBuffer, nullptr, &rtView);
			ZA_DXNAME(rtView, "DXContext::renderTargetView");

			m_RenderTarget->setTarget(rtView, backBuffer, width, height, true);
		}
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
		ZA_DXRELEASE(debug);
#endif
	}
}}}
