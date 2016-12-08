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
		static VertexBuffer* CreateVertexbuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount, ZA_SHADER_TYPE targetShader);
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
		// And finaly the actual class //
		/////////////////////////////////
	protected:
		uint m_VertexCount;
		UUID m_uuid;

		ZA_SHADER_TYPE m_TargetShader;

		VertexBuffer(uint vertexCount, ZA_SHADER_TYPE targetShader);

	public:
		virtual ~VertexBuffer() {}

		//class methods
		inline uint getVertexCount(void) const;
		inline UUID getUUID(void) const;

		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		virtual void draw() = 0;
		virtual void draw(const uint &count) = 0;
		virtual void draw(const uint &start, const uint &count) = 0;

		virtual void cleanup() = 0;
	};

}}}
