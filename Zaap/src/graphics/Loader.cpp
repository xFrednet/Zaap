#include "Loader.h"

#include "util/Console.h"

namespace zaap { namespace graphics {

	//
	// COLOR
	//
	COLOR::COLOR()
	{
		R = 0.0f;
		G = 0.0f;
		B = 0.0f;
		A = 1.0f;
	}
	COLOR::COLOR(float r, float g, float b, float a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

	//
	// VERTEX
	//
	VERTEX::VERTEX()
	{}

	VERTEX::VERTEX(math::Vec3 vertex, math::Vec2 texCoords, math::Vec3 normal)
		: Position(vertex), 
		TexCoord(texCoords),
		Normal(normal)
	{
	}

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
	Mesh Loader::loadOBJFile(String file)
	{
		std::ifstream fileStream;
		fileStream.open(file);

		//error check
		if (!fileStream.is_open())
		{
			ZAAP_ERROR(String("Loader: could not open: " + file));
			return Mesh();
		}

		//util values
		String line;
		std::vector<math::Vec3> position_unsorted;
		std::vector<math::Vec2> texCoords_unsorted;
		std::vector<math::Vec3> normals_unsorted;

		std::vector<uint> position_indices;
		std::vector<uint> texCoords_indices;
		std::vector<uint> normals_indices;
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
			if (startWith(line, "vt", 2))
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

			//indices
			if (startWith(line, "f", 1))
			{
				std::vector<std::string> splstr = split(line, " ");
				for (uint i = 1; i < splstr.size(); i++)
				{
					str = split(splstr[i], "/");
					int vertexIndex = atoi(str[0].c_str()) - 1;
					int textureIndex = atoi(str[1].c_str()) - 1;
					int normalIndex = atoi(str[2].c_str()) - 1;
					int currentIndex = vecContains(position_indices, vertexIndex);

					if (currentIndex == -1) {
						position_indices.push_back(vertexIndex);
						texCoords_indices.push_back(textureIndex);
						normals_indices.push_back(normalIndex);
						indices.push_back(position_indices.size() - 1);
					} else
					{
						if (normals_indices[currentIndex] == textureIndex)
						{
							indices.push_back(currentIndex);
						} else
						{
							position_indices.push_back(vertexIndex);
							texCoords_indices.push_back(textureIndex);
							normals_indices.push_back(normalIndex);
							indices.push_back(position_indices.size() - 1);
						}
					}
				}
			}
		}

		//sort
		uint size = position_indices.size();
		std::vector<VERTEX> vertices(size);

		for (uint i = 0; i < size; i++)
		{
			vertices[i] = VERTEX(position_unsorted[position_indices[i]], texCoords_unsorted[texCoords_indices[i]], normals_unsorted[normals_indices[i]]);
		}

		return this->loadMesh(&vertices[0], vertices.size(), &indices[0], indices.size());
	}
}}