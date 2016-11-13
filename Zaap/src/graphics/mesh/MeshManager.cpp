#include "MeshManager.h"

#include <util/Console.h>

namespace zaap { namespace graphics {
	
	std::vector<Mesh*> MeshManager::s_Meshs;

	Mesh* MeshManager::AddMesh(String name, API::VertexBuffer* vertexBuffer, API::Texture2D* texture)
	{
		return AddMesh(new TexturedMesh(name, vertexBuffer, texture));
	}

	Mesh* MeshManager::AddMesh(Mesh* mesh)
	{
		
		if (mesh->getName() == "NULL")
		{
			ZAAP_ERROR("submitted TMesh has no name");
		} else
		{
//This code only runs in debug mode because it could influence the performance
#ifdef ZAAP_DEBUG
			if (HasName(mesh->getName())) {
				ZAAP_ALERT("submitted TMesh has a name that is already included");
			}
#endif //ZAAP_DEBUG

			s_Meshs.push_back(mesh);

		}
		return mesh;
	}

	Mesh* MeshManager::GetMesh(String name)
	{
		for (uint i = 0; i < s_Meshs.size(); i++)
		{
			if (s_Meshs[i]->getName() == name)
				return s_Meshs[i];
		}

		ZAAP_ALERT("Requested TMesh was not found. Requested name: " + name);
		return nullptr;
	}

	bool MeshManager::HasName(String name)
	{
		for (uint i = 0; i < s_Meshs.size(); i++)
		{
			if (s_Meshs[i]->getName() == name)
				return true;
		}
		return false;
	}

	void MeshManager::Cleanup()
	{
		for (uint i = 0; i < s_Meshs.size(); i++)
			delete s_Meshs[i];
		ZAAP_CLEANUP_INFO();
	}
}}
