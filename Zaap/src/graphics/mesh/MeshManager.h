#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/TexturedMesh.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API MeshManager
	{
	private:
		static std::vector<Mesh*> s_Meshs;

		inline MeshManager(void) {};
	
	public:
		static Mesh* AddMesh(String name, API::VertexBuffer* vertexBuffer, API::Texture2D* texture);
		static Mesh* AddMesh(Mesh* mesh);
		static Mesh* GetMesh(String name);

		static bool HasName(String name);

		static void Cleanup();
	};

}}
