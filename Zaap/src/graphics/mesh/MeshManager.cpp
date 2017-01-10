#include "MeshManager.h"

#include <util/Console.h>
#include "TexturedMesh.h"

namespace zaap { namespace graphics {
	
	std::map<String, MeshManager::ZA_MESHMANAGER_MESH_INFO> MeshManager::s_MeshMap;

	void MeshManager::Add(Mesh* mesh)
	{
		if (!mesh)
		{
			ZAAP_ALERT("The submitted Mesh is null");
			return;
		}
		if (Contains(mesh))
		{
			ZAAP_ALERT("This manager already contains a Mesh with the name: \"" + mesh->getName() + "\"");
			return;
		}

		ZA_MESHMANAGER_MESH_INFO newMeshInfo;
		
		newMeshInfo.Mesh = mesh;
		newMeshInfo.UseCount = 1; //This is set to 1 because the added Mesh will be used too.

		s_MeshMap[mesh->getName()] = newMeshInfo;

		ZAAP_INFO("added: \"" + mesh->getName() + "\"");
	}

	Mesh* MeshManager::Get(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) == s_MeshMap.end())
			return nullptr;
		
		it->second.UseCount++;

		return it->second.Mesh;
	}

	bool MeshManager::Contains(const Mesh* mesh)
	{
		return Contains(mesh->getName());
	}

	bool MeshManager::Contains(const String& name)
	{
		return s_MeshMap.find(name) != s_MeshMap.end();
	}

	void MeshManager::Cleanup()
	{
		// TODO MeshManager cleanup
		//ZAAP_CLEANUP_INFO();
	}
}}
