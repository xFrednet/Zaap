#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/Shader.h>
#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/DX/DXContext.h>


namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXShader
	{
	private:
		ID3D10Blob* compileShader(String &shaderSrc, String version, String &methodName);
	protected:
		ID3D11VertexShader *m_VShader;
		ID3D11PixelShader *m_PShader;
		ID3D11InputLayout *m_Layout;

		bool createShaderFromFile(String shaderFile, D3D11_INPUT_ELEMENT_DESC *ied, uint eCount, String vSMain = "VShader", String pSMain = "PShader");
		bool createShaderFromString(String shaderSrc, D3D11_INPUT_ELEMENT_DESC *ied, uint eCount, String vSMain = "VShader", String pSMain = "PShader");
		
		static bool CreateConstBuffer(ID3D11Buffer* &buffer, uint size, void* data);

		void startDXShader() const;
		void stopDXShader() const;

		void cleanDXShader();
	};

}}}

/*void D3DShader::Load(const String& source)
	{
		m_Data.vs = Compile(source, "vs_4_0", "VSMain");
		SP_ASSERT(m_Data.vs);
		m_Data.ps = Compile(source, "ps_4_0", "PSMain");
		SP_ASSERT(m_Data.ps);
		D3DContext::GetDevice()->CreateVertexShader(m_Data.vs->GetBufferPointer(), m_Data.vs->GetBufferSize(), NULL, &m_Data.vertexShader);
		D3DContext::GetDevice()->CreatePixelShader(m_Data.ps->GetBufferPointer(), m_Data.ps->GetBufferSize(), NULL, &m_Data.pixelShader);

		//m_Data.vs = Compile(source, "vs_4_0", "VSMain");
		//D3DShader::Compile(const String& source, const String& profile, const String& main)
		//D3DCompile(source.c_str(), source.size(), NULL, NULL, NULL, main.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
	}

	ID3DBlob* D3DShader::Compile(const String& source, const String& profile, const String& main)
	{
		ID3DBlob* shaderBlob;
		ID3DBlob* errorBlob;
		HRESULT status = D3DCompile(source.c_str(), source.size(), NULL, NULL, NULL, main.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
		if (status != S_OK)
			std::cout << "Unable to compile shader from source" << std::endl;
		if (errorBlob)
		{
			std::cout << "Shader Compilation Error: " << profile << std::endl;
			if (errorBlob->GetBufferSize())
				std::cout << "Shader Compile Errors" << std::endl << (const char*)errorBlob->GetBufferPointer() << std::endl;
			errorBlob->Release();
		}
		if (status == S_OK)
			return shaderBlob;
		return NULL;
		}*/