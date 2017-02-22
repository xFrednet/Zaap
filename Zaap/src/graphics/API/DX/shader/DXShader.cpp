#include "DXShader.h"

#include <graphics/API/DX/DXContext.h>
#include <util/Log.h>
#include <util/Loader.h>
#include <util/StringUtil.h>

namespace zaap { namespace graphics { namespace DX {
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Static Util //
	/* //////////////////////////////////////////////////////////////////////////////// */

	ID3D10Blob* DXShader::CompileShader(String shaderSrc, const String& version, const String& methodName)
	{
		ID3D10Blob *shaderBlob;
		ID3D10Blob *errorBlob;
		
		shaderSrc = StringUtil::Replace(shaderSrc, "ZA_SHADER_LIGHT_COUNT", std::to_string(ZA_SHADER_LIGHT_COUNT));
		shaderSrc = StringUtil::Replace(shaderSrc, "ZA_SHADER_MATERIAL_COUNT", std::to_string(ZA_SHADER_MATERIAL_COUNT));

		HRESULT result = D3DCompile(shaderSrc.c_str(), shaderSrc.size(), NULL, NULL, NULL, methodName.c_str(), version.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
		if (result == S_OK)
			return shaderBlob;
		else
		{
			ZA_ERROR("compileShader: Unable to compile shader from source");
			if (errorBlob)
			{
				ZA_ERROR("compileShader: targeted version: " + version);

				if (errorBlob->GetBufferSize())
				{
					std::cout << "compileShader: Errors: " << std::endl;
					std::cout << (const char*)errorBlob->GetBufferPointer() << std::endl;
				}

				ZAAP_DXRELEASE(errorBlob);
			}
		}
		return nullptr;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // DXShader class //
	/* //////////////////////////////////////////////////////////////////////////////// */
	DXShader::DXShader()
		: m_VShader(nullptr),
		m_PShader(nullptr),
		m_Layout(nullptr)
	{
	}
	
	DXShader::~DXShader()
	{
		ZAAP_DXRELEASE(m_VShader);
		ZAAP_DXRELEASE(m_PShader);
		ZAAP_DXRELEASE(m_Layout);
	}

	bool DXShader::createShaderFromFile(String shaderFile, D3D11_INPUT_ELEMENT_DESC* ied, uint eCount, String vSMain, String pSMain)
	{
		String shaderSrc = zaap::Loader::LoadFile(shaderFile);
		return createShaderFromString(shaderSrc, ied, eCount, vSMain, pSMain);
	}

	bool DXShader::createShaderFromString(String shaderSrc, D3D11_INPUT_ELEMENT_DESC* ied, uint eCount, String vSMain, String pSMain)
	{
		ID3D10Blob *VS;
		ID3D10Blob *PS;

		VS = CompileShader(shaderSrc, "vs_4_0", vSMain);
		PS = CompileShader(shaderSrc, "ps_4_0", pSMain);
		if (!VS || !PS) return false;

		ID3D11Device *dev = DXContext::GetDevice();
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		//creation
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_VShader);
		ZAAP_DXNAME(m_VShader, "DXShader::m_VShader");
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_PShader);
		ZAAP_DXNAME(m_PShader, "DXShader::m_PShader");

		devcon->VSSetShader(m_VShader, nullptr, 0);
		devcon->PSSetShader(m_PShader, nullptr, 0);

		//input layout
		{
			dev->CreateInputLayout(ied, eCount, VS->GetBufferPointer(), VS->GetBufferSize(), &m_Layout);
			if (m_Layout)
			{
				ZAAP_DXNAME(m_Layout, "DXShader::m_Layout");
			} else
			{
				ZA_ERROR("InputLayout creation failed");
				return false;
			}

			devcon->IASetInputLayout(m_Layout);
		}

		//cleanup
		ZAAP_DXRELEASE(VS);
		ZAAP_DXRELEASE(PS);

		return true;
	}


	void DXShader::startDXShader() const
	{
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		devcon->VSSetShader(m_VShader, nullptr, 0);
		devcon->PSSetShader(m_PShader, nullptr, 0);
		devcon->IASetInputLayout(m_Layout);
	}
	void DXShader::stopDXShader() const
	{
		// TODO add stop Method
	}

}}}
