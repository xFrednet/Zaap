#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/TexturedMesh.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API TMeshManager
	{
	private:
		static std::vector<TexturedMesh> s_TMeshs;

		inline TMeshManager(void) {};
	
	public:
		static TexturedMesh AddTMesh(String name, Mesh &mesh, Texture2D* texture);
		static TexturedMesh AddTMesh(TexturedMesh &tMesh);
		static TexturedMesh GetTMesh(String name);

		static bool hasName(String name);
	};

}}
