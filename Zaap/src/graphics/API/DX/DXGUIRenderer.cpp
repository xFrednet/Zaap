#include "DXGUIRenderer.h"

#include <graphics/API/DX/shader/DXGUIShader.h>
#include <util/Log.h>
#include <graphics/API/DX/DXContext.h>


namespace zaap { namespace graphics { namespace DX {
	ZA_RESULT DXGUIRenderer::init()
	{
		ZA_MULTI_RESULT zmr;
		m_Dev = DXContext::GetDevice();
		m_Devcon = DXContext::GetDevContext();

		m_GUIShader = new DXGUIShader();
		zmr = m_GUIShader->init();
		ZA_ASSERT(ZA_SUCCEDED(zmr));
		m_GUIShader->setTargetSize(m_TargetWidth, m_TargetHeight);

		zmr += initDXObjects();
		ZA_ASSERT(ZA_SUCCEDED(zmr));

		m_Devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return (ZA_SUCCEDED(zmr)) ? ZA_OK : ZA_ERROR_DIRECTX_ERROR;
	}

	ZA_RESULT DXGUIRenderer::initDXObjects()
	{
		HRESULT hr;

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ Rasterizer state ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		{
			D3D11_RASTERIZER_DESC rDesc;
			ZeroMemory(&rDesc, sizeof(D3D11_RASTERIZER_DESC));

			//draw options
			rDesc.FillMode = D3D11_FILL_SOLID;
			rDesc.CullMode = D3D11_CULL_NONE;
			rDesc.FrontCounterClockwise = true;

			hr = m_Dev->CreateRasterizerState(&rDesc, &m_RasterizerState);
			ZA_DXNAME(m_RasterizerState, "DXGUIRenderer::m_RasterizerState");

			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_API_ERROR;
		}
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ Rasterizer state ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		{
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

			//option
			blendDesc.RenderTarget[0].BlendEnable = false;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			//creation
			hr = m_Dev->CreateBlendState(&blendDesc, &m_BlendState);
			ZA_DXNAME(m_BlendState, "DXGUIRender::m_BlendState");

			//error check
			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR;
		}
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ~ Depth stencil state ~
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc0;
			ZeroMemory(&dssDesc0, sizeof(D3D11_DEPTH_STENCIL_DESC));

			hr = m_Dev->CreateDepthStencilState(&dssDesc0, &m_DepthStencilState);
			ZA_DXNAME(m_DepthStencilState, "DXGUIRenderer3D::m_DepthStencilState");

			ZA_ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_DEPTH_STENCIL_STATE_CREATION_ERROR;
		}

		return ZA_OK;
	}

	DXGUIRenderer::DXGUIRenderer()
		: m_RasterizerState(nullptr),
		m_BlendState(nullptr),
		m_DepthStencilState(nullptr)
	{


	}

	DXGUIRenderer::~DXGUIRenderer()
	{
		m_Dev = nullptr;
		m_Devcon = nullptr;

		ZA_DXRELEASE(m_BlendState);
		ZA_DXRELEASE(m_DepthStencilState);
	}

	void DXGUIRenderer::startRenderer()
	{
		GUIRenderer::startRenderer();

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		m_Devcon->OMSetDepthStencilState(m_DepthStencilState, 1);
		m_Devcon->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
		m_Devcon->RSSetState(m_RasterizerState);
	}
}}}
