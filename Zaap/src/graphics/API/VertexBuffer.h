#pragma once

#include <Common.h>
#include <Types.h>
#include <util/UUID.h>
#include <graphics/camera/ViewFrustum.h>

namespace zaap { namespace graphics { namespace API {
	
	//TODO add vertex buffer without a IndexBuffer
	class VertexBufferCore;

	typedef za_ptr<VertexBufferCore> VertexBuffer;

	class ZAAP_API VertexBufferCore
	{
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Creation //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		static VertexBufferCore* CreateVertexBufferCore(uint vertexSize, const uint& vertexCount, const uint& indexCount, void* vertices = nullptr, uint* indices = nullptr);
		static VertexBuffer CreateVertexBuffer(uint vertexSize, const uint& vertexCount, const uint& indexCount, void* vertices = nullptr, uint* indices = nullptr);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Rendering Info //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		static uint s_TotalDrawCount;
		static ViewFrustum s_ViewFrustum;

	public:
		static uint GetTotalDrawCount();
		static void ClearTotalDrawCount();

		static void SetViewFrustum(const ViewFrustum& view);
		static ViewFrustum GetViewFrustum();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Class //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		UUID m_UUID;

		uint m_IndexCount;
		uint m_VertexCount;
		bool m_IsDynamic;
		
		VertexBufferCore(const uint& vertexCount, const uint& indexCount);

	public:
		virtual ~VertexBufferCore() {};

		/* ********************************************************* */
		// * Draw methods *
		/* ********************************************************* */
		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		virtual void draw() = 0;
		virtual void draw(const uint &count) = 0;
		virtual void draw(const uint &start, const uint &count) = 0;

		/* ********************************************************* */
		// * Getters *
		/* ********************************************************* */
		inline uint getVertexCount() const
		{
			return m_VertexCount;
		}
		inline uint getIndexCount() const
		{
			return m_IndexCount;
		}
		inline bool isDynamic() const
		{
			return m_IsDynamic;
		}

		inline UUID getUUID() const
		{
			return m_UUID;
		}

		/* ********************************************************* */
		// * Dynamic methods *
		/* ********************************************************* */
		virtual void updateVertices(void* vertices, uint vertexCount) = 0;
		virtual void updateIndices(uint* indicies, uint indexCount) = 0;
	};

}}}
