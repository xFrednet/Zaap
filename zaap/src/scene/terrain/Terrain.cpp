#include "Terrain.h"
#include <util/Console.h>
#include <graphics/TextureManager.h>

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

	TERRAIN_DESC::TERRAIN_DESC(float heightMin, float heightMax, float defaultHeight, float meshSize, uint verticesPerLine)
		: HeightMin(heightMin),
		HeightMax(heightMax),
		DefaultHeight(defaultHeight),
		MeshSize(meshSize),
		VerticesPerLine(verticesPerLine)
	{
	}

	void TERRAIN_DESC::setupForLowPoly()
	{
		HeightMin = -10.0f;
		HeightMax = 50.0f;
		DefaultHeight = 0.0f;
		MeshSize = 100.0f;
		VerticesPerLine = 50;
	}

	uint TERRAIN_DESC::getVertexCount() const
	{
		return VerticesPerLine * VerticesPerLine;
	}

	//
	// Terrain class
	//
	Terrain::Terrain(String folder, TERRAIN_DESC terrainDesc)
	{
		m_Folder = folder;
		m_TerrainDesc = terrainDesc;

		// TODO add general test method
		String heightMapPath = String(m_Folder + "\\heightMap.png");
		if (FILE *file = fopen(heightMapPath.c_str(), "r"))
		{
			fclose(file);
			m_HeightMap = graphics::Image(heightMapPath.c_str());
		} else
		{
			ZAAP_ALERT("Terrain: the given folder has no heightMap.");
		}

		String texMapPath = String(m_Folder + "\\textureMap.png");
		if (FILE *file = fopen(heightMapPath.c_str(), "r"))
		{
			fclose(file);
			m_TextureMap = graphics::Image(texMapPath.c_str());
		} else
		{
			ZAAP_ALERT("Terrain: the given folder has no TextureMap.");
		}

		loadTerrainTile(0, 0);
		loadTerrainTile(1, 0);
		loadTerrainTile(0, 1);
		loadTerrainTile(1, 1);
	}

	void Terrain::loadTerrainTile(uint tileX, uint tileY)
	{
		uint imageSize = m_TerrainDesc.VerticesPerLine;
		uint imageX = tileX * imageSize;
		uint imageY = tileY * imageSize;

		math::Vec2 position(tileX * m_TerrainDesc.MeshSize, tileY * m_TerrainDesc.MeshSize);
		TerrainTile tile(position, &m_TerrainDesc, m_HeightMap.getSubMap(imageX, imageY, imageSize, imageSize));

		tile.setTextureMap(graphics::TextureManager::LoadTexture2D("Temp", m_TextureMap.getSubMap(tileX * 100, tileY * 100, 100, 100)));

		if (graphics::TextureManager::Contains("terrainTexture0"))
		{
			graphics::TextureManager::LoadTexture2D("terrainTexture0", String(m_Folder + "\\texture_0.jpg"));
			graphics::TextureManager::LoadTexture2D("terrainTexture1", String(m_Folder + "\\texture_1.jpg"));
			graphics::TextureManager::LoadTexture2D("terrainTexture2", String(m_Folder + "\\texture_2.jpg"));
			graphics::TextureManager::LoadTexture2D("terrainTexture3", String(m_Folder + "\\texture_3.jpg"));
		}
		tile.setTexture((graphics::Texture2D*)graphics::TextureManager::GetTexture("terrainTexture0"), 0);
		tile.setTexture((graphics::Texture2D*)graphics::TextureManager::GetTexture("terrainTexture1"), 1);
		tile.setTexture((graphics::Texture2D*)graphics::TextureManager::GetTexture("terrainTexture2"), 2);
		tile.setTexture((graphics::Texture2D*)graphics::TextureManager::GetTexture("terrainTexture3"), 3);

		m_TerrainTiles.push_back(tile);
	}

	//
	// Gameloop Methods
	//
	void Terrain::update()
	{
	}
	void Terrain::render()
	{
		for (uint i = 0; i < m_TerrainTiles.size(); i++)
		{
			m_TerrainTiles[i].render();
		}
	}
}}

