#include "MaterialManager.h"
#include <util/Console.h>
#include <util/StringUtil.h>

namespace zaap { namespace graphics {
	
	std::map<String, Material> MaterialManager::s_Materials;

	ZA_RESULT MaterialManager::LoadMTLFile(String file)
	{
		/*	newmtl Material
		Ns 96.078431
		Ka 0.000000 0.000000 0.000000
		Kd 0.597895 0.597895 0.597895 //Color
		Ks 0.666000 0.666000 0.666000 //Specular
		Ni 1.000000
		d 1.000000
		illum 2
		*/
		std::ifstream fileStream;
		fileStream.open(file);

		//error check
		if (!fileStream.is_open())
		{
			ZAAP_ERROR(String("could not open: " + file));
			return ZA_ERROR_FILE_IS_IMAGINARY;
		}

		Color color;
		float reflectivity = 0.0f;
		String name;
		bool commit = false;
		String line;
		std::vector<std::string> str;
		while (!fileStream.eof())
		{
			getline(fileStream, line);
			if (StringUtil::StartsWith(line, "newmtl"))
			{
				if (commit)
				{
					if (!Contains(name))
						Add(name, Material(color, reflectivity));

				} else
					commit = true;

				name = StringUtil::Split(line, " ")[1];
			}

			if (StringUtil::StartsWith(line, "Kd "))
			{
				str = StringUtil::Split(line, " ");
				color = Color((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str()));
			}

			if (StringUtil::StartsWith(line, "Ks "))
			{
				str = StringUtil::Split(line, " ");
				reflectivity = (float)atof(str[1].c_str());
			}
		}

		if (!Contains(name))
			Add(name, Material(color, reflectivity));

		fileStream.close();
		
		return ZA_OK;
	}

	void MaterialManager::Add(String name, Material material)
	{
		if (Contains(name))
		{
			ZAAP_ALERT("The MaterialManager already contains a Material with the name: " + name + "\"");
			return;
		}
		
		s_Materials[name] = material;

		ZAAP_INFO("added: \"" + name + "\"");
	}
	Material MaterialManager::Get(const String& name)
	{
		if (Contains(name))
			return s_Materials[name];
			
		return Material();
	}

	bool MaterialManager::Contains(const String& name)
	{
		return s_Materials.find(name) != s_Materials.end();
	}
	void MaterialManager::Cleanup()
	{
		s_Materials.clear();

		ZAAP_CLEANUP_INFO();
	}
}}
