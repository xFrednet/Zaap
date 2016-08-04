#include "TerrainTile.h"

#include "Terrain.h"

namespace zaap { namespace scene {
	

	TerrainTile::TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc, graphics::Bitmap heightMap)
		: m_Position(position),
		m_TerrainDesc(terrainDesc),
		m_HightMap(nullptr)
	{
		
	}

	TerrainTile::TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc)
		: m_Position(position),
		m_TerrainDesc(terrainDesc),
		m_HightMap(nullptr)
	{
		m_HightMap = new float[terrainDesc->getVertexCount()];

		memset(m_HightMap, terrainDesc->DefaultHeight, terrainDesc->getVertexCount() * sizeof(float));
			
	}

	TerrainTile::~TerrainTile()
	{
		if (m_HightMap)
			delete[] m_HightMap;
	}

	
}}