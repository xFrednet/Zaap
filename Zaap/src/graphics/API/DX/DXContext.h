#pragma once

#include <common.h>
#include <types.h>

#include <graphics/API/DX/DXCommon.h>
#include <app/Window.h>
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
		static DXContext* GetContext(void);
		static ID3D11Device* GetDevice(void);
		static ID3D11DeviceContext* GetDevContext(void);
		static IDXGISwapChain* GetSwapChain(void);

		//debug util
		static void ReportLiveObjects(void);
	};

}}}
