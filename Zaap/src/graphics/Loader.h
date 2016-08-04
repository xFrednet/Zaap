#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {

	class ZAAP_API Loader
	{
	public:
		Loader(void);

		Mesh* loadOBJFile(String name, String file, bool texturedMesh = true);
		void loadMTLFile(String file) const;

		virtual API::VertexBuffer* loadVBuffer(void* vertices, uint vertexSize, uint vCount, uint indices[], uint indexCount) = 0;

		virtual void cleanup(void) = 0;
	};

}}