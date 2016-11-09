#pragma once

#include <Common.h>
#include <Types.h>
#include <util/UUID.h>
#include <graphics/shader/Shader.h>

namespace zaap { namespace graphics { namespace API {
	
	//TODO add vertex buffer without a IndexBuffer

	class ZAAP_API VertexBuffer
	{
		//Static values
	private:
		static std::vector<VertexBuffer*> s_VertexBuffers;
		static uint s_TotalDrawCount;

		//Static methods
	public:
		static VertexBuffer* CreateVertexbuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount, ZA_SHADER_TYPE targetShader);
		static void Delete(VertexBuffer* vertexbuffer);
		static void Delete(UUID uuid);
		static void Cleanup();

		//draw count
		static uint getTotalDrawCount();
		static void clearTotalDrawCount();

	protected:
		uint m_VertexCount;
		UUID m_uuid;

		ZA_SHADER_TYPE m_TargetShader;

		VertexBuffer(uint vertexCount, ZA_SHADER_TYPE targetShader);

	public:
		~VertexBuffer() {}

		//class methods
		uint getVertexCount(void) const;
		UUID getUUID(void) const;

		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		virtual void draw() = 0;
		virtual void draw(const uint &count) = 0;
		virtual void draw(const uint &start, const uint &count) = 0;

		virtual void cleanup() = 0;
	};

}}}
