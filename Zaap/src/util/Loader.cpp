#include "Loader.h"

#include <util/Log.h>
#include <graphics/Material.h>
#include <graphics/MaterialManager.h>
#include "StringUtil.h"
#include <graphics/shader/Shader.h>

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

	graphics::Mesh Loader::LoadOBJFile(String file)
	{
		using namespace graphics;
		using namespace std;

		Material materials[ZA_SHADER_MATERIAL_COUNT];
		uint materialCount = 0;
		ifstream fileStream;
		fileStream.open(file);

		//error check
		if (!fileStream.is_open())
		{
			ZA_ERROR(String("could not open: " + file));
			return Mesh("NULL", nullptr);
		}

		//util values
		String line;
		vector<Vec3> position_unsorted;
		vector<Vec2> texCoords_unsorted;
		vector<Vec3> normals_unsorted;

		int currentMaterial = 0;
		int textureIndex, vertexIndex, normalIndex, currentIndex;
		vector<uint> position_indices;
		vector<uint> texCoords_indices;
		vector<uint> normals_indices;
		vector<uint> material;
		vector<uint> indices;

		vector<string> str;

		while (!fileStream.eof())
		{
			getline(fileStream, line);

			//vertices
			if (StringUtil::StartsWith(line, "v "))
			{
				str = StringUtil::Split(line, " ");

				position_unsorted.push_back(
					Vec3((float)atof(str[1].c_str()), (float)atof(str[2].c_str()), (float)atof(str[3].c_str())));

				continue;
			}
			//textureCoords
			if (StringUtil::StartsWith(line, "vt"))
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
			//material
			if (StringUtil::StartsWith(line, "usemtl"))
			{
				if (materialCount >= ZA_SHADER_MATERIAL_COUNT) continue;
				
				str = StringUtil::Split(line, " ");
				materials[materialCount] = MaterialManager::Get(str[1]);
				if (&materials[materialCount] == nullptr)
				{
					ZA_ALERT("requested material is null name: \"", str[1], "\" current file: ", file);
					continue;
				}
				currentMaterial = materialCount;
				materialCount++;
			}

			//indices
			if (StringUtil::StartsWith(line, "f"))
			{
				vector<string> splstr = StringUtil::Split(line, " ");
				for (uint i = 1; i < splstr.size(); i++)
				{
					str = StringUtil::Split(splstr[i], "/");
					vertexIndex = atoi(str[0].c_str()) - 1;
					textureIndex = atoi(str[1].c_str()) - 1;
					normalIndex = atoi(str[2].c_str()) - 1;
					currentIndex = vecContains(position_indices, vertexIndex);

					if (currentIndex == -1) {
						position_indices.push_back(vertexIndex);
						texCoords_indices.push_back(textureIndex);
						material.push_back(currentMaterial);
						normals_indices.push_back(normalIndex);
						indices.push_back(position_indices.size() - 1);
					} else
					{
						if (texCoords_indices[currentIndex] == textureIndex && 
							normals_unsorted[normals_indices[currentIndex]].dot(normals_unsorted[normalIndex]) >= 0.9f &&
							material[currentIndex] == currentMaterial)
						{
							indices.push_back(currentIndex);
						} else
						{
							position_indices.push_back(vertexIndex);
							normals_indices.push_back(normalIndex);
							texCoords_indices.push_back(textureIndex);
							material.push_back(currentMaterial);
							indices.push_back(position_indices.size() - 1);
						}
					}
				}
			}
		}

		//sort
		API::VertexBuffer vBuffer;
		{
			uint size = position_indices.size();
			vector<ZA_D_VERTEX> vertices(size);
			for (uint i = 0; i < size; i++)
			{
				vertices[i].Position = position_unsorted[position_indices[i]];
				vertices[i].Normal = normals_unsorted[normals_indices[i]];
				vertices[i].TexCoord = texCoords_unsorted[texCoords_indices[i]];
				vertices[i].Material = material[i];
			}
			vBuffer = API::VertexBufferCore::CreateVertexBuffer(sizeof(ZA_D_VERTEX), vertices.size(), indices.size(), &vertices[0], &indices[0]);
		}

		Material* newMaterials = new Material[materialCount];
		memcpy(&newMaterials[0], &materials[0], sizeof(Material) * materialCount);

		ZA_INFO("Loaded \"", file, "\"");

		return Mesh(file, vBuffer, newMaterials, materialCount);
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
			ZA_ERROR("Could not open: ", file);
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
