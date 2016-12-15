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
		//Constructor to init values
		DXRenderer3D();

		// <Function>
		//      cleanupAPIRenderer (overridden from Renderer3D)
		//
		// <Description>
		//      This method releases all the Direct X objects 
		//      that are inside this class.
		//
		// <Note>
		//      This is called by the cleanup method in Renderer3D. 
		//
		void cleanupAPIRenderer() override;
	public:
		// <Function>
		//      prepareFrame (overridden from Renderer3D)
		//
		// <Description>
		//      "This method should be called at the start of every Frame.
		//      It prepares the Frame in some different ways, just call it
		//      for the greater good of the engine." (From Renderer3D)
		//      
		//      It clears the DepthStencil and the current frame.
		//      
		void prepareFrame() const override;
		
		// <Function>
		//      prepareFrame (overridden from Renderer3D)
		//
		// <Description>
		//      "This method should be called at the end of every Frame.
		//      It presents the Frame by swapping the BackBuffer." (From Renderer3D)
		//      
		//      This method swaps the current buffer with the BackBuffer.
		//
		void presentFrame() const override;

		// <Function>
		//      setAlphaTestingState (overridden from Renderer3D)
		//
		// <Description>
		//      "This method disables/enables alpha testing.
		//      This can be used to disable the alpha channel for 
		//      objects that should be rendered without that. It should
		//      also improve the performance. 
		//      => Enable if you want/need a alpha value disable it 
		//         otherwise to improve performance." (From Renderer3D)
		//      
		//      It swaps the m_BlendState to disable / enable alpha testing.
		//      
		// <Input>
		//      enable      : indicates the new state 
		//                        true = enabled
		//                        false = disabled
		//
		void setAlphaTestingState(bool enabled) const override;
		
		// <Function>
		//      setDepthTestingState (overridden from Renderer3D)
		//
		// <Description>
		//      "This method disables/enables depth testing. 
		//      This maybe useful for the GUI and other components
		//      because they are always rendered in front this could
		//      save some extra test. It's also useful to control which
		//      models are rendered to the DepthStencil." (From Renderer3D)
		//      
		//      It swaps the m_DepthStencilState to disable / enable depth testing.
		//      
		// <Input>
		//      enable      : indicates the new state 
		//                        true = enabled
		//                        false = disabled
		//
		void setDepthTestingState(bool enable) const override;

		// <Function>
		//      resize (overridden from Renderer3D)
		//
		// <Description>
		//      This method configures the RenderTarget size and
		//      the DepthStencil.
		//      
		// <Input>
		//      width   : the new width
		//      height  : the new height
		//      
		// <Note>
		//      This method will be changed to add extra resize options 
		//      or to enable the user to set a target frame part
		//      
		void resize(uint width, uint height) override;
	};
	
}}}

#endif // ZAAP_INCLUDE_DIRECTX
