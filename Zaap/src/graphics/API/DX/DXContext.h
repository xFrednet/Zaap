#pragma once

#include <Common.h>
#ifdef ZAAP_INCLUDE_DIRECTX

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/Context.h>
#include <events/WindowEvent.h>

namespace zaap { namespace graphics { namespace DX {
	
	class DXRenderTarget;

	class ZAAP_API DXContext : public API::Context
	{
	protected:
		ID3D11Device *m_Dev;
		ID3D11DeviceContext *m_Devcon;
		
		IDXGISwapChain *m_SwapChain;

		DXRenderTarget *m_RenderTarget;
		
	protected:
		API::RenderTarget* getRenderTarget() override;
		void prepareFrame() override;
		void presentFrame() override;

	private:
		void windowCallback(const Event& event);
		void resize(const uint& width, const uint& height);

	public:
		DXContext();
		~DXContext();

		ZA_RESULT init() override;

		//getters
		static inline DXContext* GetContext(void)
		{
			return (DXContext*)s_Context;
		}
		static inline ID3D11Device* GetDevice(void)
		{
			return GetContext()->m_Dev;
		}
		static inline ID3D11DeviceContext* GetDevContext(void)
		{
			return GetContext()->m_Devcon;
		}
		static inline IDXGISwapChain* GetSwapChain(void)
		{
			return GetContext()->m_SwapChain;
		}

		//debug util
		static void ReportLiveObjects(void);
	};

}}}
#endif // ZAAP_INCLUDE_DIRECTX
