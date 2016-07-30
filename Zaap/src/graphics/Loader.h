#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {

	struct ZAAP_API COLOR {	
		float R, G, B, A;
		
	public:
		COLOR();
		COLOR(float r, float g, float b, float a);
	};

	struct ZAAP_API VERTEX
	{
		math::Vec3 Position;
		math::Vec2 TexCoord;
		math::Vec3 Normal;

	public:
		VERTEX();
		VERTEX(math::Vec3 position, math::Vec2 texCoord, math::Vec3 normal);
	};

	class ZAAP_API Loader
	{
	public:
		Loader(void);

		API::VertexBuffer* loadOBJFile(String file);
		void loadMTLFile(String file);

		virtual API::VertexBuffer* loadVBuffer(VERTEX vertices[], uint vCount, uint indexBuffer[], uint indexCount) = 0;

		virtual void cleanup(void) const = 0;
	};

}}