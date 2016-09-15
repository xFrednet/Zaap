#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {

	class ZAAP_API Loader
	{
	public:
		static Mesh* LoadOBJFile(String name, String file, bool texturedMesh = true);
		static void LoadMTLFile(String file);

	};

}}