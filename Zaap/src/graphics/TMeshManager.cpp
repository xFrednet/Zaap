#include "TMeshManager.h"
#include "util/Console.h"

namespace zaap { namespace graphics {
	
	std::vector<TexturedMesh> TMeshManager::s_TMeshs;

	TexturedMesh TMeshManager::AddTMesh(String name, Mesh& mesh, Texture2D* texture)
	{
		return AddTMesh(TexturedMesh(name, mesh, texture));
	}

	TexturedMesh TMeshManager::AddTMesh(TexturedMesh& tMesh)
	{
		
		if (&tMesh.getName() == nullptr)
		{
			ZAAP_ERROR("TMeshManager: submitted TMesh has no name")
		} else
		{
//This code only runs in debug mode because it could influence the performance
#ifdef ZAAP_DEBUG
			if (hasName(tMesh.getName())) {
				ZAAP_ALERT("TMeshManager: submitted TMesh has a name that is already included")
			}
#endif //ZAAP_DEBUG

			s_TMeshs.push_back(tMesh);

		}
		return tMesh;
	}

	TexturedMesh TMeshManager::GetTMesh(String name)
	{
		for (uint i = 0; i < s_TMeshs.size(); i++)
		{
			if (s_TMeshs[i].getName() == name)
				return s_TMeshs[i];
		}

		ZAAP_ALERT("TMeshManager: Requested TMesh was not found. Requested name:" + name);
		return TexturedMesh();
	}

	bool TMeshManager::hasName(String name)
	{
		for (uint i = 0; i < s_TMeshs.size(); i++)
		{
			if (s_TMeshs[i].getName() == name)
				return true;
		}
		return false;
	}
}}
