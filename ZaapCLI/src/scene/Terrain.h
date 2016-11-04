#pragma once

#include <ZaapCLI.h>

#include <scene/terrain/Terrain.h>

#include <maths/Vector2.h>

namespace ZaapCLI {

	public ref struct TerrainOptions : public ManagedClass<zaap::scene::TERRAIN_DESC> {
	public:
		ZA_CLI_VALUE(float, HeightMin, heightMin);
		ZA_CLI_VALUE(float, HeightMax, heightMax);
		ZA_CLI_VALUE(float, DefaultHeight, defaultHeight);
		ZA_CLI_VALUE(float, VertexSpacing, vertexSpacing);
		ZA_CLI_VALUE(uint, VerticesPerTexture, verticesPerTexture);
		ZA_CLI_VALUE(uint, MaxVerticesPerTerrainTile, maxVerticesPerTerrainTile);
		
		TerrainOptions();
		TerrainOptions(zaap::scene::TERRAIN_DESC* instance);

		void setup();
	};

	static zaap::scene::TERRAIN_DESC to_CPP_TERRAIN_DESC(TerrainOptions^ terrainDesc);
	static TerrainOptions^ to_CLI_TERRAIN_DESC(zaap::scene::TERRAIN_DESC terrainDesc);

	public ref class Terrain : public ManagedClass<zaap::scene::Terrain>
	{
	private:
	public:
		Terrain(System::String^ folder, TerrainOptions^ terrainDesc);

		//Util
		void cleanup();

		//getters
		TerrainOptions^ getTerrainOptions();
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
