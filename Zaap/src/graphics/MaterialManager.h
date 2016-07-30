#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Material.h>
#include <map>

namespace zaap { namespace graphics {
	
	class ZAAP_API MaterialManager
	{
	private:
		static std::map<String, Material*> s_Materials;
	public:
		static Material* Add(String name, Material *material);
		static Material* Get(const String const &name);

		static bool Contains(const String const &name);
		static void Cleanup();
	};
		
}}
