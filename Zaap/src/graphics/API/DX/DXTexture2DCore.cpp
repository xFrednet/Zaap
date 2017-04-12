#include "DXTexture2DCore.h"

#include <util/ImageLoader.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructors / Deconstructor // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	DXTexture2DCore::DXTexture2DCore(String filePath, const ZA_TEXTURE_FILTER& filterType)
		: Texture2DCore(filePath),
		m_Texture(nullptr)
	{
		byte* b = nullptr;
		uint bytesperPixel;

		ZA_RESULT res = ImageLoader::Load(filePath, &m_Width, &m_Height, &bytesperPixel, &b);
		if (ZA_FAILED(res))
		{
			ZA_SUBMIT_ERROR(res);
			return;
		}

		if (bytesperPixel == 32)
			init(b, ZA_FORMAT_R8G8B8A8_UINT, filterType);
		else 
			init(b, ZA_FORMAT_R8G8B8_UINT, filterType);

		delete b;
	}
	DXTexture2DCore::DXTexture2DCore(const Bitmap& bitmap, const String& name, const ZA_TEXTURE_FILTER& filterType)
		: Texture2DCore(name),
		m_Texture(nullptr)
	{
		m_Width = bitmap.getWidth();
		m_Height = bitmap.getHeight();
		m_Format = bitmap.getFormat();

		init(bitmap.getPixelArray(), bitmap.getFormat(), filterType);
	}

	DXTexture2DCore::DXTexture2DCore(ID3D11Texture2D* texture)
		: Texture2DCore("given Texture"),
		m_Texture(texture),
		m_TextureView(nullptr),
		m_SamplerState(nullptr)
	{
		m_Texture->GetDesc(&m_TextureDesc);
		m_Width = m_TextureDesc.Width;
		m_Height = m_TextureDesc.Height;

		//init(nullptr, ZA_FORMAT_UNKNOWN);
	}

	DXTexture2DCore::~DXTexture2DCore()
	{
		ZA_DXRELEASE(m_Texture);
		ZA_DXRELEASE(m_TextureView);
		ZA_DXRELEASE(m_SamplerState);
	}

	ZA_RESULT DXTexture2DCore::init(byte const *bytes, ZA_FORMAT format, ZA_TEXTURE_FILTER filterType)
	{
		//general declarations
		HRESULT result;
		ID3D11Device *dev = DXContext::GetDevice();
		
		//Format
		DXGI_FORMAT DXformat = GetDirectXFormat(format);

		//
		// Texture
		//
		ZA_ASSERT(!m_Texture, "m_Texture is already initialized");
		if (m_Texture)
			return ZA_ERROR_API_TEXTURE2D_CREATION_ERROR;

		if (!m_Texture)
		{
			//sub resource
			D3D11_SUBRESOURCE_DATA resource;
			uint stride = GetFormatSize(format);
			resource.pSysMem			= bytes;
			resource.SysMemPitch		= stride * m_Width;
			resource.SysMemSlicePitch	= stride * m_Width * m_Height;

			//texture
			ZeroMemory(&m_TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

			m_TextureDesc.Width				= m_Width;
			m_TextureDesc.Height			= m_Height;
			m_TextureDesc.MipLevels			= 1;
			m_TextureDesc.ArraySize			= 1;
			m_TextureDesc.Format			= DXformat;
			m_TextureDesc.SampleDesc.Count	= 1;
			m_TextureDesc.Usage				= D3D11_USAGE_DYNAMIC;
			m_TextureDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
			m_TextureDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
			m_TextureDesc.MiscFlags			= 0;
			
			result = dev->CreateTexture2D(&m_TextureDesc, &resource, &m_Texture);
			if (FAILED(result))
			{
				ZA_ERROR("Failed to create a Texture2D with the given data.");
				return ZA_ERROR_API_TEXTURE_ERROR;
			}
			ZA_DXNAME(m_Texture, String("DXTexture2D::m_Texture(" + m_Name + ")"));
		} else
		{
			m_Texture->GetDesc(&m_TextureDesc);
			DXformat = m_TextureDesc.Format;
		}

		//
		// Resource View
		//
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
			ZeroMemory(&resDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

			resDesc.Format = DXformat;
			resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			resDesc.Texture2D.MostDetailedMip = 0;
			resDesc.Texture2D.MipLevels = -1;

			result = dev->CreateShaderResourceView(m_Texture, &resDesc, &m_TextureView);
			if (FAILED(result))
			{
				ZA_ERROR("Failed to create a ShaderResourceView.");
				return ZA_ERROR_API_TEXTURE_ERROR;
			}
			ZA_DXNAME(m_Texture, String("DXTexture2D::m_TextureView(" + m_Name + ")"));
			//TODO add devcon->GenerateMips(m_TextureView);
		}

		//
		// Sampler
		//
		{
			if (filterType == ZA_TEXTURE_FILTER_LINAR)
				m_SamplerDesc.Filter		= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			else 
				m_SamplerDesc.Filter		= D3D11_FILTER_MIN_MAG_MIP_POINT;
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
				ZA_ERROR("Failed to create a ShaderResourceView.");
				return ZA_ERROR_API_TEXTURE_ERROR;
			}
			ZA_DXNAME(m_SamplerState, String("DXTexture2D::m_SamerState(" + m_Name + ")"));
		}

		return ZA_OK;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Abstract members // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	void DXTexture2DCore::bind(uint slot)
	{
		
		if (!m_TextureView && !m_SamplerState)
			return;

		DXContext::GetDevContext()->PSSetShaderResources(slot, 1, &m_TextureView);
		DXContext::GetDevContext()->PSSetSamplers(slot, 1, &m_SamplerState);
	}
	void DXTexture2DCore::unbind(uint slot)
	{
		DXContext::GetDevContext()->PSSetShaderResources(slot, 1, nullptr);
		DXContext::GetDevContext()->PSSetSamplers(slot, 1, nullptr);
	}

}}}