#pragma once

#include <Common.h>

#include <graphics/GUIRenderer.h>

#include <graphics/API/DX/DXCommon.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXGUIRenderer : public GUIRenderer
	{
	protected:
		// <Value>
		//      m_Dev
		//
		// <Note>
		//      This value is only a pointer to the m_Dev value from
		//      DXContext. So It's just set to null in the cleanup method.
		//
		ID3D11Device* m_Dev;

		// <Value>
		//      m_Devcon
		//
		// <Note>
		//      This value is only a pointer to the m_Devcon value from
		//      DXContext. So It's just set to null in the cleanup method.
		//
		ID3D11DeviceContext* m_Devcon;

		ID3D11RasterizerState* m_RasterizerState;
		ID3D11BlendState* m_BlendState;
		ID3D11DepthStencilState* m_DepthStencilState;

		ZA_RESULT init() override;

	private:
		ZA_RESULT initDXObjects();
	public:
		DXGUIRenderer();

		~DXGUIRenderer() override;

		void startRenderer() override;
	public:
	};

}}}
