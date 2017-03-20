#pragma once

#include <Common.h>
#include <Types.h>
#include <util/UUID.h>
#include <graphics/shader/Shader.h>
#include <graphics/camera/ViewFrustum.h>

namespace zaap { namespace graphics { namespace API {
	
	//TODO add vertex buffer without a IndexBuffer

	class ZAAP_API VertexBuffer
	{
		////////////////
		// Management //
		////////////////
	private:
		static std::vector<VertexBuffer*> s_VertexBuffers;
	public:
		static VertexBuffer* CreateVertexbuffer(uint vertexSize, uint vertexCount, uint indexCount, void* vertices = nullptr, uint* indices = nullptr);
		static void Delete(VertexBuffer* vertexbuffer);
		static void Delete(const UUID& uuid);
		static void Cleanup();

		///////////////////////
		// Rendering options //
		///////////////////////
	private:
		static uint s_TotalDrawCount;
		static ViewFrustum s_ViewFrustum;

	public:
		//draw count
		static inline uint GetTotalDrawCount();
		static inline void ClearTotalDrawCount();

		static inline void SetViewFrustum(const ViewFrustum& view);
		static inline ViewFrustum GetViewFrustum();

		/////////////////////////////////
		// And finally the actual class //
		/////////////////////////////////
	protected:
		UUID m_uuid;

		uint m_IndexCount;
		uint m_VertexCount;
		bool m_IsDynamic;
		
		VertexBuffer(const uint& vertexCount, const uint& indexCount);

	public:
		virtual ~VertexBuffer() {}

		//class methods

		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		virtual void draw() = 0;
		virtual void draw(const uint &count) = 0;
		virtual void draw(const uint &start, const uint &count) = 0;
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Getters //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline uint getVertexCount() const;
		inline uint getIndexCount() const;
		inline bool isDynamic() const;

		inline UUID getUUID() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Dynamic methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		virtual void updateVertices(void* vertices, uint vertexCount) = 0;
		virtual void updateIndices(uint* indicies, uint indexCount) = 0;
	};

}}}
