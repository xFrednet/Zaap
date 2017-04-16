#include "DXTexture2DCore.h"

#include <util/ImageLoader.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace DX {

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructors / Deconstructor // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	DXTexture2DCore::DXTexture2DCore(String filePath, ZA_TEX2D_DESC desc)
		: Texture2DCore(filePath),
		m_Texture(nullptr)
	{
		byte* b = nullptr;
		uint bytesperPixel;

		ZA_RESULT res = ImageLoader::Load(filePath, &m_Width, &m_Height, &bytesperPixel, &b);
		ZA_ASSERT(ZA_SUCCEDED(res), "ImageLoader::Load failed.");

		desc.Format = (bytesperPixel == 32) ? ZA_FORMAT_R8G8B8A8_UINT : ZA_FORMAT_R8G8B8_UINT;
		res = init(b, desc);
		ZA_ASSERT(ZA_SUCCEDED(res), "init failed.");
		//TODO add error messages

		delete b;
	}
	DXTexture2DCore::DXTexture2DCore(const Bitmap& bitmap, const String& name, ZA_TEX2D_DESC desc)
		: Texture2DCore(name),
		m_Texture(nullptr)
	{
		m_Width = bitmap.getWidth();
		m_Height = bitmap.getHeight();
		desc.Format = bitmap.getFormat();

		ZA_RESULT zr = init(bitmap.getPixelArray(), desc);
		ZA_ASSERT(ZA_SUCCEDED(zr));
	}

	DXTexture2DCore::DXTexture2DCore(ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureView, ID3D11SamplerState* sampler)
		: Texture2DCore("given Texture"),
		m_Texture(texture),
		m_TextureView(textureView),
		m_SamplerState(sampler)
	{
		m_Texture->GetDesc(&m_TextureDesc);
		m_Width = m_TextureDesc.Width;
		m_Height = m_TextureDesc.Height;
	}

	DXTexture2DCore::~DXTexture2DCore()
	{
		ZA_DXRELEASE(m_Texture);
		ZA_DXRELEASE(m_TextureView);
		ZA_DXRELEASE(m_SamplerState);
	}

	ZA_RESULT DXTexture2DCore::init(byte const *bytes, ZA_TEX2D_DESC desc)
	{
		//general declarations
		HRESULT result;
		ID3D11Device *dev = DXContext::GetDevice();
		ID3D11DeviceContext *devcon = DXContext::GetDevContext();
		
		//Format
		m_Format = desc.Format;
		DXGI_FORMAT DXformat = GetDirectXFormat(desc.Format);

		/* ********************************************************* */
		// * Desc validation *
		/* ********************************************************* */
		uint mipMapCount = 1;
		{
			if (desc.IsDynamic && desc.MipMapCount != 1)
			{
				ZA_ALERT("A dynamic texture has to have a MipMapCount of 1");
				desc.MipMapCount = 1;
			}
			/* ##################################### */
			// # MipMap #
			/* ##################################### */
			uint maxCount = (m_Width == m_Height) ? (uint)log2f((float)m_Width) : 1;
			if (desc.MipMapCount > 1)
			{
				if (maxCount < desc.MipMapCount)
				{
					ZA_ALERT("The targeted MipMap count(", desc.MipMapCount, ") is higher than the possible maximum MipMap count of: ", maxCount);
					desc.MipMapCount = maxCount;
				}
			}
			if (desc.MipMapCount == 0)
				mipMapCount = maxCount;
			else
				mipMapCount = desc.MipMapCount;
		}

		/* ********************************************************* */
		// * Texture *
		/* ********************************************************* */
		{
			ZA_ASSERT(!m_Texture, "m_Texture is already initialized");
			if (m_Texture)
				return ZA_ERROR_API_TEXTURE2D_CREATION_ERROR;

			{
				//texture
				ZeroMemory(&m_TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

				m_TextureDesc.Width				= m_Width;
				m_TextureDesc.Height			= m_Height;
				m_TextureDesc.ArraySize			= 1;
				m_TextureDesc.Format			= DXformat;
				m_TextureDesc.SampleDesc.Count	= 1;
				m_TextureDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
				//MipMaps
				m_TextureDesc.BindFlags			|= (desc.MipMapCount != 1) ? D3D11_BIND_RENDER_TARGET : 0;
				m_TextureDesc.MipLevels			= desc.MipMapCount;
				m_TextureDesc.MiscFlags			= (desc.MipMapCount != 1) ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;
				//dynamic
				if (desc.IsDynamic)
				{
					m_TextureDesc.Usage				= D3D11_USAGE_DYNAMIC;
					m_TextureDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
				} else
				{
					m_TextureDesc.Usage				= D3D11_USAGE_DEFAULT;
					m_TextureDesc.CPUAccessFlags	= 0;
				}

				/* ##################################### */
				// # Creation #
				/* ##################################### */
				result = dev->CreateTexture2D(&m_TextureDesc, nullptr, &m_Texture);
				ZA_DXNAME(m_Texture, String("DXTexture2D::m_Texture(" + m_Name + ")"));
				if (FAILED(result))
					return ZA_ERROR_API_TEXTURE_ERROR;

				devcon->UpdateSubresource(m_Texture, 0, 0, bytes, GetFormatSize(desc.Format) * m_Width, 0);
			}
		}

		/* ********************************************************* */
		// * ShaderResourceView *
		/* ********************************************************* */
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
			ZeroMemory(&resDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

			resDesc.Format						= DXformat;
			resDesc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
			resDesc.Texture2D.MostDetailedMip	= 0;
			resDesc.Texture2D.MipLevels			= -1;

			/* ##################################### */
			// # Creation #
			/* ##################################### */
			result = dev->CreateShaderResourceView(m_Texture, &resDesc, &m_TextureView);
			ZA_DXNAME(m_TextureView, String("DXTexture2D::m_TextureView(" + m_Name + ")"));
			if (FAILED(result))
				return ZA_ERROR_API_TEXTURE_ERROR;
			
			if (desc.MipMapCount != 1)
				devcon->GenerateMips(m_TextureView);
		}

		/* ********************************************************* */
		// * Sampler *
		/* ********************************************************* */
		{
			m_SamplerDesc.Filter = (desc.FilterType == ZA_TEXTURE_FILTER_LINAR) ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
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

			/* ##################################### */
			// # Creation #
			/* ##################################### */
			result = dev->CreateSamplerState(&m_SamplerDesc, &m_SamplerState);
			ZA_DXNAME(m_SamplerState, String("DXTexture2D::m_SamerState(" + m_Name + ")"));
			if (FAILED(result))
				return ZA_ERROR_API_TEXTURE_ERROR;
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
