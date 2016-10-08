#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/Shader.h>
#include <graphics/API/DXCommon.h>
#include <graphics/API/DXContext.h>


namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXShader
	{
	protected:
		ID3D11VertexShader *m_VShader;
		ID3D11PixelShader *m_PShader;
		ID3D11InputLayout *m_Layout;

		bool loadShaders(LPCTSTR vShaderFile, LPCTSTR pShaderFile, D3D11_INPUT_ELEMENT_DESC *ied, uint eCount, LPCTSTR vSMain = "VShader", LPCTSTR pSMain = "PShader");
		static bool CreateConstBuffer(ID3D11Buffer* &buffer, uint size, void* data);

		void startDXShader() const;
		void stopDXShader() const;

		void cleanDXShader();
	};

}}}
