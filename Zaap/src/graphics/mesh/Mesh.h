#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/VertexBuffer.h>


namespace zaap { namespace graphics {

	class ZAAP_API Mesh
	{
	protected:
		String m_Name;
		
		API::VertexBuffer* m_VertexBuffer;
		
		Mesh();
		Mesh(String name, API::VertexBuffer* vertexBuffer);
	public:

		//vertex buffer
		API::VertexBuffer* getVertexBuffer(void) const;
		uint getVertexCount(void) const;

		String getName(void) const;
 	};

}}