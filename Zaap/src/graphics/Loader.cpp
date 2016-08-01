#include "Loader.h"

#include <util/Console.h>
#include <graphics/Material.h>
#include <graphics/MaterialManager.h>
#include <graphics/shader/DXShader/DXMaterialShader.h>
#include "mesh/TexturedMesh.h"
#include "mesh/MaterialMesh.h"

namespace zaap { namespace graphics {

	//
	// Loader
	//
	Loader::Loader(void)
	{}

	bool startWith(std::string str, std::string str2, int count)
	{
		for (int i = 0; i < count; i++)
		{
			if (str[i] != str2[i]) return false;
		}
		return true;
	}
	std::vector<std::string> split(std::string str, std::string delimiter)
	{
		std::vector<std::string> returnStr;

		size_t pos = 0;
		while ((pos = str.find(delimiter)) != std::string::npos)
		{
			returnStr.push_back(str.substr(0, pos));
			str.erase(0, pos + delimiter.length());
		}
		returnStr.push_back(str);
		return returnStr;
	}
	int vecContains(std::vector<uint> &vec, int &value)
	{
		for (unsigned int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == value) return i;
		}
		return -1;
	}
	
	Mesh* Loader::loadOBJFile(String name, String file, bool isTMesh)
	{
		Mesh* rMesh = nullptr;
		Material materials[8];
		uint materialCount = 0;
		std::ifstream fileStream;
		fileStream.open(file);

		//error check
		if (!fileStream.is_open())
		{
			ZAAP_ERROR(String("Loader: could not open: " + file));
			return nullptr;
		}

		//util values
		String line;
		std::vector<math::Vec3> position_unsorted;
		std::vector<math::Vec2> texCoords_unsorted;
		std::vector<math::Vec3> normals_unsorted;

		int currentMaterial = 0;
		int textureIndex = 0;
		std::vector<uint> position_indices;
		std::vector<uint> texCoords_indices;
		std::vector<uint> normals_indices;
		std::vector<uint> material;
		std::vector<uint> indices;

		std::vector<std::string> str;

		while (!fileStream.eof())
		{
			std::getline(fileStream, line);

			//vertices
			if (startWith(line, "v ", 2))
			{
				str = split(line, " ");

				position_unsorted.push_back(
					math::Vec3((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str())));

				continue;
			}
			//textureCoords
			if (startWith(line, "vt", 2) && isTMesh)
			{
				str = split(line, " ");
				texCoords_unsorted.push_back(math::Vec2((float)atof(str[1].c_str()), (float)atof(str[2].c_str())));

				continue;
			}
			//normals
			if (startWith(line, "vn", 2))
			{
				str = split(line, " ");

				normals_unsorted.push_back(
					math::Vec3((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str())));

				continue;
			}

			if (startWith(line, "usemtl", 6) && !isTMesh)
			{
				if (materialCount >= 8) continue;
				
				str = split(line, " ");
				materials[materialCount] = *MaterialManager::Get(str[1]);
				materials[materialCount].Color.R = 1.0f;
				if (&materials[materialCount] == nullptr)
				{
					ZAAP_ALERT("Loader: requested material is null name: \"" + str[1] + "\" current file: " + file);
					continue;
				}
				currentMaterial = materialCount;
				materialCount++;
			}

			//indices
			if (startWith(line, "f", 1))
			{
				std::vector<std::string> splstr = split(line, " ");
				for (uint i = 1; i < splstr.size(); i++)
				{
					str = split(splstr[i], "/");
					int vertexIndex = atoi(str[0].c_str()) - 1;
					if (isTMesh) textureIndex = atoi(str[1].c_str()) - 1;
					int normalIndex = atoi(str[2].c_str()) - 1;
					int currentIndex = vecContains(position_indices, vertexIndex);

					if (currentIndex == -1) {
						position_indices.push_back(vertexIndex);
						if (isTMesh) texCoords_indices.push_back(textureIndex);
						if (!isTMesh) material.push_back(currentMaterial);
						normals_indices.push_back(normalIndex);
						indices.push_back(position_indices.size() - 1);
					} else
					{
						if ((!isTMesh || texCoords_indices[currentIndex] == textureIndex) && 
							normals_unsorted[normals_indices[currentIndex]].dot(normals_unsorted[normalIndex]) >= 0.9f &&
							(isTMesh || material[currentIndex] == currentMaterial))
						{
							indices.push_back(currentIndex);
						} else
						{
							position_indices.push_back(vertexIndex);
							if (isTMesh) texCoords_indices.push_back(textureIndex);
							if (!isTMesh) material.push_back(currentMaterial);
							normals_indices.push_back(normalIndex);
							indices.push_back(position_indices.size() - 1);
						}
					}
				}
			}
		}

		//sort
		API::VertexBuffer* vBuffer = nullptr;
		uint size = position_indices.size();
		if (isTMesh)
		{
			std::vector<TEXTURE_VERTEX> vertices(size);

			for (uint i = 0; i < size; i++)
			{
				vertices[i] = TEXTURE_VERTEX(position_unsorted[position_indices[i]], normals_unsorted[normals_indices[i]], texCoords_unsorted[texCoords_indices[i]]);
			}
			
			vBuffer = this->loadVBuffer(&vertices[0], sizeof(TEXTURE_VERTEX), size, &indices[0], indices.size());

			rMesh = new TexturedMesh(name, vBuffer, nullptr);
		} else
		{
			std::vector<MATERIAL_VERTEX> vertices(size);

			for (uint i = 0; i < size; i++)
			{
				vertices[i] = MATERIAL_VERTEX(position_unsorted[position_indices[i]], normals_unsorted[normals_indices[i]], material[i]);
			}

			vBuffer = this->loadVBuffer(&vertices[0], sizeof(MATERIAL_VERTEX), size, &indices[0], indices.size());

			rMesh = new MaterialMesh(name, vBuffer, materials, materialCount);
		}

		ZAAP_INFO(String("Loader: loaded ") + file + " as a " + (isTMesh ? "TexturedMesh" : "MaterialMesh"));

		return rMesh;
	}

	void Loader::loadMTLFile(String file) const
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
			ZAAP_ERROR(String("Loader: could not open: " + file));
			return;
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
			if (startWith(line, "newmtl", 6))
			{
				if (commit)
				{
					if (!MaterialManager::Contains(name))
						MaterialManager::Add(name, new Material(color, reflectivity));

				} else commit = true;
					
				name = split(line, " ")[1];
			}

			if (startWith(line, "kd ", 3))
			{
				str = split(line, " ");
				color = Color((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str()));
			}

			if (startWith(line, "kd ", 3))
			{
				str = split(line, " ");
				reflectivity = (float)atof(str[1].c_str());
			}
		}

		if (!MaterialManager::Contains(name))
			MaterialManager::Add(name, new Material(color, reflectivity));

	}
}}
