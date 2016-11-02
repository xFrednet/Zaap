#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Renderer.h>
#include <graphics/camera/Camera.h>

namespace zaap { namespace graphics { namespace DX {

	class DXRenderer : public Renderer
	{
	private:
		//general DX objects
		ID3D11DeviceContext *m_Devcon;
		ID3D11Device *m_Dev;

		//Rendering
		ID3D11RenderTargetView *m_RenderTargetView;

		//RasterizerState
		ID3D11RasterizerState *m_RasterizerState; 

		//BlendState
		// 0 = enabled
		// 1 = disabled
		ID3D11BlendState *m_BlendState[2];

		//DepthBffer
		// 0 = enabled
		// 1 = disabled
		ID3D11DepthStencilState *m_DepthStencilState[2];
		ID3D11Texture2D *m_DepthStencil;
		ID3D11DepthStencilView *m_DepthStencilView;
	protected:
		void init() override;

		//init  
		void initRasterizerState();
		void initBlendState();
		void initDepthBuffer();

		void resize(uint width, uint height) override;

		//setters / loaders
		void setRenderTargets(ID3D11RenderTargetView *renderTargetView, ID3D11DepthStencilView *depthStencilView) const;

		//render options
		void setDepthTestState(bool enable) override;
		void setAlphaChanelState(bool enable) override;

		//render util
		void prepareFrame() override;
		void render(const scene::Terrain const *terrinTile) override;
		void render(Entity* entity) override;

		//util
		ViewFrustum getViewFrustum() override;

		void cleanup() override;
	};

}}}
