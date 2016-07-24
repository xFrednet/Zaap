#pragma once

#include "graphics/API/DXCommon.h"
#include "app/Window.h"
#include "graphics/DX/DXLoader.h"
#include "graphics/API/Context.h"
#include "Common.h"

namespace zaap { namespace graphics	{ namespace DX {
			
	class ZAAP_API DXContext : public API::Context
	{
	protected:
		ID3D11Device *m_Dev;
		ID3D11DeviceContext *m_Devcon;
		
		IDXGISwapChain *m_SwapChain;

		ID3D11RasterizerState *m_RasterState;

		DXLoader m_Loader;
	protected:
		void cleanup(void) override;
		Loader* getLoader() override;

		//Buffer stuff
		void swapBuffers(void) override;
		
		//util
		void resize(uint width, uint height) override;

	public:
		DXContext(Window &window);

		//getters
		static DXContext* GetContext(void);
		static ID3D11Device* GetDevice(void);
		static ID3D11DeviceContext* GetDevContext(void);
		static IDXGISwapChain* GetSwapChain(void);
		static Loader* GetLoader(void);

		//debug util
		static void ReportLiveObjects(void);
	};

}}}
