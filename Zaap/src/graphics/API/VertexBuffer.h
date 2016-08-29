#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace graphics { namespace API {
	
	class ZAAP_API VertexBuffer
	{
	private:
		uint m_VertexCount;
	
		static std::vector<VertexBuffer*> s_VertexBuffers;

	protected:
		VertexBuffer(uint vertexCount);

	public:
		
		//VertexBuffer management
		static VertexBuffer* CreateVertexbuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount);
		static void Cleanup();

		uint getVertexCount(void) const;
		
		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;

		virtual void cleanup() = 0;
	};

}}}