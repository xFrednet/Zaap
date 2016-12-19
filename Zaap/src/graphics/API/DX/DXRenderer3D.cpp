#include "DXRenderer3D.h"

namespace zaap { namespace graphics { namespace DX {
	DXRenderer3D::DXRenderer3D()
	{
		m_Dev = DXContext::GetDevice();
		m_Devcon = DXContext::GetDevContext();

		resize(Window::GetWidth(), Window::GetHeight());

	}

	ZA_RESULT DXRenderer3D::initRasterizerState()
	{
		D3D11_RASTERIZER_DESC rDesc;
		ZeroMemory(&rDesc, sizeof(D3D11_RASTERIZER_DESC));

		//draw options
		rDesc.FillMode = D3D11_FILL_WIREFRAME;
		rDesc.FillMode = D3D11_FILL_SOLID;
		rDesc.CullMode = D3D11_CULL_NONE;
		rDesc.FrontCounterClockwise = true;

		//DepthBias
		rDesc.DepthClipEnable = false;

		//other options
		rDesc.ScissorEnable = false;
		rDesc.MultisampleEnable = false;
		rDesc.AntialiasedLineEnable = false;

		m_Dev->CreateRasterizerState(&rDesc, &m_RasterizerState);
		ZAAP_DXNAME(m_RasterizerState, "DXRenderer3D::m_RasterizerState");

		m_Devcon->RSSetState(m_RasterizerState);

		return ZA_OK;
	}

	ZA_RESULT DXRenderer3D::initBlendState()
	{
		HRESULT hr;
		//
		// BlendState[0]
		//
		{
			D3D11_BLEND_DESC blendDesc0;
			ZeroMemory(&blendDesc0, sizeof(D3D11_BLEND_DESC));
			blendDesc0.RenderTarget[0].BlendEnable = false;
			blendDesc0.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			hr = m_Dev->CreateBlendState(&blendDesc0, &m_BlendState[0]);
			ZAAP_DXNAME(m_BlendState[0], "DXRender::m_BlendState[0]");

			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR;
		}
		{
			D3D11_BLEND_DESC blendDesc1;
			ZeroMemory(&blendDesc1, sizeof(D3D11_BLEND_DESC));

			blendDesc1.RenderTarget[0].BlendEnable = true;
			blendDesc1.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc1.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc1.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc1.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc1.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc1.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc1.RenderTarget[0].RenderTargetWriteMask = 0x0f;

			//creation
			hr = m_Dev->CreateBlendState(&blendDesc1, &m_BlendState[1]);
			ZAAP_DXNAME(m_BlendState[1], "DXRender::m_BlendState[1]");

			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR;
		}
		return ZA_OK;
	}

	ZA_RESULT DXRenderer3D::initDepthBuffer()
	{
	}

	void DXRenderer3D::prepareFrame() const
	{
	}

	void DXRenderer3D::presentFrame() const
	{
	}

	void DXRenderer3D::setAlphaTestingState(bool enabled) const
	{
	}

	void DXRenderer3D::setDepthTestingState(bool enable) const
	{
	}

	void DXRenderer3D::resize(uint width, uint height)
	{
	}

	void DXRenderer3D::cleanupAPIRenderer()
	{
		//These values are created and therefore deleted by DXContest
		m_Dev = nullptr;
		m_Devcon = nullptr;
	}
}}}
