#pragma once

#include "graphics/Renderer.h"
#include "graphics/API/DXCommon.h"
#include "graphics/shader/DXShader/DXStaticShader.h"
#include "graphics/Model.h"
#include "graphics/camera/Camera.h"
#include "Common.h"

namespace zaap { namespace graphics { namespace DX {

	class DXRenderer : public Renderer
	{
	private:
		//general DX objects
		ID3D11DeviceContext *m_Devcon;
		ID3D11Device *m_Dev;

		//Rendering
		ID3D11RenderTargetView *m_RenderTargetView;

		//BlendState
		ID3D11BlendState *m_BlendState;

		//DepthBffer
		ID3D11DepthStencilState *m_DepthStencilState;
		ID3D11Texture2D *m_DepthStencil;
		ID3D11DepthStencilView *m_DepthStencilView;

		DXStaticShader m_Shader;

		Camera* m_Camera;
	protected:
		void init() override;

		//setup  
		void setupBlendState();
		void setupDepthBuffer();

		void resize(uint width, uint height) override;

		void setCamera(Camera* camera) override;
		void setRenderTargets(ID3D11RenderTargetView *renderTargetView, ID3D11DepthStencilView *depthStencilView) const;

		void prepare() override;
		void render(Model* model) override;

		void cleanup() override;
	};

}}}