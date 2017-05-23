#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXVertexBufferCore : public API::VertexBufferCore
	{
	private:
		friend class DXRenderer;
		friend class VertexBuffer;
	private:
		ID3D11Buffer *m_VertexBuffer;
		ID3D11Buffer *m_IndexBuffer;
		
		uint m_Stride;
	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructor and Deconstructor //
		/* //////////////////////////////////////////////////////////////////////////////// */
		DXVertexBufferCore(uint vertexSize, uint vertexCount, uint indexCount, void* vertices = nullptr, uint* indices = nullptr);
		DXVertexBufferCore(ID3D11Buffer *vertexBuffer, ID3D11Buffer *indexBuffer, uint stride, uint vertexCount, uint indexCount);
		virtual ~DXVertexBufferCore();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Draw util //
		/* //////////////////////////////////////////////////////////////////////////////// */
		void bind(uint slot) override;
		void unbind(uint slot) override;

		void draw() override;
		void draw(const uint& count) override;
		void draw(const uint &start, const uint &count) override;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Getters //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline ID3D11Buffer* getVertexBuffer();
		inline ID3D11Buffer const* getVertexBuffer() const;
		inline ID3D11Buffer* getIndexBuffer();
		inline ID3D11Buffer const* getIndexBuffer() const;
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Dynamic methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		void updateVertices(void* vertices, uint vertexCount) override;
		void updateIndices(uint* indicies, uint indexCount) override;
	};

}}}