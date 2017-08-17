#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/Shader.h>
#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/DX/DXContext.h>


namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXShader
	{
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Static Util //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		// <Function>
		//		CreateConstBuffer
		//
		// <Description>
		//		This creates a constant buffer from the given information.
		//
		// <Note>
		//		TODO change the return value to ZA_RESULT
		//
		// <Input>
		//		buffer::
		//			The buffer that will be created. It should point to a nullptr.;;
		//		size::
		//			The size of the buffer. (Just use sizeof() on the buffer struct);;
		//		data::
		//			A pointer to the memory that should be loaded at the start.;;
		//
		// <Return>
		//		A value that indicates if this creating failed or not.
		//
		static inline bool CreateConstBuffer(ID3D11Buffer** buffer, const uint& size, void const* data)
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

			return !FAILED(DXContext::GetDevice()->CreateBuffer(&bDesc, &initData, buffer));
		}

		// <Function>
		//		LoadResource
		//
		// <Description>
		//		This loads the given date to the given buffer.
		//
		// <Note>
		//		TODO run performance test on this function vs directly writing it into the shader
		//
		// <Input>
		//		buffer::
		//			The buffer that should be written to.;;
		//		data::
		//			A pointer to the memory that should be loaded.;;
		//		size::
		//			The size of the buffer. (Just use sizeof() on the buffer struct);;
		//
		static inline void LoadResource(ID3D11Resource* buffer, void const* data, const uint& size)
		{
			D3D11_MAPPED_SUBRESOURCE ms;
			DXContext::GetDevContext()->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, data, size);
			DXContext::GetDevContext()->Unmap(buffer, NULL);
		}

	private:
		// <Function>
		//		compileShader
		//
		// <Description>
		//		This compiles the shader and returns is as a ID3D10Blob.
		//
		// <Note>
		//		TODO return a ZA_RESULT
		//
		// <Input>
		//		shaderSrc::
		//			The source code of the shader.;;
		//		version::
		//			The version that should be used by the compiler.;;
		//		methodName::
		//			The name of the main method in the shader.;;
		//
		// <Return>
		//		This returns the compiled shader or a nullptr in case of a failure.
		//
		static ID3D10Blob* CompileShader(String shaderSrc, const String& version, const String &methodName);
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // DXShader class //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		// <Value>
		//		m_VShader
		//
		// <Description>
		//		The pointer to the vertex shader object.
		//
		ID3D11VertexShader *m_VShader;
		// <Value>
		//		m_PShader
		//
		// <Description>
		//		The pointer to the pixel shader object.
		//
		ID3D11PixelShader *m_PShader;
		// <Value>
		//		m_Layout
		//
		// <Description>
		//		The input layout for this shader.
		//
		ID3D11InputLayout *m_Layout;
	public:
		// <Constructor>
		//		DXShader
		//
		// <Description>
		//		This constructor simply sets the members to null.
		//
		DXShader();

		// <Destructor>
		//		~DXShader
		//
		// <Description>
		//		This deletes the pointers... thats it.
		//
		virtual ~DXShader();

		
		//TODO update createShaderFromFile and createShaderFromString to return a ZA_RESULT (maybe rename them to initFromFile and initFromString)
		ZA_RESULT createShaderFromFile(String shaderFile, D3D11_INPUT_ELEMENT_DESC *ied, uint eCount, String vSMain = "VShader", String pSMain = "PShader");
		ZA_RESULT createShaderFromString(String shaderSrc, D3D11_INPUT_ELEMENT_DESC *ied, uint eCount, String vSMain = "VShader", String pSMain = "PShader");
		
		// <Function>
		//		startDXShader
		//
		// <Description>
		//		This starts the vertex and the pixel shader.
		//
		// <Note>
		//		This only starts the two shaders the buffers have to
		//		be loaded from the sub classes.
		//
		void startDXShader() const;

		// <Function>
		//		stopDXShader
		//
		// <Description>
		//		This stops the vertex and the pixel shader.
		//
		// <Note>
		//		This isn't implemented yet because I haven't found a
		//		reason to stop the shader when a different shader is
		//		set right afterwards.
		//
		void stopDXShader() const;
	public:

	};

}}}
