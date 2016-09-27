#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace graphics { namespace API {
	
	//TODO add vertex buffer without a IndexBuffer

	class ZAAP_API VertexBuffer
	{
	private:
		static std::vector<VertexBuffer*> s_VertexBuffers;

	protected:
		static uint s_TotalDrawCount;
		uint m_VertexCount;
		
		VertexBuffer(uint vertexCount);

	public:
		
		//Static values
		static VertexBuffer* CreateVertexbuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount);
		static void Cleanup();
		//draw count
		static uint getTotalDrawCount();
		static void clearTotalDrawCount();

		//class methods
		uint getVertexCount(void) const;
		
		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		virtual void draw() = 0;
		virtual void draw(const uint &count) = 0;
		virtual void draw(const uint &start, const uint &count) = 0;

		virtual void cleanup() = 0;
	};

}}}