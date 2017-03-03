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
		//		This is used by the deconstructor to decide if
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
	public:
		DXRenderTarget();
		DXRenderTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers = false);
		~DXRenderTarget();

		void setTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers = false);

		void bindTexture(uint index) override;
		void unbindTexture(uint index) override;
		
		void clearRenderTarget(const Color& color) override;
		void startTarget(void* depthStencil = nullptr) override;
	};

}}}

