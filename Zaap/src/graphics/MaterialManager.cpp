#include "MaterialManager.h"
#include <util/Console.h>

namespace zaap { namespace graphics {
	
	std::map<String, Material*> MaterialManager::s_Materials;

	Material* MaterialManager::Add(String name, Material* material)
	{
		if (Contains(name))
		{
			ZAAP_ALERT("MaterialManager: The manager already contains a material with the name: " + name);
			delete material;
			return Get(name);
		}
		
		s_Materials[name] = material;

		return material;
	}
	Material* MaterialManager::Get(const String& name)
	{
		if (!Contains(name))
			return nullptr;
		
		return s_Materials[name];
	}

	bool MaterialManager::Contains(const String& name)
	{
		return s_Materials.find(name) != s_Materials.end();
	}
	void MaterialManager::Cleanup()
	{
		std::map<String, Material*>::iterator it;
		for (it = s_Materials.begin(); it != s_Materials.end(); it++)
		{
			delete it->second;
		}

		ZAAP_CLEANUP_LOG("MaterialManager");
	}
}}
