#include "DXRenderTarget.h"

#include <graphics/Color.h>
#include <graphics/API/DX/DXContext.h>
#include <graphics/Bitmap.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {
	DXRenderTarget::DXRenderTarget()
		: RenderTarget(0, 0),
		m_AutoDeleteMembers(true),
		m_RenderTargetView(nullptr),
		m_Texture(nullptr),
		m_SamplerState(nullptr),
		m_TextureView(nullptr)
	{
	}
	DXRenderTarget::DXRenderTarget(ID3D11RenderTargetView* view, ID3D11Texture2D* texture, const uint& width, const uint& height, bool autoDeleteMembers)
		: RenderTarget(width, height),
		m_AutoDeleteMembers(autoDeleteMembers),
		m_RenderTargetView(view),
		m_Texture(texture),
		m_SamplerState(nullptr),
		m_TextureView(nullptr)
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
		m_SamplerState = nullptr;
		m_TextureView = nullptr;

		m_Width = width;
		m_Height = height;
		m_RenderTargetView = view;
		m_Texture = texture;

		informUpdateListeners();
	}

	void DXRenderTarget::setShaderResources(ID3D11ShaderResourceView* textureView, ID3D11SamplerState* samplerState)
	{
		if (textureView && samplerState)// both are a valid
		{
			m_TextureView = textureView;
			m_SamplerState = samplerState;
		} else if (!textureView && !samplerState) // both are null
		{
			m_TextureView = nullptr;
			m_SamplerState = nullptr;
		}
		// else no else it will do nothing if just one is null
	}

	ZA_RESULT DXRenderTarget::createTarget(const uint& width, const uint& height)
	{
		HRESULT hr;
		ID3D11Device *dev = DXContext::GetDevice();
		DXGI_FORMAT DXformat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ Texture creation ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ID3D11Texture2D* texture;
		{
			D3D11_TEXTURE2D_DESC texDesc;
			ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));

			texDesc.Width				= width;
			texDesc.Height				= height;
			texDesc.MipLevels			= 1;
			texDesc.ArraySize			= 1;
			texDesc.Format				= DXformat;
			texDesc.SampleDesc.Count	= 1;
			texDesc.Usage				= D3D11_USAGE_DEFAULT;
			texDesc.BindFlags			= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			texDesc.CPUAccessFlags		= 0;

			hr = dev->CreateTexture2D(&texDesc, nullptr, &texture);
			ZA_DXNAME(texture, "DXRenderTarget::texture");

			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_ERROR;
		}
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ RenderTargetView ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ID3D11RenderTargetView* renderTarget;
		{
			hr = dev->CreateRenderTargetView(texture, nullptr, &renderTarget);
			ZA_DXNAME(renderTarget, "DXRenderTarget::renderTarget");

			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_ERROR;
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ textureView ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ID3D11ShaderResourceView* textureView;
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tViewDesc;
			ZeroMemory(&tViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

			tViewDesc.Format				= DXformat;
			tViewDesc.ViewDimension			= D3D11_SRV_DIMENSION_TEXTURE2D;
			tViewDesc.Texture2D.MostDetailedMip = 0;
			tViewDesc.Texture2D.MipLevels	= -1;

			hr = dev->CreateShaderResourceView(texture, &tViewDesc, &textureView);
			ZA_DXNAME(textureView, "DXRenderTarget::textureView");

			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_ERROR;
		}
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ SamplerState ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ID3D11SamplerState* samperState;
		{
			D3D11_SAMPLER_DESC sDesc;
			ZeroMemory(&sDesc, sizeof(D3D11_SAMPLER_DESC));

			sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sDesc.MipLODBias = 0;
			sDesc.MaxAnisotropy = 1;
			sDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			sDesc.MinLOD = 0;
			sDesc.MaxLOD = D3D11_FLOAT32_MAX;

			hr = dev->CreateSamplerState(&sDesc, &samperState);
			ZA_DXNAME(samperState, "DXRenderTarget::samperState");

			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_ERROR;
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ assigning the Values ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if (m_AutoDeleteMembers)
		{
			ZA_DXRELEASE(m_Texture);
			ZA_DXRELEASE(m_RenderTargetView);
			ZA_DXRELEASE(m_TextureView);
			ZA_DXRELEASE(m_SamplerState);
		}

		m_Width				= width;
		m_Height			= height;
		m_Texture			= texture;
		m_RenderTargetView	= renderTarget;
		m_TextureView		= textureView;
		m_SamplerState		= samperState;
		m_AutoDeleteMembers = true;

		informUpdateListeners();

		return ZA_OK;
	}

	ZA_RESULT DXRenderTarget::resizeTarget(const uint& width, const uint& height)
	{
		return createTarget(width, height);
	}

	void DXRenderTarget::bindTexture(uint slot)
	{
		if (m_SamplerState && m_TextureView)
		{
			DXContext::GetDevContext()->PSSetShaderResources(slot, 1, &m_TextureView);
			DXContext::GetDevContext()->PSSetSamplers(slot, 1, &m_SamplerState);
		}
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
