#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Renderer.h>
#include <graphics/API/DXCommon.h>
#include <graphics/shader/DXShader/DXTextureShader.h>
#include <graphics/camera/Camera.h>
#include <graphics/shader/DXShader/DXMaterialShader.h>

namespace zaap { namespace graphics { namespace DX {

	class DXRenderer : public Renderer
	{
	private:
		//general DX objects
		ID3D11DeviceContext *m_Devcon;
		ID3D11Device *m_Dev;

		//Rendering
		ID3D11RenderTargetView *m_RenderTargetView;

		//Rasterstate
		ID3D11RasterizerState *m_RasterizerState;

		//BlendState
		ID3D11BlendState *m_BlendState;

		//DepthBffer
		ID3D11DepthStencilState *m_DepthStencilState;
		ID3D11Texture2D *m_DepthStencil;
		ID3D11DepthStencilView *m_DepthStencilView;

		DXMaterialShader *m_MaterialShader;
		DXTextureShader *m_TextureShader;

		Camera* m_Camera;
	protected:
		void init() override;

		//init  
		void initRasterizerState();
		void initBlendState();
		void initDepthBuffer();

		void resize(uint width, uint height) override;

		//setters / loaders
		void setCamera(Camera* camera) override;
		void setRenderTargets(ID3D11RenderTargetView *renderTargetView, ID3D11DepthStencilView *depthStencilView) const;
		void loadLight(Light* light) override;

		//render util
		void prepare() override;
		void render(Entity* entity) override;

		void cleanup() override;
	};

}}}
