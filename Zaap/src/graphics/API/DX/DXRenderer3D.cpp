#include "DXRenderer3D.h"
#include "DXTexture2DCore.h"
#include "shader/DXDefaultShader.h"
#include "shader/DXTerrainShader.h"
#include <app/Window.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {
	
	DXRenderer3D::DXRenderer3D(ZA_RENDERER_TARGET_TYPE renderTargetType)
		: Renderer3D(renderTargetType)
	{
		m_Dev = DXContext::GetDevice();
		m_Devcon = DXContext::GetDevContext();

		m_DefaultShader = new DXDefaultShader();
		((DXDefaultShader*)m_DefaultShader)->init();
		m_TerrainShader = new DXTerrainShader();

		initRasterizerState();
		initBlendState();
		initDepthBuffer();

		renderTargetUpdated();

		m_Devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	DXRenderer3D::~DXRenderer3D()
	{
		//These values are created and therefore deleted by DXContest
		m_Dev = nullptr;
		m_Devcon = nullptr;

		ZA_DXRELEASE(m_RasterizerState);
		ZA_DXRELEASE(m_BlendState[0]);
		ZA_DXRELEASE(m_BlendState[1]);
		ZA_DXRELEASE(m_DepthStencilState[0]);
		ZA_DXRELEASE(m_DepthStencilState[1]);
		ZA_DXRELEASE(m_DepthStencilView);
	}

	void DXRenderer3D::renderTargetUpdated()
	{
		HRESULT hr;
		uint width = m_RenderTarget->getWidth();
		uint height = m_RenderTarget->getHeight();

		//Delete all old objects
		{
			m_Devcon->OMSetRenderTargets(0, nullptr, nullptr);

			//depth stencil
			if (m_DepthStencilView)
			{
				ZA_DXRELEASE(m_DepthStencilView);
			}
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
			ZA_DXNAME(depthStencil, "DXRenderer::DepthStencil");
			hr = m_Dev->CreateDepthStencilView(depthStencil, NULL, &m_DepthStencilView);
			//TODO add a error message for hr
			ZA_DXNAME(m_DepthStencilView, "DXRenderer::DepthStencilView");

			m_DepthStencil = new DXTexture2DCore(depthStencil);
		}
		
		updateProjectionMatrix();

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

		m_RenderTarget->startTarget(m_DepthStencilView);
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

		HRESULT hr = m_Dev->CreateRasterizerState(&rDesc, &m_RasterizerState);
		ZA_DXNAME(m_RasterizerState, "DXRenderer3D::m_RasterizerState");

		m_Devcon->RSSetState(m_RasterizerState);

		ZA_ASSERT(SUCCEEDED(hr));
		return (FAILED(hr)) ? ZA_ERROR_API_ERROR : ZA_OK;
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
			ZA_DXNAME(m_BlendState[0], "DXRender3D::m_BlendState[0]");

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
			ZA_DXNAME(m_BlendState[1], "DXRender3D::m_BlendState[1]");

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
			ZA_DXNAME(m_DepthStencilState[0], "DXRenderer3D::m_DepthStencilState[0]");

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
			ZA_DXNAME(m_DepthStencilState[1], "DXRenderer3D::m_DepthStencilState[1]");

			if (FAILED(hr))
				return ZA_ERROR_DIRECTX_DEPTH_STENCIL_STATE_CREATION_ERROR;
		}

		//enable depth testing
		m_Devcon->OMSetDepthStencilState(m_DepthStencilState[1], 1);

		return ZA_OK;
	}

	void DXRenderer3D::startRenderer() const
	{
		m_RenderTarget->startTarget(m_DepthStencilView);
		m_Devcon->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		

		m_Devcon->RSSetState(m_RasterizerState);
		setDepthTestingState(true);
		setAlphaTestingState(false);
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

}}}
