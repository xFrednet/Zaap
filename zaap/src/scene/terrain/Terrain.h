﻿#pragma once

#include <Common.h>
#include <Types.h>
#include <graphics/Bitmap.h>
#include "TerrainTile.h"

namespace zaap { namespace scene {
	
	struct ZAAP_API TERRAIN_DESC
	{
		float HeightMin;
		float HeightMax;
		float DefaultHeight;
		float MeshSize;
		uint VerticesPerLine;

		TERRAIN_DESC();
		TERRAIN_DESC(float heightMin, float heightMax, float defaultHeight, float meshSize, uint verticesPerLine);

		void setupForLowPoly();

		uint getVertexCount(void) const;

	};

	class ZAAP_API Terrain
	{
	private:
		String m_Folder;
		TERRAIN_DESC m_TerrainDesc;
		std::vector<TerrainTile*> m_TerrainTiles;
	public:
		Terrain(String folder, TERRAIN_DESC terrainDesc);
	};

}}
