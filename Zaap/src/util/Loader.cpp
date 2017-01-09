#include "Loader.h"

#include <util/Console.h>
#include <graphics/Material.h>
#include <graphics/MaterialManager.h>
#include <graphics/mesh/TexturedMesh.h>
#include <graphics/mesh/MaterialMesh.h>

namespace zaap {

	//
	// Loader
	//
	int vecContains(std::vector<uint> &vec, int &value)
	{
		for (unsigned int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == value) return i;
		}
		return -1;
	}

	graphics::Mesh* Loader::LoadOBJFile(String name, String file, bool isTMesh)
	{
		using namespace graphics;

		Mesh* rMesh = nullptr;
		Material materials[8];
		uint materialCount = 0;
		std::ifstream fileStream;
		fileStream.open(file);

		//error check
		if (!fileStream.is_open())
		{
			ZAAP_ERROR(String("could not open: " + file));
			return nullptr;
		}

		//util values
		String line;
		std::vector<Vec3> position_unsorted;
		std::vector<Vec2> texCoords_unsorted;
		std::vector<Vec3> normals_unsorted;

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
			if (StringUtil::StartsWith(line, "v "))
			{
				str = StringUtil::Split(line, " ");

				position_unsorted.push_back(
					Vec3((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str())));

				continue;
			}
			//textureCoords
			if (StringUtil::StartsWith(line, "vt") && isTMesh)
			{
				str = StringUtil::Split(line, " ");
				texCoords_unsorted.push_back(Vec2((float)atof(str[1].c_str()), (float)atof(str[2].c_str())));

				continue;
			}
			//normals
			if (StringUtil::StartsWith(line, "vn"))
			{
				str = StringUtil::Split(line, " ");

				normals_unsorted.push_back(
					Vec3((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str())));

				continue;
			}

			if (StringUtil::StartsWith(line, "usemtl") && !isTMesh)
			{
				if (materialCount >= 8) continue;
				
				str = StringUtil::Split(line, " ");
				materials[materialCount] = MaterialManager::Get(str[1]);
				if (&materials[materialCount] == nullptr)
				{
					ZAAP_ALERT("requested material is null name: \"" + str[1] + "\" current file: " + file);
					continue;
				}
				currentMaterial = materialCount;
				materialCount++;
			}

			//indices
			if (StringUtil::StartsWith(line, "f"))
			{
				std::vector<std::string> splstr = StringUtil::Split(line, " ");
				for (uint i = 1; i < splstr.size(); i++)
				{
					str = StringUtil::Split(splstr[i], "/");
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
			std::vector<ZA_TEXTURE_VERTEX> vertices(size);

			for (uint i = 0; i < size; i++)
			{
				vertices[i] = ZA_TEXTURE_VERTEX(position_unsorted[position_indices[i]], normals_unsorted[normals_indices[i]], texCoords_unsorted[texCoords_indices[i]]);
			}
			
			vBuffer = API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(ZA_TEXTURE_VERTEX), size, &indices[0], indices.size(), ZA_SHADER_TEXTURE_SHADER);

			rMesh = new TexturedMesh(name, vBuffer, nullptr);
		} else
		{
			std::vector<ZA_MATERIAL_VERTEX> vertices(size);

			for (uint i = 0; i < size; i++)
			{
				vertices[i] = ZA_MATERIAL_VERTEX(position_unsorted[position_indices[i]], normals_unsorted[normals_indices[i]], material[i]);
			}

			vBuffer = API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(ZA_MATERIAL_VERTEX), size, &indices[0], indices.size(), ZA_SHADER_MATERIAL_SHADER);
			
			rMesh = new MaterialMesh(name, vBuffer, materials, materialCount);
		}

		ZAAP_INFO(String("loaded ") + file + " as a " + (isTMesh ? "TexturedMesh" : "MaterialMesh"));

		return rMesh;
	}

	String Loader::LoadFile(String file)
	{
		using namespace std;

		String content;
		fstream fileStream;
		fileStream.open(file);

		//error check
		if (!fileStream.is_open())
		{
			ZAAP_ERROR(String("could not open: " + file));
			return "";
		}

		//loading file
		String line;
		while (!fileStream.eof())
		{
			getline(fileStream, line);
			content += line + "\n";
		}

		return content;
	}
}
