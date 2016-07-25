#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace graphics { namespace API {
	
	class ZAAP_API VertexBuffer
	{
	private:
		uint m_VertexCount;
	protected:
		VertexBuffer(uint vertexCount);
	public:

		uint getVertexCount(void) const;
		
		virtual void bind(uint slot) = 0;
		virtual void unbind(uint slot) = 0;
	};

}}}