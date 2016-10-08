#include "DXShader.h"

#include <graphics/API/DX/DXContext.h>
#include <util/Console.h>
#include <util/Loader.h>

namespace zaap { namespace graphics { namespace DX {

	bool DXShader::createShaderFromFile(String shaderFile, D3D11_INPUT_ELEMENT_DESC* ied, uint eCount, String vSMain, String pSMain)
	{
		String shaderSrc = Loader::LoadFile(shaderFile);
		return createShaderFromString(shaderSrc, ied, eCount, vSMain, pSMain);
	}

	bool DXShader::createShaderFromString(String shaderSrc, D3D11_INPUT_ELEMENT_DESC* ied, uint eCount, String vSMain, String pSMain)
	{
		ID3D10Blob *VS;
		ID3D10Blob *PS;

		VS = compileShader(shaderSrc, "vs_4_0", vSMain);
		PS = compileShader(shaderSrc, "ps_4_0", pSMain);
		if (!VS || !PS) return false;

		ID3D11Device *dev = DXContext::GetDevice();
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();

		//creation
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_VShader);
		DXNAME(m_VShader, "DXShader::m_VShader");
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_PShader);
		DXNAME(m_PShader, "DXShader::m_PShader");

		devcon->VSSetShader(m_VShader, nullptr, 0);
		devcon->PSSetShader(m_PShader, nullptr, 0);

		//input layout
		{
			dev->CreateInputLayout(ied, eCount, VS->GetBufferPointer(), VS->GetBufferSize(), &m_Layout);
			if (m_Layout)
			{
				DXNAME(m_Layout, "DXShader::m_Layout");
			} else
			{
				ZAAP_ERROR_(m_Layout, "DXShader: InputLayout creation failed");
				return false;
			}

			devcon->IASetInputLayout(m_Layout);
		}

		//cleanup
		DXRELEASE(VS);
		DXRELEASE(PS);

		return true;
	}
	ID3D10Blob* DXShader::compileShader(String &shaderSrc, String version, String &methodName)
	{
		ID3D10Blob *shaderBlob;
		ID3D10Blob *errorBlob;
		HRESULT result = D3DCompile(shaderSrc.c_str(), shaderSrc.size(), NULL, NULL, NULL, methodName.c_str(), version.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
		if (result == S_OK)
			return shaderBlob;
		else
		{
			ZAAP_ERROR("DXShader::compileShader: Unable to compile shader from source");
			if (errorBlob)
			{
				ZAAP_ERROR("DXShader::compileShader: targeted version: " + version);

				if (errorBlob->GetBufferSize())
				{
					std::cout << "DXShader::compileShader: Errors: " << std::endl;
					std::cout << (const char*)errorBlob->GetBufferPointer() << std::endl;
				}

				DXRELEASE(errorBlob);
			}
		}
		return nullptr;
	}

	bool DXShader::CreateConstBuffer(ID3D11Buffer* &buffer, uint size, void* data)
	{
		D3D11_BUFFER_DESC bDesc;
		bDesc.ByteWidth = size;
		bDesc.Usage = D3D11_USAGE_DYNAMIC;
		bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bDesc.MiscFlags = 0;
		bDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &data;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		return !FAILED(DXContext::GetDevice()->CreateBuffer(&bDesc, &initData, &buffer));
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

	void DXShader::cleanDXShader()
	{
		DXRELEASE(m_VShader);
		DXRELEASE(m_PShader);
		DXRELEASE(m_Layout);
	}

}}}
