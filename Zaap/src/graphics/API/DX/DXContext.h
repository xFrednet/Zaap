#pragma once

#include <Common.h>

#ifdef ZAAP_INCLUDE_DIRECTX

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/Context.h>

namespace zaap { namespace graphics	{ namespace DX {
			
	class ZAAP_API DXContext : public API::Context
	{
	protected:
		ID3D11Device *m_Dev;
		ID3D11DeviceContext *m_Devcon;
		
		IDXGISwapChain *m_SwapChain;
	protected:
		void cleanup(void) override;

		//Buffer stuff
		void swapBuffers(void) override;

	public:
		DXContext();

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
