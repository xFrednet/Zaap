#include "DXRenderer.h"

#include <graphics/API/DXContext.h>
#include <graphics/API/VertexBuffer.h>
#include <maths/MathHelper.h>
#include <util/Console.h>
#include <graphics/mesh/TexturedMesh.h>

namespace zaap { namespace graphics { namespace DX {
	
	void DXRenderer::init()
	{
		m_Devcon = DXContext::GetDevContext();
		m_Dev = DXContext::GetDevice();
		
		resize(852, 480);

		initRasterizerState();
		initBlendState();
		initDepthBuffer();

		m_Devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_Shader.loadProjectionMatrix(math::CreateProjectionMatrix(0.1f, 1000.0f, 90.0f, 90.0f));
	}

	//
	//init
	//
	void DXRenderer::initRasterizerState()
	{
		D3D11_RASTERIZER_DESC rDesc;
		ZeroMemory(&rDesc, sizeof(D3D11_RASTERIZER_DESC));

		//draw options
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
		DXNAME(m_RasterizerState, "DXRenderer::m_RasterizerState");

		m_Devcon->RSSetState(m_RasterizerState);

	}
	void DXRenderer::initBlendState()
	{
		//desc
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.RenderTarget[0].BlendEnable			= false;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		//creation
		HRESULT hr = m_Dev->CreateBlendState(&blendDesc, &m_BlendState);
		DXNAME(m_BlendState, "DXRender::m_BlendState")
		if (FAILED(hr))
			ZAAP_ERROR("DXRenderer: The BlendState creation failed");
		
		float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		uint sampleMask = 0xffffffff;

		m_Devcon->OMSetBlendState(m_BlendState, blendFactor, sampleMask);

		ZAAP_INFO("DXRenderer: created the BlendState");
	}
	void DXRenderer::initDepthBuffer()
	{
		HRESULT hr;

		//
		// DepthStencilState
		//
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc;

			//Depth test
			dssDesc.DepthEnable		= true;
			dssDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
			dssDesc.DepthFunc		= D3D11_COMPARISON_LESS_EQUAL;
			
			//Stencil test
			dssDesc.StencilEnable = true;
			dssDesc.StencilReadMask = 0xFF;
			dssDesc.StencilWriteMask = 0xFF;

			// Stencil operations if pixel is back-facing
			dssDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dssDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			dssDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;
			dssDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// Stencil operations if pixel is back-facing
			dssDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dssDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			dssDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;

			//Depth stencil state creation
			hr = m_Dev->CreateDepthStencilState(&dssDesc, &m_DepthStencilState);
			DXNAME(m_DepthStencilState, "DXRenderer::m_DepthStencilState");
			if (FAILED(hr))
				ZAAP_ERROR("DXRenderer: Failed to xreate the DepthStencilState");

			m_Devcon->OMSetDepthStencilState(m_DepthStencilState, 1);
		}

	}

	void DXRenderer::resize(uint width, uint height)
	{
		//
		// release als renderRargetViews
		//
		{
			m_Devcon->OMGetRenderTargets(0, nullptr, nullptr);
			DXRELEASE(m_RenderTargetView);
			DXRELEASE(m_DepthStencil);
			DXRELEASE(m_DepthStencilView);
		}
		
		//
		// resizing the Backbuffer and creating the RenderTargetView
		//
		HRESULT hr;
		{
			DXContext::GetSwapChain()->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
			
			ID3D11Texture2D *backBuffer;
			hr = DXContext::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
			if (FAILED(hr)) ZAAP_ERROR("DXRenderer: Failed to get the Backbuffer from the SwapChain");

			hr = m_Dev->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView);
			if (FAILED(hr)) ZAAP_ERROR("DXRenderer: Failed to create the RenderTargetView");

			DXNAME(m_RenderTargetView, "DXRenderer::m_RenderTargetView");
			DXRELEASE(backBuffer);
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
			if (FAILED(hr)) ZAAP_ERROR("DXRenderer: Failed to create the DepthStencil");

			hr = m_Dev->CreateDepthStencilView(m_DepthStencil, NULL, &m_DepthStencilView);
			if (FAILED(hr)) ZAAP_ERROR("DXRenderer: Failed to create the DepthStencilView");

			DXNAME(m_DepthStencilView, "DXRenderer::DepthStencil");
			DXNAME(m_DepthStencilView, "DXRenderer::DepthStencilView")
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
	void DXRenderer::setCamera(Camera* camera)
	{
		m_Camera = camera;
	}
	void DXRenderer::setRenderTargets(ID3D11RenderTargetView* renderTargetView, ID3D11DepthStencilView* depthStencilView) const
	{
		m_Devcon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
		//m_Devcon->OMSetRenderTargets(1, &renderTargetView, NULL);
	}
	void DXRenderer::loadLight(Light* light)
	{
		m_Shader.loadLight(light);
	}

	//
	// Render util
	//
	void DXRenderer::prepare()
	{
		DXContext::SwapBuffers();

		m_Devcon->ClearRenderTargetView(m_RenderTargetView, D3DXCOLOR(1, 0, 1, 1));
		m_Devcon->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		m_Shader.loadViewMatrix(m_Camera->getViewMatrix());
		
		//TODO Change Method
	}
	math::Mat4 matrix_;
	void DXRenderer::render(Entity* entity)
	{
		//Texture
		TexturedMesh tMesh = *(TexturedMesh*)entity->getMesh();
		tMesh.getTexture()->bind(0);

		//Vertex Buffer
		tMesh.getVertexBuffer()->bind(0);

		//Matrix
		entity->getTransformationMatrix(matrix_);
		m_Shader.loadTransformationMatrix(matrix_);

		//rendering
		m_Devcon->DrawIndexed(tMesh.getVertexCount(), 0, 0);
	}

	void DXRenderer::cleanup()
	{
		m_Devcon = nullptr;
		m_Dev = nullptr;

		m_Shader.cleanup();

		//Rendering
		DXRELEASE(m_RenderTargetView);
		
		//Rasterizer
		DXRELEASE(m_RasterizerState);

		//BlendState
		DXRELEASE(m_BlendState);

		//DepthBuffer
		DXRELEASE(m_DepthStencilState);
		DXRELEASE(m_DepthStencil);
		DXRELEASE(m_DepthStencilView);

		ZAAP_CLEANUP_LOG("DXRenderer");
	}

}}}
