#include "TerrainPart.h"

#include "Terrain.h"

//
// Terrain
//
namespace zaap { namespace scene {

	TerrainPart::TerrainPart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical)
		: m_VertexX(vertexX),
		m_VertexY(vertexY),
		m_VCountHorizontal(vCountHorizontal),
		m_VCountVertical(vCountVertical)
	{
	}

	TerrainPart::~TerrainPart() {}

	//
	// Creation
	//
	TerrainPart* TerrainPart::CreateTerrainPart(uint vertexX, uint vertexY, uint width, uint height, Terrain* terrain)
	{
		uint vCount = width * height;
		if (vCount > terrain->getTerrainDesc().MaxVerticesPerTerrainTile)
		{
			return new TerrainTreePart(vertexX, vertexY, width, height, terrain);
		} else
		{
			return new TerrainTreeEndPart(vertexX, vertexY, width, height, terrain);
		}
	}

	//
	// Getters
	//
	uint TerrainPart::getVCountHorizontal() const
	{
		return m_VCountHorizontal;
	}
	uint TerrainPart::getVCountVertical() const
	{
		return m_VCountVertical;
	}
	uint TerrainPart::getVCount() const
	{
		return m_VCountHorizontal * m_VCountVertical;
	}

	void TerrainPart::cleanup() {}
}}

//
// TerrainTreePart
//
namespace zaap { namespace scene {

	TerrainTreePart::TerrainTreePart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain)
		: TerrainPart(vertexX, vertexY, vCountHorizontal, vCountVertical)
	{
		uint horizontal = m_VCountHorizontal;
		uint vertical = m_VCountVertical;
		uint centerX = horizontal / 2;
		uint centerY = vertical / 2;

		uint lx, ly;
		uint vx, vy;
		uint width, height;
		for (ly = 0; ly < 2; ly++)
		{
			//height && vy Value
			vy = m_VertexX + (centerY * (ly == 1));
			height = vertical / 2 + ((vertical % 2) * (ly == 1)); //Adds 1 if ((ly == 1) && (m_VCountVertical % 2 == 1)) 

			for (lx = 0; lx < 2; lx++)
			{
				//width && vx
				vx = m_VertexY + (centerX * (lx == 1));
				width = horizontal / 2 + ((horizontal % 2) * (lx == 1));

				m_Members[lx + ly * 2] = CreateTerrainPart(vx, vy, width, height, terrain);
			}
		}
	}

	void TerrainTreePart::cleanup()
	{
		for (uint i = 0; i < 4; i++)
		{
			if (m_Members[i])
			{
				m_Members[i]->cleanup();
				delete m_Members[i];
				m_Members[i] = nullptr;
			}
		}

	}

	void TerrainTreePart::render()
	{
		for (uint i = 0; i < 4; i++)
			if (m_Members[i])
				m_Members[i]->render();
	}
}}

//
// TerrainTreeEndPart
//
namespace zaap { namespace scene{

	TerrainTreeEndPart::TerrainTreeEndPart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain)
		: TerrainPart(vertexX, vertexY, 
			((vertexX + vCountHorizontal + 1) < terrain->getVCountHorizontal()) ? (vCountHorizontal + 1) : vCountHorizontal,
			((vertexY + vCountVertical + 1) < terrain->getVCountVertical()) ? (vCountVertical + 1) : vCountVertical)
		//Adds one to the width and height because the End tiles have to overlap. 
		//However the values are kept the same if they reach the edge because there is no tile to overlap.
	{
		std::vector<graphics::TERRAIN_VERTEX> vertices(getVCount());

		uint width = m_VCountHorizontal;
		uint height = m_VCountVertical;
		uint terrainWidth = terrain->getVCountHorizontal();

		uint x, y;
		uint xa, ya;
		for (y = 0; y < height; y++)
		{
			ya = m_VertexY + y;
			for (x = 0; x < width; x++)
			{
				xa = m_VertexX + x;
				vertices[x + y * width] = terrain->m_Vertices[xa + ya * terrainWidth];
			}
		}

		// c0  c3
		//
		// c1  c2
		uint c0, c1, c2, c3;
		std::vector<uint> indices;
		for (y = 0; y < height - 1; y++)
		{
			for (x = 0; x < width - 1; x++)
			{
				c0 = (x    ) + (y    ) * m_VCountHorizontal;
				c1 = (x    ) + (y + 1) * m_VCountHorizontal;
				c2 = (x + 1) + (y + 1) * m_VCountHorizontal;
				c3 = (x + 1) + (y    ) * m_VCountHorizontal;

				// c0, c1, c2
				indices.push_back(c0);
				indices.push_back(c1);
				indices.push_back(c2);

				// c0, c2, c3
				indices.push_back(c0);
				indices.push_back(c2);
				indices.push_back(c3);
			}
		}

		m_VBuffer = graphics::API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(graphics::TERRAIN_VERTEX), vertices.size(), &indices[0], indices.size());
	}

	void TerrainTreeEndPart::render()
	{
		m_VBuffer->draw();
	}
}}