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

	void MeshManager::ReleasedMesh(Mesh* mesh)
	{
		//null check
		if (!mesh)
		{
			ZAAP_ALERT("The submitted Mesh is null");
			return;
		}

		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(mesh->getName())) == s_MeshMap.end())
			delete mesh; //TODO destroy mesh

		it->second.UseCount--;
		if (it->second.UseCount == 0)
		{
			if (it->second.Mesh)
			{
				delete it->second.Mesh; //TODO destroy mesh
				it->second.Mesh = nullptr;
			}
			s_MeshMap.erase(it);
		}
	}

	void MeshManager::RemoveMesh(Mesh* mesh)
	{
		if (mesh)
			RemoveMesh(mesh->getName());
	}

	void MeshManager::RemoveMesh(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) != s_MeshMap.end())
			s_MeshMap.erase(it);
	}

	Mesh* MeshManager::Get(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) == s_MeshMap.end())
			return nullptr;
		
		it->second.UseCount++;

		return it->second.Mesh;
	}

	uint MeshManager::GetUseCount(Mesh const* mesh)
	{
		if (mesh)
			return GetUseCount(mesh->getName());

		return 0;
	}

	uint MeshManager::GetUseCount(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) != s_MeshMap.end())
			return it->second.UseCount;

		return 0;
	}

	bool MeshManager::Contains(const Mesh* mesh)
	{
		if (mesh)
			return Contains(mesh->getName());

		return false;
	}

	bool MeshManager::Contains(const String& name)
	{
		return s_MeshMap.find(name) != s_MeshMap.end();
	}

	void MeshManager::Cleanup()
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		for (it = s_MeshMap.begin(); it != s_MeshMap.end(); it++)
		{
			delete it->second.Mesh; //TODO destroy mesh
		}
		s_MeshMap.clear();

		ZAAP_CLEANUP_INFO();
	}
}}
