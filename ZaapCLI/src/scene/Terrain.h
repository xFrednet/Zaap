#pragma once

#include <ZaapCLI.h>

#include <scene/terrain/Terrain.h>

#include <maths/Vector2.h>

namespace ZaapCLI {

	struct TERRAIN_DESC {
		float HeightMin;
		float HeightMax;
		float DefaultHeight;
		float VertexSpacing;
		uint VerticesPerTexture;
		uint MaxVerticesPerTerrainTile;

		TERRAIN_DESC();
		TERRAIN_DESC(float heightMin, float heightMax, float defaultHeight, float vertexSpacing, uint verticesPerTexture);

		void setup();
	};

	public ref class Terrain : public ManagedClass<zaap::scene::Terrain>
	{
	private:
	public:
		Terrain(System::String^ folder, TERRAIN_DESC terrainDesc);

		//Util
		void cleanup();

		//getters
		TERRAIN_DESC getTerrainDesc();
		//graphics::API::Texture2D* getTexture(uint texture) const;

		float getMinHeight();
		float getMaxHeight();

		float getHorizontalSize();
		float getVerticalSize();
		uint getVCountHorizontal();
		uint getVCountVertical();

		//HeightMap
		float getVertexHeight(uint vertexX, uint vertexY);
		float getHeight(Vector2^ point);

		//game loop methods
		void update();
		void render();

		//render
		void bindTextures();
	};
}
