#pragma once

#include <Common.h>

#ifdef ZAAP_INCLUDE_DIRECTX

#include "graphics/Renderer3D.h"

#include "DXCommon.h"
#include "DXContext.h"

namespace zaap { namespace graphics { namespace DX {
	
	// <Class>
	//      DXRenderer3D
	//
	// <Description>
	//      This is a API class for DirectX. It uses Renderer3D as
	//      its base class. Use Renderer3D::CreateNewInstance to 
	//      create a new instance of this Renderer3D
	//      
	class ZAAP_API DXRenderer3D : public Renderer3D
	{
	private:
		// <Value>
		//      m_Dev
		//
		// <Note>
		//     This value is only a pointer to the m_Dev value from
		//     DXContext. So It's just set to null in the cleanup method.
		//
		ID3D11DeviceContext** m_Dev;

		// <Value>
		//      m_Devcon
		//
		// <Note>
		//     This value is only a pointer to the m_Devcon value from
		//     DXContext. So It's just set to null in the cleanup method.
		//
		ID3D11Device**        m_Devcon;

		// TODO add description
		ID3D11RasterizerState *m_RasterizerState;

		// <Value>
		//      m_DepthStencilState
		//
		// <Description>
		//      This holds the information if alpha testing is enabled or disabled.
		//      
		//      This value is an array to store the enabled and disabled state.
		//          0 = disabled
		//          1 = enabled
		//      
		ID3D11BlendState *m_BlendState[2];

		// <Value>
		//      m_DepthStencilState
		//
		// <Description>
		//      This holds the information if DepthTesting is enabled and
		//      if it's enabled how to deal with the stencil content.
		//      
		//      This value is an array to store the enabled and disabled state.
		//          0 = disabled
		//          1 = enabled
		//      
		ID3D11DepthStencilState *m_DepthStencilState[2];

		// <Value>
		//      m_DepthStencilView
		//
		// <Description>
		//      Holds the information about m_DepthStencil. 
		//
		ID3D11DepthStencilView *m_DepthStencilView;
	protected:
		DXRenderer3D();

		void cleanupAPIRenderer() override;
	public:
		void prepareFrame() const override;
		void presentFrame() const override;
		void setAlphaTestingState(bool enabled) const override;
		void setDepthTestingState(bool enable) const override;
	};
	
}}}

#endif // ZAAP_INCLUDE_DIRECTX
