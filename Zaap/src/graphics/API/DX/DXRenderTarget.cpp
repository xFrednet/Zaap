#include "DXRenderTarget.h"

#include <graphics/Color.h>
#include <graphics/API/DX/DXContext.h>

namespace zaap { namespace graphics { namespace DX {
	DXRenderTarget::DXRenderTarget()
		: RenderTarget(0, 0),
		m_AutoDeleteMembers(true),
		m_RenderTargetView(nullptr),
		m_Texture(nullptr)
	{
	}
	DXRenderTarget::DXRenderTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers)
		: RenderTarget(width, height),
		m_AutoDeleteMembers(autoDeleteMembers),
		m_RenderTargetView(view),
		m_Texture(texture)
	{
	}

	DXRenderTarget::~DXRenderTarget()
	{
		if (!m_AutoDeleteMembers)
		{
			ZA_DXRELEASE(m_RenderTargetView);
			ZA_DXRELEASE(m_Texture);
		}
	}

	void DXRenderTarget::setTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers)
	{
		if (!m_AutoDeleteMembers)
		{
			ZA_DXRELEASE(m_RenderTargetView);
			ZA_DXRELEASE(m_Texture);
		}
		m_AutoDeleteMembers = autoDeleteMembers;

		m_Width = width;
		m_Height = height;
		m_RenderTargetView = view;
		m_Texture = texture;

		informUpdateListeners();
	}

	void DXRenderTarget::bindTexture(uint slot)
	{
		//TODO bind and unbind
		//DXContext::GetDevContext()->PSSetShaderResources(slot, 1, &m_TextureView);
		//DXContext::GetDevContext()->PSSetSamplers(slot, 1, &m_SamplerState);
	}

	void DXRenderTarget::unbindTexture(uint index)
	{
	}

	void DXRenderTarget::clearRenderTarget(const Color& color)
	{
		DXContext::GetDevContext()->ClearRenderTargetView(m_RenderTargetView, color.getDXColor());
	}

	void DXRenderTarget::startTarget(void* depthStencil)
	{
		DXContext::GetDevContext()->OMSetRenderTargets(1, &m_RenderTargetView, (ID3D11DepthStencilView*)depthStencil);
	}

}}}
