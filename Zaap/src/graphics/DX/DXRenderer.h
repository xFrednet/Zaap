#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Renderer.h>
#include <graphics/API/DXCommon.h>
#include <graphics/camera/Camera.h>
#include <graphics/shader/materialShader/MaterialShader.h>
#include <graphics/shader/textureShader/TextureShader.h>
#include <graphics/shader/terrainShader/TerrainShader.h>

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
		ID3D11BlendState *m_BlendState;

		//DepthBffer
		ID3D11DepthStencilState *m_DepthStencilState;
		ID3D11Texture2D *m_DepthStencil;
		ID3D11DepthStencilView *m_DepthStencilView;

		Camera* m_Camera;
	protected:
		void init() override;

		//init  
		void initRasterizerState();
		void initBlendState();
		void initDepthBuffer();

		void resize(uint width, uint height) override;

		//Camera
		void setCamera(Camera* camera) override;
		Camera* getCamera() override;

		//setters / loaders
		void setRenderTargets(ID3D11RenderTargetView *renderTargetView, ID3D11DepthStencilView *depthStencilView) const;
		void loadLightSetup(LightSetup* lightSetup) override;

		//render util
		void prepare() override;
		void render(const scene::Terrain const *terrinTile) override;
		void render(Entity* entity) override;

		//util
		ViewFrustum getViewFrustum() override;

		void cleanup() override;
	};

}}}
