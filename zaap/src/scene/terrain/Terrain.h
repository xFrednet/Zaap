﻿#pragma once

#include <Common.h>
#include <Types.h>
#include <graphics/API/Texture.h>
#include <graphics/mesh/Mesh.h>
#include <scene/terrain/TerrainPart.h>

namespace zaap {namespace graphics {
	class Renderer3D;
}
}

namespace zaap { namespace scene {
	
	struct ZAAP_API TERRAIN_DESC
	{
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

	class ZAAP_API Terrain
	{
		friend class TerrainPart;
		friend class TerrainTreePart;
		friend class TerrainTreeEndPart;
	private:
		TERRAIN_DESC m_TerrainDesc;

		//Mesh
		float m_MinHeight;
		float m_MaxHeight;
		uint m_VCountHorizontal;
		uint m_VCountVertical;
		std::vector<graphics::ZA_TERRAIN_VERTEX> m_Vertices;
		graphics::API::Texture2D m_Textures[4];

		//HeightMap
		void initVertices(String heightMapFile, String texMapFile);
		float calculateHeightFromColor(graphics::Color color) const;
		Vec3 calcualteNormal(uint vertexX, uint vertexY) const;

		//Rendering
		TerrainPart* m_ParrentNode;
	public:
		Terrain(String folder, TERRAIN_DESC terrainDesc);

		//Util
		void init(String folder);
		void initTexture(String folder);
		void cleanup();

		//getters
		TERRAIN_DESC getTerrainDesc() const;
		graphics::API::Texture2D getTexture(uint texture) const;

		float getMinHeight() const;
		float getMaxHeight() const;

		float getHorizontalSize() const;
		float getVerticalSize() const;
		uint getVCountHorizontal() const;
		uint getVCountVertical() const;

		//HeightMap
		float getVertexHeight(uint vertexX, uint vertexY) const;
		float getHeight(Vec2 point);

		//game loop methods
		void update();
		void render(graphics::Renderer3D* renderer) const;
		
		//render
		void bindTextures() const;
	};

}}
