#pragma once

#include <graphics/API/RenderTarget.h>

#include "DXCommon.h"

namespace zaap { namespace graphics { namespace DX {
	class DXContext;

	class ZAAP_API DXRenderTarget : public API::RenderTarget
	{
	private:
		friend DXContext;

		// <Value>
		//		m_AutoDeleteMembers
		//
		// <Descritpion>
		//		This is used by the destructor to decide if
		//		the members should be deleted by this or a different
		//		source.
		//
		bool m_AutoDeleteMembers;
		
		// <Value>
		//      m_RenderTargetView
		// 
		// <Description>
		//		This is the link between the render target texture
		//		and direct X.
		//
		ID3D11RenderTargetView* m_RenderTargetView;

		// <Value>
		//		m_Texture
		//
		// <Descritpion>
		//		This is the actual texture object of the @RenderTarget
		//
		ID3D11Texture2D* m_Texture;
		
		// <Value>
		//		m_SamplerState
		//
		// <Description>
		//		This is the sampler of the texture. It also indicates if
		//		the Texture can be bound as a shader resource.
		//
		ID3D11SamplerState* m_SamplerState;
		// <Value>
		//		m_TextureView
		//
		// <Description>
		//		This is the resource view of the texture. It also indicates if
		//		the Texture can be bound as a shader resource.
		ID3D11ShaderResourceView* m_TextureView;
	public:
		DXRenderTarget();
		DXRenderTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers = false);
		~DXRenderTarget();

		void setTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers = false);
		void setShaderResources(ID3D11ShaderResourceView* textureView, ID3D11SamplerState* samplerState);

		ZA_RESULT createTarget(const uint& width, const uint& height) override; //TODO add a sample count option
		ZA_RESULT resizeTarget(const uint& width, const uint& height) override;

		void bindTexture(uint index) override;
		void unbindTexture(uint index) override;
		
		void clearRenderTarget(const Color& color) override;
		void startTarget(void* depthStencil = nullptr) override;
	};

}}}

