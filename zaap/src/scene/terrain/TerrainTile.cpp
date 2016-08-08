#include "TerrainTile.h"

#include "Terrain.h"
#include <util/Console.h>
#include <graphics/mesh/Mesh.h>
#include <graphics/API/Context.h>
#include <graphics/Renderer.h>

namespace zaap { namespace scene {

	TerrainTile::TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc, graphics::Bitmap heightMap)
		: m_Position(position),
		m_TerrainDesc(terrainDesc),
		m_HightMap(nullptr)
	{
		if (heightMap.Width != m_TerrainDesc->VerticesPerLine || 
			heightMap.Height != m_TerrainDesc->VerticesPerLine)
		{
			ZAAP_ALERT("TerrainTile: given heightMap has a different size than specified in the TERRAIN_DESC");
			makeFlat(m_TerrainDesc->DefaultHeight);
			return;
		}


		uint size = m_TerrainDesc->VerticesPerLine;
		m_HightMap = new float[size * size];

		std::vector<graphics::Color> colors(size * size);
		for (uint y = 0; y < size; y++)
		{
			for (uint x = 0; x < size; x++) {
				m_HightMap[x + y * size] = calculateHeight(heightMap.getColor(x, y));
				colors[x + y * size] = heightMap.getColor(x, y);
				//m_HightMap[x + y * size] = calculateHeight(heightMap.getColor(x, y));
			}
		}

		createVertexBuffer();
	}
	TerrainTile::TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc)
		: m_Position(position),
		m_TerrainDesc(m_TerrainDesc),
		m_HightMap(nullptr)
	{
		uint size = m_TerrainDesc->getVertexCount();
		m_HightMap = new float[size];

		makeFlat(m_TerrainDesc->DefaultHeight);
		
		createVertexBuffer();
	}

	TerrainTile::~TerrainTile()
	{
		if (m_HightMap) //TODO REMOVE THIS
			delete[] m_HightMap;
	}

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
	graphics::Texture2D* TerrainTile::getTexture() const
	{
		return m_Texture;
	}
	graphics::API::VertexBuffer* TerrainTile::getVertexBuffer() const
	{
		return m_VBuffer;
	}

	//
	//
	// Setter
	void TerrainTile::setTexture(graphics::Texture2D* texture)
	{
		m_Texture = texture;
	}

	//
	// Util
	//
	void TerrainTile::makeFlat(float height)
	{
		uint size = m_TerrainDesc->getVertexCount();
		if (!m_HightMap) m_HightMap = new float[size];

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
		if (!m_HightMap)
		{
			ZAAP_ALERT("TerrainTile: Unable to create a VertexBuffer from a undefined HightMap");
			return;
		}
		uint verticesPerLine = m_TerrainDesc->VerticesPerLine;
		float distance = m_TerrainDesc->MeshSize / verticesPerLine;

		std::vector<graphics::TEXTURE_VERTEX> vertices(verticesPerLine * verticesPerLine);

		math::Vec3 position;
		float xa, ya;
		uint x;
		for (uint y = 0; y < verticesPerLine; y++)
		{
			ya = y * distance;
			for (x = 0; x < verticesPerLine; x++)
			{
				xa = x * distance;
				position = math::Vec3(xa, m_HightMap[x + y * verticesPerLine], ya);
				graphics::TEXTURE_VERTEX v = graphics::TEXTURE_VERTEX(position, math::Vec3(0.0f, 1.0f, 0.0f), math::Vec2((float)(x % 2), (float)(y % 2)));
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
			&vertices[0], sizeof(graphics::TEXTURE_VERTEX), vertices.size(), &indices[0], indices.size());
	}
}}
