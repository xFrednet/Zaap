#include "MeshManager.h"

#include <util/Log.h>

namespace zaap { namespace graphics {
	
	std::map<String, MeshManager::ZA_MESHMANAGER_MESH_INFO> MeshManager::s_MeshMap;

	void MeshManager::Add(const Mesh& mesh)
	{
		if (Contains(mesh))
		{
			ZA_ALERT("This manager already contains a Mesh with the name: \"", mesh.getName(), "\"");
			return;
		}

		ZA_MESHMANAGER_MESH_INFO newMeshInfo;
		
		newMeshInfo.Mesh = mesh;
		newMeshInfo.UseCount = 1; //This is set to 1 because the added Mesh will be used too.

		s_MeshMap[mesh.getName()] = newMeshInfo;

		ZA_INFO("added: \"", mesh.getName(), "\"");
	}

	void MeshManager::ReleasedMesh(const Mesh& mesh)
	{
		//null check
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(mesh.getName())) == s_MeshMap.end())
			return;

		it->second.UseCount--;
		if (it->second.UseCount == 0)
		{
			s_MeshMap.erase(it);
		}
	}

	void MeshManager::RemoveMesh(const Mesh& mesh)
	{
		RemoveMesh(mesh.getName());
	}

	void MeshManager::RemoveMesh(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) != s_MeshMap.end())
			s_MeshMap.erase(it);
	}

	Mesh MeshManager::Get(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) == s_MeshMap.end())
			return Mesh();
		
		it->second.UseCount++;

		return it->second.Mesh;
	}

	uint MeshManager::GetUseCount(const Mesh& mesh)
	{
		if (mesh.getName() != "NULL")
			return GetUseCount(mesh.getName());

		return 0;
	}

	uint MeshManager::GetUseCount(const String& name)
	{
		std::map<String, ZA_MESHMANAGER_MESH_INFO>::iterator it;
		if ((it = s_MeshMap.find(name)) != s_MeshMap.end())
			return it->second.UseCount;

		return 0;
	}

	bool MeshManager::Contains(const Mesh& mesh)
	{
		if (mesh.getName() != "NULL")
			return Contains(mesh.getName());

		return false;
	}

	bool MeshManager::Contains(const String& name)
	{
		return s_MeshMap.find(name) != s_MeshMap.end();
	}

	void MeshManager::Cleanup()
	{
		s_MeshMap.clear();

		ZA_LOG_CLEANUP();
	}
}}
