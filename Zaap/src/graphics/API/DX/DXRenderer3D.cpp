﻿#include "DXRenderer3D.h"
#include "DXTexture2D.h"
#include "shader/types/DXTextureShader.h"
#include "shader/types/DXTerrainShader.h"
#include "shader/types/DXMaterialShader.h"
#include "shader/types/DXFontShader2D.h"

namespace zaap { namespace graphics { namespace DX {
	
	DXRenderer3D::DXRenderer3D()
	{
		m_Dev = DXContext::GetDevice();
		m_Devcon = DXContext::GetDevContext();

		m_TextureShader = new DXTextureShader();
		m_MaterialShader = new DXMaterialShader();
		m_TerrainShader = new DXTerrainShader();
		m_FontShader2D = new DXFontShader2D();

		resize(Window::GetWidth(), Window::GetHeight());

		initRasterizerState();
		initBlendState();
		initDepthBuffer();

		m_Devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	//
	// Init methods
	// 
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

			//options
			blendDesc0.RenderTarget[0].BlendEnable = true;
			blendDesc0.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc0.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc0.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc0.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc0.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc0.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc0.RenderTarget[0].RenderTargetWriteMask = 0x0f;

			//creation
			hr = m_Dev->CreateBlendState(&blendDesc0, &m_BlendState[0]);
			ZAAP_DXNAME(m_BlendState[0], "DXRender3D::m_BlendState[0]");

			//error check
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR;
		}
		//
		// BlendState[1]
		//
		{
			D3D11_BLEND_DESC blendDesc1;
			ZeroMemory(&blendDesc1, sizeof(D3D11_BLEND_DESC));

			//option
			blendDesc1.RenderTarget[0].BlendEnable = false;
			blendDesc1.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			//creation
			hr = m_Dev->CreateBlendState(&blendDesc1, &m_BlendState[1]);
			ZAAP_DXNAME(m_BlendState[1], "DXRender3D::m_BlendState[1]");

			//error check
			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_BLENDSTATE_CREATION_ERROR;
		}
		return ZA_OK;
	}
	ZA_RESULT DXRenderer3D::initDepthBuffer()
	{
		HRESULT hr;
		
		// DepthSTencilState 0
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc0;
			ZeroMemory(&dssDesc0, sizeof(D3D11_DEPTH_STENCIL_DESC));

			//Depth test
			dssDesc0.DepthEnable = false;

			//Stencil test
			dssDesc0.StencilEnable = false;
			
			hr = m_Dev->CreateDepthStencilState(&dssDesc0, &m_DepthStencilState[0]);
			ZAAP_DXNAME(m_DepthStencilState[0], "DXRenderer3D::m_DepthStencilState[0]");

			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_DEPTH_STENCIL_STATE_CREATION_ERROR;
		}

		// DepthStencilState 1
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc1;

			//Depth test
			dssDesc1.DepthEnable		= true;
			dssDesc1.DepthWriteMask		= D3D11_DEPTH_WRITE_MASK_ALL;
			dssDesc1.DepthEnable		= D3D11_COMPARISON_LESS_EQUAL;

			//Stencil test
			dssDesc1.StencilEnable		= true;
			dssDesc1.StencilReadMask	= 0xff;
			dssDesc1.StencilWriteMask	= 0xff;

			// Stencil operations if pixel is back facing
			dssDesc1.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
			dssDesc1.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_INCR;
			dssDesc1.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_INCR_SAT;
			dssDesc1.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;

			// Stencil operations if pixel is back-facing
			dssDesc1.BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
			dssDesc1.BackFace.StencilDepthFailOp	= D3D11_STENCIL_OP_DECR;
			dssDesc1.BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
			dssDesc1.BackFace.StencilFunc			= D3D11_COMPARISON_NEVER;

			//creation
			hr = m_Dev->CreateDepthStencilState(&dssDesc1, &m_DepthStencilState[1]);
			ZAAP_DXNAME(m_DepthStencilState[1], "DXRenderer3D::m_DepthStencilState[1]");

			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_DEPTH_STENCIL_STATE_CREATION_ERROR;
		}

		//enable depth testing
		m_Devcon->OMSetDepthStencilState(m_DepthStencilState[1], 1);

		return ZA_OK;
	}

	void DXRenderer3D::setCustomRenderTarget(API::Texture2D* target, uint width, uint height)
	{
		if (!target)
		{
			m_HasCustomRenderTarget = false;
			resize(Window::GetWidth(), Window::GetHeight());
			return;
		}
		//else the texture is a custom render target
		
		m_HasCustomRenderTarget = true;
		m_RenderTarget = target;

		updateProjectionMatrix();
		
		//
		// View port
		//
		D3D11_VIEWPORT viewport;
		{
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = (float)target->getWidth();
			viewport.Height = (float)target->getHeight();
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			m_Devcon->RSSetViewports(1, &viewport);
		}

	}
	void DXRenderer3D::resize(uint width, uint height)
	{
		if (m_HasCustomRenderTarget) return;

		HRESULT hr;
		m_Width = width;
		m_Height = height;
		updateProjectionMatrix();

		//Delete all old objects
		{
			m_Devcon->OMSetRenderTargets(0, nullptr, nullptr);
		
			//render target
			if (m_RenderTarget)
			{
				ZAAP_DXRELEASE(m_RenderTargetView);
				m_RenderTarget->cleanup();
				delete m_RenderTarget;
			}

			//depth stencil
			if (m_DepthStencilView)
			{
				ZAAP_DXRELEASE(m_DepthStencilView);
				m_DepthStencil->cleanup();
				delete m_DepthStencil;
			}
		}

		//resizing the buffers
		{
			DXContext::GetSwapChain()->ResizeBuffers(0, m_Width, m_Height, DXGI_FORMAT_UNKNOWN, 0);

			ID3D11Texture2D* backbuffer;
			hr = DXContext::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer);
			//TODO add a error message for hr
			ZAAP_DXNAME(backbuffer, "DXRenderer3D::m_BackBuffer");

			ZAAP_DXNAME(m_RenderTargetView, "DXRenderer3D::m_RenderTargetView");
			hr = m_Dev->CreateRenderTargetView(backbuffer, nullptr, &m_RenderTargetView);
			//TODO add a error message for hr

			m_RenderTarget = new DXTexture2D(backbuffer);
		}

		//
		//DepthBuffer
		//
		D3D11_TEXTURE2D_DESC dsDesc;
		{
			ID3D11Texture2D* depthStencil;
			
			dsDesc.Width = width;
			dsDesc.Height = height;
			dsDesc.MipLevels = 1;
			dsDesc.ArraySize = 1;
			dsDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			dsDesc.SampleDesc.Count = 1;
			dsDesc.SampleDesc.Quality = 0;
			dsDesc.Usage = D3D11_USAGE_DEFAULT;
			dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			dsDesc.CPUAccessFlags = 0;
			dsDesc.MiscFlags = 0;

			hr = m_Dev->CreateTexture2D(&dsDesc, NULL, &depthStencil); //NULL = no init data
			//TODO add a error message for hr
			ZAAP_DXNAME(depthStencil, "DXRenderer::DepthStencil");
			hr = m_Dev->CreateDepthStencilView(depthStencil, NULL, &m_DepthStencilView);
			//TODO add a error message for hr
			ZAAP_DXNAME(m_DepthStencilView, "DXRenderer::DepthStencilView");

			m_DepthStencil = new DXTexture2D(depthStencil);
		}
		
		//
		// View port
		//
		D3D11_VIEWPORT viewport;
		{
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = (float)width;
			viewport.Height = (float)height;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			m_Devcon->RSSetViewports(1, &viewport);
		}

		m_Devcon->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	}
	void DXRenderer3D::prepareFrame() const
	{
		m_Devcon->ClearRenderTargetView(m_RenderTargetView, D3DXCOLOR(1, 0, 1, 1));
		m_Devcon->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DXRenderer3D::presentFrame() const
	{
		DXContext::SwapBuffers();
	}

	void DXRenderer3D::setAlphaTestingState(bool enabled) const
	{
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		uint sampleMask = 0xffffffff;

		if (enabled)
			m_Devcon->OMSetBlendState(m_BlendState[0], blendFactor, sampleMask);
		else
			m_Devcon->OMSetBlendState(m_BlendState[1], blendFactor, sampleMask);
	}

	void DXRenderer3D::setDepthTestingState(bool enable) const
	{
		if (enable)
			m_Devcon->OMSetDepthStencilState(m_DepthStencilState[1], 1);
		else
			m_Devcon->OMSetDepthStencilState(m_DepthStencilState[0], 1);
	}


	void DXRenderer3D::cleanupAPIRenderer()
	{
		//These values are created and therefore deleted by DXContest
		m_Dev = nullptr;
		m_Devcon = nullptr;
	}

}}}
