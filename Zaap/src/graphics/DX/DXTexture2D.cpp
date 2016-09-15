#include "DXTexture2D.h"

#include <util/ImageLoader.h>
#include <util/Console.h>

namespace zaap { namespace graphics { namespace DX {
	
	DXTexture2D::DXTexture2D(String name, String filePath)
		: Texture2D(name)
	{
		init(ImageLoader::Load(filePath, &m_Width, &m_Height, &m_BitsPerPixel));
	}

	DXTexture2D::DXTexture2D(String name, Image image)
		: Texture2D(name)
	{
		if (image.getBitsPerPixel() != 32)
		{
			ZAAP_ALERT("DXTexture2D: submitted Image has an unexpected bitrate");
		}

		m_Width = image.getWidth();
		m_Height = image.getHeight();
		m_BitsPerPixel = image.getBitsPerPixel();

		init(image.getPixelArray());
	}

	void DXTexture2D::init(byte const *bytes)
	{
		//general declarations
		HRESULT result;
		ID3D11Device *dev = DXContext::GetDevice();
		
		//
		// Texture
		//
		{
			//sub resource
			D3D11_SUBRESOURCE_DATA resource;
			uint stride = 4;
			resource.pSysMem			= bytes;
			resource.SysMemPitch		= stride * m_Width;
			resource.SysMemSlicePitch	= stride * m_Width * m_Height;

			//texture
			ZeroMemory(&m_TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

			m_TextureDesc.Width				= m_Width;
			m_TextureDesc.Height			= m_Height;
			m_TextureDesc.MipLevels			= 1;
			m_TextureDesc.ArraySize			= 1;
			m_TextureDesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
			m_TextureDesc.SampleDesc.Count	= 1;
			m_TextureDesc.Usage				= D3D11_USAGE_DYNAMIC;
			m_TextureDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
			m_TextureDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
			m_TextureDesc.MiscFlags			= 0;
			
			result = dev->CreateTexture2D(&m_TextureDesc, &resource, &m_Texture);
			if (FAILED(result))
			{
				ZAAP_ERROR("DXTexture2D: Failed to create a Texture2D with the given data.");
				return;
			}
			DXNAME(m_Texture, String("DXTexture2D::m_Texture(" + m_TextureName + ")"));
		}

		//
		// Resource View
		//
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
			ZeroMemory(&resDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

			resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			resDesc.Texture2D.MostDetailedMip = 0;
			resDesc.Texture2D.MipLevels = -1;

			result = dev->CreateShaderResourceView(m_Texture, &resDesc, &m_TextureView);
			if (FAILED(result))
			{
				ZAAP_ERROR("DXTexture2D: Failed to create a ShaderResourceView.");
				return;
			}
			DXNAME(m_Texture, String("DXTexture2D::m_TextureView(" + m_TextureName + ")"));
			//TODO add devcon->GenerateMips(m_TextureView);
		}

		//
		// Sampler
		//
		{
			m_SamplerDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			m_SamplerDesc.AddressU			= D3D11_TEXTURE_ADDRESS_WRAP;
			m_SamplerDesc.AddressV			= D3D11_TEXTURE_ADDRESS_WRAP;
			m_SamplerDesc.AddressW			= D3D11_TEXTURE_ADDRESS_WRAP;
			m_SamplerDesc.MipLODBias		= 0;
			m_SamplerDesc.MaxAnisotropy		= 1;
			m_SamplerDesc.ComparisonFunc	= D3D11_COMPARISON_ALWAYS;
			m_SamplerDesc.BorderColor[0]	= 0;
			m_SamplerDesc.BorderColor[1]	= 0;
			m_SamplerDesc.BorderColor[2]	= 0;
			m_SamplerDesc.BorderColor[3]	= 0;
			m_SamplerDesc.MinLOD			= 0;
			m_SamplerDesc.MaxLOD			= D3D11_FLOAT32_MAX;

			result = dev->CreateSamplerState(&m_SamplerDesc, &m_SamplerState);
			if (FAILED(result))
			{
				ZAAP_ERROR("DXTexture2D: Failed to create a ShaderResourceView.");
				return;
			}
			DXNAME(m_SamplerState, String("DXTexture2D::m_SamerState(" + m_TextureName + ")"));
		}

	}

	void DXTexture2D::bind(uint slot)
	{
		DXContext::GetDevContext()->PSSetShaderResources(slot, 1, &m_TextureView);
		DXContext::GetDevContext()->PSSetSamplers(slot, 1, &m_SamplerState);
	}
	void DXTexture2D::unbind(uint slot)
	{
		DXContext::GetDevContext()->PSSetShaderResources(slot, 1, nullptr);
		DXContext::GetDevContext()->PSSetSamplers(slot, 1, nullptr);
	}

	void DXTexture2D::cleanup() 
	{
		DXRELEASE(m_Texture);
		DXRELEASE(m_TextureView);
		DXRELEASE(m_SamplerState);
	}

}}}