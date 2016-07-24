#include "DXShader.h"

#include "graphics/API/DXContext.h"
#include "util/Console.h"

namespace zaap { namespace graphics { namespace DX {

	bool DXShader::loadShaders(LPCTSTR vShaderFile, LPCTSTR pShaderFile, D3D11_INPUT_ELEMENT_DESC* ied, uint eCount, LPCTSTR vSMain, LPCTSTR pSMain)
	{
		ID3D10Blob *VS, *PS;
		ID3D10Blob *errorMessage = nullptr;
		HRESULT result;

		//Vertex shader
		result = D3DX11CompileFromFile(vShaderFile, 0, 0, vSMain, "vs_4_0", 0, 0, 0, &VS, &errorMessage, 0);
		if (FAILED(result))
		{
			ZAAP_ERROR("DXShader: Error Compiling the VertexShader: ");
			ZAAP_ERROR((char*)errorMessage->GetBufferPointer());
			return false;
		}

		//Pixel shader
		result = D3DX11CompileFromFile(pShaderFile, 0, 0, pSMain, "ps_4_0", 0, 0, 0, &PS, &errorMessage, 0);
		if (FAILED(result))
		{
			ZAAP_ERROR("DXShader: Error Compiling the PixelShader: ");
			ZAAP_ERROR((char*)errorMessage->GetBufferPointer());
			return false;
		}

		ID3D11Device *dev = DXContext::GetDevice();
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		//creation
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_VShader);
		DXNAME(m_VShader, "DXShader::m_VShader");
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_PShader);
		DXNAME(m_PShader, "DXShader::m_PShader");

		devcon->VSSetShader(m_VShader, 0, 0);
		devcon->PSSetShader(m_PShader, 0, 0);

		dev->CreateInputLayout(ied, eCount, VS->GetBufferPointer(), VS->GetBufferSize(), &m_Layout);
		if (m_Layout) 
			DXNAME(m_Layout, "DXShader::m_Layout")
		else 
			ZAAP_ERROR_(m_Layout, "DXShader: InputLayout creation failed");

		devcon->IASetInputLayout(m_Layout);

		//cleanup
		DXRELEASE(VS);
		DXRELEASE(PS);
		DXRELEASE(errorMessage);
		dev = nullptr;
		devcon = nullptr;

		return true;
	}

	void DXShader::start(void) const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		devcon->VSSetShader(m_VShader, 0, 0);
		devcon->PSSetShader(m_PShader, 0, 0);
		devcon->IASetInputLayout(m_Layout);
	}
	void DXShader::stop() const
	{
		// TODO add stop Method
	}

	void DXShader::cleanDXShader()
	{
		DXRELEASE(m_VShader);
		DXRELEASE(m_PShader);
		DXRELEASE(m_Layout);
	}

}}}
