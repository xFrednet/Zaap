#pragma once

#include <Common.h>
#include <Types.h>
#include <graphics/Image.h>
#include <graphics/API/VertexBuffer.h>
#include <graphics/API/Texture2D.h>

namespace zaap { namespace scene {
	
	struct ZAAP_API TERRAIN_DESC
	{
		float HeightMin;
		float HeightMax;
		float DefaultHeight;
		float MeshSize;
		uint VerticesPerLine;
		uint VerticesPerTexture;

		TERRAIN_DESC();
		TERRAIN_DESC(float heightMin, float heightMax, float defaultHeight, float meshSize, uint verticesPerLine, uint verticesPerTexture);

		void setupForLowPoly();

		uint getVertexCount(void) const;

	};

	class ZAAP_API Terrain
	{
	private:
		TERRAIN_DESC m_TerrainDesc;

		//Mesh
		std::vector<float> m_HeightMap;
		graphics::API::VertexBuffer *m_VBuffer;
		graphics::API::Texture2D *m_Texture;

		void initHeightMap(String heightMapFile);
		float getHeight(graphics::Color color) const;
		math::Vec3 calcualteNormal(uint vertexX, uint vertexY) const;

	public:
		Terrain(String folder, TERRAIN_DESC terrainDesc);
		~Terrain();

		//Util
		void init(String folder);
		void initTexture(String folder);
		void initBuffers();
		void cleanup();

		//getters
		TERRAIN_DESC getTerrainDesc() const;
		graphics::API::VertexBuffer* getVertexBuffer() const;
		graphics::API::Texture2D* getTexture() const;

		float getVertexHeight(uint vertexX, uint vertexY) const;

		//game loop methods
		void update();
		void render();
	};

}}
