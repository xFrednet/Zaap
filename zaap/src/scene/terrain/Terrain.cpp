#include "Terrain.h"

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
		MeshSize = 50.0f;
		VerticesPerLine = 50;
	}

	uint TERRAIN_DESC::getVertexCount() const
	{
		return VerticesPerLine * VerticesPerLine;
	}
}}

