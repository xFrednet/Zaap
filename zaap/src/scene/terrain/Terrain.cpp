#include "Terrain.h"
#include <util/Console.h>
#include <graphics/TextureManager.h>
#include <graphics/mesh/Mesh.h>
#include <graphics/API/Context.h>
#include <graphics/API/DXContext.h>
#include <graphics/Renderer.h>

namespace zaap { namespace scene {
	
	//
	// Terrain Desc
	//
	TERRAIN_DESC::TERRAIN_DESC()
		: HeightMin(0.0f),
		HeightMax(0.0f),
		DefaultHeight(0.0f),
		MeshSize(0.0f),
		VerticesPerLine(0)
	{
	}

	TERRAIN_DESC::TERRAIN_DESC(float heightMin, float heightMax, float defaultHeight, float meshSize, uint verticesPerLine, uint verticesPerTexture)
		: HeightMin(heightMin),
		HeightMax(heightMax),
		DefaultHeight(defaultHeight),
		MeshSize(meshSize),
		VerticesPerLine(verticesPerLine),
		VerticesPerTexture(verticesPerTexture)
	{
	}

	void TERRAIN_DESC::setupForLowPoly()
	{
		HeightMin = -10.0f;
		HeightMax = 50.0f;
		DefaultHeight = 0.0f;
		MeshSize = 100.0f;
		VerticesPerLine = 100;
		VerticesPerTexture = 10;
	}

	uint TERRAIN_DESC::getVertexCount() const
	{
		return VerticesPerLine * VerticesPerLine;
	}

	
	//
	// Terrain class
	//
	Terrain::Terrain(String folder, TERRAIN_DESC terrainDesc)
		: m_TerrainDesc(terrainDesc),
		m_HeightMap(m_TerrainDesc.getVertexCount())
	{
		init(folder);
	}
	Terrain::~Terrain()
	{
	}

	//
	// Util
	//
	void Terrain::init(String folder)
	{
		initHeightMap(String(folder + "heightMap.png"));
		initTexture(folder);
		initBuffers();
	}

	void Terrain::initTexture(String folder)
	{
		m_Texture = graphics::TextureManager::LoadTexture2D("terrainTexture", folder + "texture_3.jpg");
	}

	//HeightMap
	void Terrain::initHeightMap(String heightMapFile)
	{
		if (m_HeightMap.size() != m_TerrainDesc.getVertexCount())
			m_HeightMap = std::vector<float>(m_TerrainDesc.getVertexCount());

		uint size = m_TerrainDesc.VerticesPerLine;
		graphics::Image heightMap(heightMapFile.c_str());

		//error check
		if (heightMap.getWidth() != size || heightMap.getHeight() != size)
		{
			if (heightMap.getWidth() == 0 || heightMap.getHeight() == 0)
			{
				ZAAP_ERROR("Terrain: The given heightMap does not exists");
			} else
			{
				ZAAP_ERROR("Terrain: The given heightMap has the wrong size");
			}
			return;
		}

		uint x, y;
		for (y = 0; y < size; y++)
		{
			for (x = 0; x < size; x++)
			{
				m_HeightMap[x + y * size] = getHeight(heightMap.getColor(x, y));
			}
		}
	}
	float Terrain::getHeight(graphics::Color color) const
	{
		float total = color.R + color.G + color.B;
		float distance = m_TerrainDesc.HeightMax - m_TerrainDesc.HeightMin;
		total /= 3.0f;
		return distance * total + m_TerrainDesc.HeightMin;
	}
	math::Vec3 Terrain::calcualteNormal(uint vX, uint vY) const
	{
		math::Vec3 normal(0.0f, 2.0f, 0.0f);

		//x Value
		{
			if (vX == 0)
				normal.X = getVertexHeight(vX, vY) - getVertexHeight(vX + 1, vY);
			else if (vX == m_TerrainDesc.VerticesPerLine - 1) 
				normal.X = getVertexHeight(vX - 1, vY) - getVertexHeight(vX, vY);
			else //vertexX < m_TerrainDesc.VerticesPerLine - 1
				normal.X = getVertexHeight(vX - 1, vY) - getVertexHeight(vX + 1, vY);
			
		}
		{
			if (vY == 0)
				normal.Z = getVertexHeight(vX, vY) - getVertexHeight(vX, vY + 1);
			else if (vY == m_TerrainDesc.VerticesPerLine - 1)
				normal.Z = getVertexHeight(vX, vY - 1) - getVertexHeight(vX, vY);
			else //vX < m_TerrainDesc.VerticesPerLine - 1
				normal.Z = getVertexHeight(vX, vY - 1) - getVertexHeight(vX, vY + 1);
		}


		normal.normalize();
		return normal;
	}

	void Terrain::initBuffers()
	{
		uint size = m_TerrainDesc.VerticesPerLine;
		std::vector<graphics::TERRAIN_VERTEX> vertices(size * size);

		float texIncrease = 1.0f / m_TerrainDesc.VerticesPerTexture;

		uint x, y;
		for (y = 0; y < size; y++)
		{
			for (x = 0; x < size; x++)
			{
				vertices[x + y * size].Position = math::Vec3((float)x, m_HeightMap[x + y * size], (float)y);
				vertices[x + y * size].Normal = calcualteNormal(x, y);
				vertices[x + y * size].TexCoord = math::Vec2(x * texIncrease, y * texIncrease);
			}
		}

		// c0  c3
		//
		// c1  c2
		uint c0, c1, c2, c3;
		std::vector<uint> indices;
		for (y = 0; y < size - 1; y++)
		{
			for (x = 0; x < size - 1; x++)
			{
				c0 = (x    ) + (y    ) * size;
				c1 = (x    ) + (y + 1) * size;
				c2 = (x + 1) + (y + 1) * size;
				c3 = (x + 1) + (y    )* size;
				
				// c0, c1, c2
				indices.push_back(c0);
				indices.push_back(c1);
				indices.push_back(c2);

				// c0, c2, c3
				indices.push_back(c0);
				indices.push_back(c2);
				indices.push_back(c3);

			}
		}

		m_VBuffer = graphics::API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(graphics::TERRAIN_VERTEX), vertices.size(), &indices[0], indices.size());

	}

	void Terrain::cleanup()
	{
	}

	TERRAIN_DESC Terrain::getTerrainDesc() const
	{
		return m_TerrainDesc;
	}

	graphics::API::VertexBuffer* Terrain::getVertexBuffer() const
	{
		return m_VBuffer;
	}

	graphics::API::Texture2D* Terrain::getTexture() const
	{
		return m_Texture;
	}

	float Terrain::getVertexHeight(uint vertexX, uint vertexY) const
	{
		uint size = m_TerrainDesc.VerticesPerLine;
		
		if (vertexX >= size || vertexY >= size)
			return 0.0f;

		return m_HeightMap[vertexX + vertexY * size];
	}

	//
	// Gameloop Methods
	//
	void Terrain::update()
	{
	}
	void Terrain::render()
	{
		graphics::Renderer::Render(this);
	}
}}

