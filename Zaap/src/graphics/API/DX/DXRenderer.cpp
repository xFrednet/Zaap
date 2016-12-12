#include "DXRenderer.h"

#include <graphics/API/DX/DXContext.h>
#include <graphics/API/VertexBuffer.h>
#include <util/Console.h>
#include <graphics/mesh/TexturedMesh.h>
#include <graphics/mesh/MaterialMesh.h>

namespace zaap { namespace graphics { namespace DX {

	Mat4 matrix_;
	void DXRenderer::init()
	{
		m_Devcon = DXContext::GetDevContext();
		m_Dev = DXContext::GetDevice();
		
		resize(Window::GetWidth(), Window::GetHeight());

		initRasterizerState();
		initBlendState();
		initDepthBuffer();
		
		m_Devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	//
	//init
	//
	void DXRenderer::initRasterizerState()
	{
		D3D11_RASTERIZER_DESC rDesc;
		ZeroMemory(&rDesc, sizeof(D3D11_RASTERIZER_DESC));

		//draw options
		rDesc.FillMode				= D3D11_FILL_WIREFRAME;
		rDesc.FillMode				= D3D11_FILL_SOLID;
		rDesc.CullMode				= D3D11_CULL_NONE;
		rDesc.FrontCounterClockwise = true;

		//DepthBias
		rDesc.DepthClipEnable		= false;

		//other options
		rDesc.ScissorEnable			= false;
		rDesc.MultisampleEnable		= false;
		rDesc.AntialiasedLineEnable = false;

		m_Dev->CreateRasterizerState(&rDesc, &m_RasterizerState);
		ZAAP_DXNAME(m_RasterizerState, "DXRenderer::m_RasterizerState");

		m_Devcon->RSSetState(m_RasterizerState);

	}
	void DXRenderer::initBlendState()
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
				ZAAP_ERROR("The BlendState[0] creation failed");
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
				ZAAP_ERROR("The BlendState[1] creation failed");
		}
		ZAAP_INFO("created the BlendStates");
	}
	void DXRenderer::initDepthBuffer()
	{
		HRESULT hr;

		//
		// DepthStencilState 0
		//
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc0;

			//Depth test
			dssDesc0.DepthEnable		= true;
			dssDesc0.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
			dssDesc0.DepthFunc		= D3D11_COMPARISON_LESS_EQUAL;
			
			//Stencil test
			dssDesc0.StencilEnable = true;
			dssDesc0.StencilReadMask = 0xFF;
			dssDesc0.StencilWriteMask = 0xFF;

			// Stencil operations if pixel is back-facing
			dssDesc0.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dssDesc0.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			dssDesc0.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;
			dssDesc0.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// Stencil operations if pixel is back-facing
			dssDesc0.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dssDesc0.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			dssDesc0.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			dssDesc0.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;

			//Depth stencil state creation
			hr = m_Dev->CreateDepthStencilState(&dssDesc0, &m_DepthStencilState[0]);
			ZAAP_DXNAME(m_DepthStencilState[0], "DXRenderer::m_DepthStencilState[0]");
			if (FAILED(hr))
				ZAAP_ERROR("Failed to create the DepthStencilState[0]");

			m_Devcon->OMSetDepthStencilState(m_DepthStencilState[0], 1);
		}

		//
		// DepthStencilState 1
		//
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc1;

			//Depth test
			dssDesc1.DepthEnable = false;
			dssDesc1.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			dssDesc1.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

			//Stencil test
			dssDesc1.StencilEnable = false;
			dssDesc1.StencilReadMask = 0xFF;
			dssDesc1.StencilWriteMask = 0xFF;

			// Stencil operations if pixel is back-facing
			dssDesc1.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dssDesc1.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			dssDesc1.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;
			dssDesc1.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// Stencil operations if pixel is back-facing
			dssDesc1.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dssDesc1.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			dssDesc1.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			dssDesc1.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;

			//Depth stencil state creation
			hr = m_Dev->CreateDepthStencilState(&dssDesc1, &m_DepthStencilState[1]);
			ZAAP_DXNAME(m_DepthStencilState[1], "DXRenderer::m_DepthStencilState[1]");
			if (FAILED(hr))
				ZAAP_ERROR("Failed to create the DepthStencilState[1]");

		}
	}

	void DXRenderer::resize(uint width, uint height)
	{
		//
		// update ProjectionMatrix
		//
		if (m_MaterialShader)m_MaterialShader->setProjectionMatrix(m_ProjectionMatrix);
		if (m_TextureShader)m_TextureShader->setProjectionMatrix(m_ProjectionMatrix);
		if (m_TerrainShader)m_TerrainShader->setProjectionMatrix(m_ProjectionMatrix);

		//
		// release all renderTargetViews
		//
		{
			m_Devcon->OMGetRenderTargets(0, nullptr, nullptr);
			ZAAP_DXRELEASE(m_RenderTargetView);
			ZAAP_DXRELEASE(m_DepthStencil);
			ZAAP_DXRELEASE(m_DepthStencilView);
		}
		
		//
		// resizing the BackBuffer and creating the RenderTargetView
		//
		HRESULT hr;
		{
			DXContext::GetSwapChain()->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
			
			ID3D11Texture2D *backBuffer;
			hr = DXContext::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
			if (FAILED(hr)) ZAAP_ERROR("Failed to get the BackBuffer from the SwapChain");

			hr = m_Dev->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView);
			if (FAILED(hr)) ZAAP_ERROR("Failed to create the RenderTargetView");

			ZAAP_DXNAME(m_RenderTargetView, "DXRenderer::m_RenderTargetView");
			ZAAP_DXRELEASE(backBuffer);
		}

		//
		//DepthBuffer
		//
		//DepthStencil
		D3D11_TEXTURE2D_DESC dsDesc;
		{
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

			hr = m_Dev->CreateTexture2D(&dsDesc, NULL, &m_DepthStencil); //NULL = no init data
			if (FAILED(hr)) ZAAP_ERROR("Failed to create the DepthStencil");

			hr = m_Dev->CreateDepthStencilView(m_DepthStencil, NULL, &m_DepthStencilView);
			if (FAILED(hr)) ZAAP_ERROR("Failed to create the DepthStencilView");

			ZAAP_DXNAME(m_DepthStencilView, "DXRenderer::DepthStencil");
			ZAAP_DXNAME(m_DepthStencilView, "DXRenderer::DepthStencilView")
		}

		//setRenderTargets
		setRenderTargets(m_RenderTargetView, m_DepthStencilView);

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

	}

	//
	// Setters / Loaders
	//
	void DXRenderer::setRenderTargets(ID3D11RenderTargetView* renderTargetView, ID3D11DepthStencilView* depthStencilView) const
	{
		m_Devcon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	}

	void DXRenderer::setDepthTestState(bool enable)
	{
		if (enable)
			m_Devcon->OMSetDepthStencilState(m_DepthStencilState[0], 1);
		else 
			m_Devcon->OMSetDepthStencilState(m_DepthStencilState[1], 1);
	}
	void DXRenderer::setAlphaChanelState(bool enable)
	{
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		uint sampleMask = 0xffffffff;
		
		if (enable)
			m_Devcon->OMSetBlendState(m_BlendState[1], blendFactor, sampleMask);
		else
			m_Devcon->OMSetBlendState(m_BlendState[0], blendFactor, sampleMask);
	}

	//
	// Render util
	//
	void DXRenderer::prepareFrame()
	{
		DXContext::SwapBuffers();

		m_Devcon->ClearRenderTargetView(m_RenderTargetView, D3DXCOLOR(1, 0, 1, 1));
		m_Devcon->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		m_MaterialShader->setCameraPosition(Vec3());

		//TODO improve Method 
	}

	void DXRenderer::render(const scene::Terrain const* terrain)
	{
		m_TerrainShader->start();

		m_TerrainShader->setTransformationMatrix(Mat4(1.0f));
	}

	void DXRenderer::cleanup()
	{
		m_Devcon = nullptr;
		m_Dev = nullptr;

		m_TextureShader->cleanup();
		m_MaterialShader->cleanup();
		m_TerrainShader->cleanup();

		delete m_TextureShader;
		delete m_MaterialShader;
		delete m_TerrainShader;

		//Rendering
		ZAAP_DXRELEASE(m_RenderTargetView);
		
		//Rasterizer
		ZAAP_DXRELEASE(m_RasterizerState);

		//BlendState
		ZAAP_DXRELEASE(m_BlendState[0]);
		ZAAP_DXRELEASE(m_BlendState[1]);

		//DepthBuffer
		ZAAP_DXRELEASE(m_DepthStencilState[0]);
		ZAAP_DXRELEASE(m_DepthStencilState[1]);
		ZAAP_DXRELEASE(m_DepthStencil);
		ZAAP_DXRELEASE(m_DepthStencilView);

		ZAAP_CLEANUP_INFO();
	}

}}}
