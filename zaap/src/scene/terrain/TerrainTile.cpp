﻿#include "TerrainTile.h"

#include "Terrain.h"
#include <util/Console.h>
#include <graphics/mesh/Mesh.h>
#include <graphics/API/Context.h>
#include <graphics/Renderer.h>

namespace zaap { namespace scene {

	TerrainTile::TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc, graphics::Image heightMap)
		: m_Position(position),
		m_TerrainDesc(terrainDesc),
		m_HightMap(m_TerrainDesc->VerticesPerLine * m_TerrainDesc->VerticesPerLine)
	{
		if (heightMap.getWidth() != m_TerrainDesc->VerticesPerLine || 
			heightMap.getHeight() != m_TerrainDesc->VerticesPerLine)
		{
			ZAAP_ALERT("TerrainTile: given heightMap has a different size than specified in the TERRAIN_DESC");
			makeFlat(m_TerrainDesc->DefaultHeight);
			return;
		}

		uint size = m_TerrainDesc->VerticesPerLine;

		for (uint y = 0; y < size; y++)
		{
			for (uint x = 0; x < size; x++) {
				m_HightMap[x + y * size] = calculateHeight(heightMap.getColor(x, y));
			}
		}

		createVertexBuffer();
	}
	TerrainTile::TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc)
		: m_Position(position),
		m_TerrainDesc(m_TerrainDesc),
		m_HightMap(m_TerrainDesc->VerticesPerLine * m_TerrainDesc->VerticesPerLine)
	{
		makeFlat(m_TerrainDesc->DefaultHeight);
		
		createVertexBuffer();
	}

	TerrainTile::~TerrainTile() {}

	//
	// GameLoop
	//
	void TerrainTile::render()
	{
		graphics::Renderer::Render(this);
	}

	math::Mat4 TerrainTile::getTransformationMatrix() const
	{
		return math::CreateTransformationMatrix(math::Vec3(m_Position.X, 0, m_Position.Y), math::Vec3(0, 0, 0), math::Vec3(1, 1, 1));
	}
	graphics::API::VertexBuffer* TerrainTile::getVertexBuffer() const
	{
		return m_VBuffer;
	}

	//
	// Texture Stuff
	//
	void TerrainTile::setTexture(graphics::Texture2D* texture, uint index)
	{
		if (index >= 4) return;
		m_Textures[index] = texture;
	}
	graphics::Texture2D* TerrainTile::getTexture(uint index) const
	{
		if (index >= 4) return nullptr;
		return m_Textures[index];
	}
	void TerrainTile::setTextureMap(graphics::Texture2D* textureMap)
	{
		m_TextureMap = textureMap;
	}
	graphics::Texture2D* TerrainTile::getTextureMap() const
	{
		return m_TextureMap;
	}

	//
	// Util
	//
	void TerrainTile::makeFlat(float height)
	{
		uint size = m_TerrainDesc->getVertexCount();

		for (uint i = 0; i < size; i++)
		{
			m_HightMap[i] = height;
		}
	}

	float TerrainTile::calculateHeight(graphics::Color color) const
	{
		float total = color.getR() + color.getG() + color.getB();
		total /= 3.0f;
		float distance = m_TerrainDesc->HeightMax - m_TerrainDesc->HeightMin;
		if (total >= 0.5)
			total = total;
		return distance * total + m_TerrainDesc->HeightMin;
	}
	void TerrainTile::createVertexBuffer()
	{
		uint verticesPerLine = m_TerrainDesc->VerticesPerLine;

		std::vector<graphics::TERRAIN_VERTEX> vertices(verticesPerLine * verticesPerLine);

		//Position
		math::Vec3 position;
		float distance = m_TerrainDesc->MeshSize / (verticesPerLine - 1);
		
		//TexMap
		math::Vec2 texMapCoord;
		float texMapDistance = 1.0f / verticesPerLine;

		//TexCoord
		math::Vec2 texCoord;
		float ya;
		uint x;
		for (uint y = 0; y < verticesPerLine; y++)
		{
			ya = y * distance;
			for (x = 0; x < verticesPerLine; x++)
			{
				position = math::Vec3(x * distance, m_HightMap[x + y * verticesPerLine], ya);
				texMapCoord = math::Vec2(x * texMapDistance, y * texMapDistance);
				texCoord = math::Vec2((float)(x % 2), (float)(y % 2));

				graphics::TERRAIN_VERTEX v = graphics::TERRAIN_VERTEX(position, math::Vec3(0.0f, 1.0f, 0.0f), texMapCoord, texCoord);
				vertices[x + y * verticesPerLine] = v;
			}
		}
		
		std::vector<uint> indices;
		// c0   c1
		//
		// c2   c3
		uint c0, c1, c2, c3;
		for (uint y = 0; y < verticesPerLine - 1; y++)
		{
			for (x = 0; x < verticesPerLine - 1; x++)
			{
				c0 = (x    ) + (y    ) * verticesPerLine;
				c1 = (x + 1) + (y    ) * verticesPerLine;
				c2 = (x    ) + (y + 1) * verticesPerLine;
				c3 = (x + 1) + (y + 1) * verticesPerLine;
				
				// c0, c2, c1
				indices.push_back(c0);
				indices.push_back(c2);
				indices.push_back(c1);

				// c2, c3, c1
				indices.push_back(c2);
				indices.push_back(c3);
				indices.push_back(c1);
			}
		}

		m_VBuffer = graphics::API::Context::GetLoader()->loadVBuffer(
			&vertices[0], sizeof(graphics::TERRAIN_VERTEX), vertices.size(), &indices[0], indices.size());
	}
}}
