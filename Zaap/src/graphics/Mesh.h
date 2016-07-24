#pragma once

#include "API/DXCommon.h"
#include "API/VertexBuffer.h"
#include "Common.h"
#include "Types.h"

namespace zaap { namespace graphics {

	class ZAAP_API Mesh
	{
	private:
		API::VertexBuffer* m_VertexBuffer;
	public:
		Mesh();
		Mesh(API::VertexBuffer* vertexBuffer);

		API::VertexBuffer* getVertexBuffer(void) const;
		uint getVertexCount(void) const;

 	};

}}