#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXVertexBuffer : public API::VertexBuffer
	{
	private:
		friend class DXRenderer;
		friend class VertexBuffer;
	private:
		ID3D11Buffer *m_VBuffer;
		ID3D11Buffer *m_IndexBuffer;
		
		uint m_Stride;
	public:
		DXVertexBuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount);
		DXVertexBuffer(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, uint vertexCount, uint stride);

		ID3D11Buffer* const* getVBuffer() const;
		ID3D11Buffer* getIBuffer() const;

		void bind(uint slot) override;
		void unbind(uint slot) override;

		void draw() override;
		void draw(const uint& count) override;
		void draw(const uint &start, const uint &count) override;

		void cleanup() override;
	};

}}}