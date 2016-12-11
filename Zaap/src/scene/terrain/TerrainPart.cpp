#include "TerrainPart.h"

#include "Terrain.h"
#include <graphics/Renderer.h>

//
// Terrain
//
namespace zaap { namespace scene {

	TerrainPart::TerrainPart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain const* terrain)
		: m_VertexX(vertexX),
		m_VertexY(vertexY),
		m_VCountHorizontal(vCountHorizontal),
		m_VCountVertical(vCountVertical)
	{
		TERRAIN_DESC tDesc = terrain->getTerrainDesc();
		m_MinX = m_VertexX * tDesc.VertexSpacing;
		m_MinZ = m_VertexY * tDesc.VertexSpacing;

		m_MaxX = (m_VertexX + m_VCountHorizontal) * tDesc.VertexSpacing;
		m_MaxZ = (m_VertexY + m_VCountVertical) * tDesc.VertexSpacing;

		m_MinHeight = terrain->getMinHeight();
		m_MaxHeight = terrain->getMaxHeight();
		
	}

	TerrainPart::~TerrainPart() {}

	//
	// Creation
	//
	TerrainPart* TerrainPart::CreateTerrainPart(uint vertexX, uint vertexY, uint width, uint height, Terrain* terrain)
	{
		uint vCount = width * height;
		if (vCount > terrain->getTerrainDesc().MaxVerticesPerTerrainTile)
			return new TerrainTreePart(vertexX, vertexY, width, height, terrain);

		return new TerrainTreeEndPart(vertexX, vertexY, width, height, terrain);

	}

	bool TerrainPart::isVisible(const graphics::ViewFrustum& view) const
	{
		return view.isCuboidVisible(Vec3(m_MinX, m_MinHeight, m_MinZ), Vec3(m_MaxX, m_MaxHeight, m_MaxZ));

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
		: TerrainPart(vertexX, vertexY, vCountHorizontal, vCountVertical, terrain)
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
			vy = m_VertexY + (centerY * (ly == 1));
			height = vertical / 2 + ((vertical % 2) * (ly == 1)); //Adds 1 if ((ly == 1) && (m_VCountVertical % 2 == 1)) 

			for (lx = 0; lx < 2; lx++)
			{
				//width && vx
				vx = m_VertexX + (centerX * (lx == 1));
				width = horizontal / 2 + ((horizontal % 2) * (lx == 1));

				m_Members[lx + ly * 2] = CreateTerrainPart(vx, vy, width, height, terrain);
			}
		}

		Vec3 min_(m_MinX, m_MinHeight, m_MinZ);
		Vec3 max_(m_MaxX, m_MaxHeight, m_MaxZ);

		Vec3 tPoints[]{
			Vec3(min_.X, min_.Y, min_.Z), Vec3(max_.X, min_.Y, min_.Z),
			Vec3(min_.X, min_.Y, max_.Z), Vec3(max_.X, min_.Y, max_.Z),
			Vec3(min_.X, max_.Y, min_.Z), Vec3(max_.X, max_.Y, min_.Z),
			Vec3(min_.X, max_.Y, max_.Z), Vec3(max_.X, max_.Y, max_.Z)
		};

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

	void TerrainTreePart::render(const graphics::ViewFrustum& view)
	{
		if (isVisible(view))
			for (uint i = 0; i < 4; i++)
				m_Members[i]->render(view);
	}
}}

//
// TerrainTreeEndPart
//
namespace zaap { namespace scene {

	TerrainTreeEndPart::TerrainTreeEndPart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain)
		: TerrainPart(vertexX, vertexY, 
			((vertexX + vCountHorizontal + 1) < terrain->getVCountHorizontal()) ? (vCountHorizontal + 1) : vCountHorizontal,
			((vertexY + vCountVertical + 1) < terrain->getVCountVertical()) ? (vCountVertical + 1) : vCountVertical, terrain)
		//Adds one to the width and height because the End tiles have to overlap. 
		//However the values are kept the same if they reach the edge because there is no tile to overlap.
	{
		std::vector<graphics::ZA_TERRAIN_VERTEX> vertices(getVCount());

		uint width = m_VCountHorizontal;
		uint height = m_VCountVertical;
		uint terrainWidth = terrain->getVCountHorizontal();

		m_MinHeight = m_MaxHeight = terrain->getVertexHeight(m_VertexX, m_VertexY);
		uint x, y;
		uint xa, ya;
		float vertexHeight;
		for (y = 0; y < height; y++) 
		{
			ya = m_VertexY + y;
			for (x = 0; x < width; x++)
			{
				xa = m_VertexX + x;
				vertices[x + y * width] = terrain->m_Vertices[xa + ya * terrainWidth]; // memcpy does not seem to be faster

				vertexHeight = vertices[x + y * width].Position.Y;

				if (vertexHeight < m_MinHeight)
					m_MinHeight = vertexHeight;
				else if (vertexHeight > m_MaxHeight)
					m_MaxHeight = vertexHeight;
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

		m_VBuffer = graphics::API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(graphics::ZA_TERRAIN_VERTEX), vertices.size(), &indices[0], indices.size(), graphics::ZA_SHADER_TERRAIN_SHADER);
	}

	void TerrainTreeEndPart::render(const graphics::ViewFrustum& view) 
	{
		if (isVisible(view))
			m_VBuffer->draw();
	}

}}

//
//
//
namespace zaap { namespace scene {
	TerrainNullPart::TerrainNullPart()
		: TerrainPart(0, 0, 0, 0, nullptr)
	{
	}

	void TerrainNullPart::render(const graphics::ViewFrustum& view) {}
}}