#include "Terrain.h"
#include <util/Console.h>
#include <graphics/TextureManager.h>
#include <graphics/mesh/Mesh.h>
#include <graphics/Renderer.h>

//
// Terrain Desc
//
namespace zaap { namespace scene {

	
	TERRAIN_DESC::TERRAIN_DESC()
		: HeightMin(0.0f),
		HeightMax(0.0f),
		DefaultHeight(0.0f),
		VertexSpacing(0.0f),
		VerticesPerTexture(0),
		MaxVerticesPerTerrainTile(0)
	{
	}
	TERRAIN_DESC::TERRAIN_DESC(float heightMin, float heightMax, float defaultHeight, float vertexSpacing, uint verticesPerTexture)
		: HeightMin(heightMin),
		HeightMax(heightMax),
		DefaultHeight(defaultHeight),
		VertexSpacing(vertexSpacing),
		VerticesPerTexture(verticesPerTexture),
		MaxVerticesPerTerrainTile(0)
	{
	}

	void TERRAIN_DESC::setup()
	{
		HeightMin = -10.0f;
		HeightMax = 20.0f;
		DefaultHeight = 0.0f;
		VertexSpacing = 1.0f;
		VerticesPerTexture = 10;
		MaxVerticesPerTerrainTile = 2500;
	}

}}

//
// Terrain class
//
namespace zaap { namespace scene {
	
	Terrain::Terrain(String folder, TERRAIN_DESC terrainDesc)
		: m_TerrainDesc(terrainDesc),
		m_Vertices(0)
	{
		init(folder);
	}

	//
	// Util
	//
	void Terrain::init(String folder)
	{
		initVertices(String(folder + "heightMap.png"), String(folder + "textureMap.png"));
		initTexture(folder);

		m_ParrentNode = TerrainPart::CreateTerrainPart(0, 0, m_VCountHorizontal, m_VCountVertical, this);
	}

	void Terrain::initTexture(String folder)
	{
		m_Textures[0] = graphics::API::Texture::CreateTexture2D("terrainTexture", folder + "texture_0.jpg");
		m_Textures[1] = graphics::API::Texture::CreateTexture2D("terrainTexture", folder + "texture_1.jpg");
		m_Textures[2] = graphics::API::Texture::CreateTexture2D("terrainTexture", folder + "texture_3.jpg");
		m_Textures[3] = graphics::API::Texture::CreateTexture2D("terrainTexture", folder + "texture_2.jpg");
	}
	void Terrain::cleanup()
	{
		m_ParrentNode->cleanup();
		delete m_ParrentNode;

		m_ParrentNode = nullptr;
	}

	//
	// HeightMap
	//
	void Terrain::initVertices(String heightMapFile, String texMapFile)
	{
		graphics::Bitmap heightMap(heightMapFile.c_str());

		//error check
		m_VCountHorizontal = heightMap.getWidth();
		m_VCountVertical = heightMap.getHeight();
		if (m_VCountHorizontal == 0 || m_VCountVertical == 0)
		{
			ZAAP_ERROR("The given heightMap does not exists");
			return;
		}

		if (m_Vertices.size() != m_VCountHorizontal * m_VCountVertical)
			m_Vertices = std::vector<graphics::ZA_TERRAIN_VERTEX>(m_VCountHorizontal * m_VCountVertical);

		//height
		uint x, y;
		{
			float height = calculateHeightFromColor(heightMap.getColor(0, 0));
			m_MinHeight = m_MaxHeight = height;
			float vSpacing = m_TerrainDesc.VertexSpacing;

			for (y = 0; y < m_VCountVertical; y++)
			{
				for (x = 0; x < m_VCountHorizontal; x++)
				{
					height = calculateHeightFromColor(heightMap.getColor(x, y));
					m_Vertices[x + y * m_VCountVertical].Position = Vec3((float)x * vSpacing, height, (float)y * vSpacing);

					if (height < m_MinHeight)
						m_MinHeight = height;
					else if (height > m_MaxHeight)
						m_MaxHeight = height;
				}
			}
		}

		//other Vertex Data
		{
			graphics::Bitmap texMap(texMapFile.c_str());

			float texIncrease = 1.0f / m_TerrainDesc.VerticesPerTexture;
			for (y = 0; y < m_VCountVertical; y++)
			{
				for (x = 0; x < m_VCountHorizontal; x++)
				{
					m_Vertices[x + y * m_VCountVertical].Normal = calcualteNormal(x, y);
					m_Vertices[x + y * m_VCountVertical].TexMapColor = texMap.getColor(x, y).getRGB();
					m_Vertices[x + y * m_VCountVertical].TexCoord = Vec2(x * texIncrease, y * texIncrease);
				}
			}
			
		}
	}
	float Terrain::calculateHeightFromColor(graphics::Color color) const
	{
		float total = color.R + color.G + color.B;
		float distance = m_TerrainDesc.HeightMax - m_TerrainDesc.HeightMin;
		total /= 3.0f;
		return distance * total + m_TerrainDesc.HeightMin;
	}
	float Terrain::getVertexHeight(uint vertexX, uint vertexY) const
	{
		if (vertexX >= m_VCountHorizontal || vertexY >= m_VCountVertical)
			return 0.0f;

		return m_Vertices[vertexX + vertexY * m_VCountVertical].Position.Y;
	}

	Vec3 Terrain::calcualteNormal(uint vX, uint vY) const
	{
		Vec3 normal(0.0f, 2.0f, 0.0f);

		//x Value
		{
			if (vX == 0)
				normal.X = getVertexHeight(vX, vY) - getVertexHeight(vX + 1, vY);
			else if (vX == m_VCountHorizontal - 1) 
				normal.X = getVertexHeight(vX - 1, vY) - getVertexHeight(vX, vY);
			else //vertexX < m_TerrainDesc.VerticesPerLine - 1
				normal.X = getVertexHeight(vX - 1, vY) - getVertexHeight(vX + 1, vY);
			
		}
		{
			if (vY == 0)
				normal.Z = getVertexHeight(vX, vY) - getVertexHeight(vX, vY + 1);
			else if (vY == m_VCountVertical - 1)
				normal.Z = getVertexHeight(vX, vY - 1) - getVertexHeight(vX, vY);
			else //vX < m_TerrainDesc.VerticesPerLine - 1
				normal.Z = getVertexHeight(vX, vY - 1) - getVertexHeight(vX, vY + 1);
		}

		normal.normalize();
		return normal;
	}

	//
	// Getters
	//
	TERRAIN_DESC Terrain::getTerrainDesc() const
	{
		return m_TerrainDesc;
	}
	graphics::API::Texture2D* Terrain::getTexture(uint texture) const
	{
		if (texture >= 4) 
			return m_Textures[0];

		return m_Textures[texture];
	}

	float Terrain::getMinHeight() const
	{
		return m_MinHeight;
	}
	float Terrain::getMaxHeight() const
	{
		return m_MaxHeight;
	}

	float Terrain::getHorizontalSize() const
	{
		return m_VCountHorizontal * m_TerrainDesc.VertexSpacing;
	}
	float Terrain::getVerticalSize() const
	{
		return m_VCountVertical * m_TerrainDesc.VertexSpacing;
	}

	uint Terrain::getVCountHorizontal() const
	{
		return m_VCountHorizontal;
	}
	uint Terrain::getVCountVertical() const
	{
		return m_VCountVertical;
	}

	float Terrain::getHeight(Vec2 point)
	{
		uint vX = (uint)(point.X / m_TerrainDesc.VertexSpacing);
		uint vY = (uint)(point.Y / m_TerrainDesc.VertexSpacing);

		if (vX >= m_VCountHorizontal - 1 || vY >= m_VCountVertical - 1)
			return 0.0f;

		// true    | false  
		// v0   v2 |      v2
		//         |        
		// v1      | v3   v0
		Vec3 v0, v1, v2;
		if ((point.X - vX) <= (1 - (point.Y - vY)))
		{
			v0 = m_Vertices[(vX    ) + (vY    ) * m_VCountHorizontal].Position;
			v1 = m_Vertices[(vX    ) + (vY + 1) * m_VCountHorizontal].Position;
			v2 = m_Vertices[(vX + 1) + (vY    ) * m_VCountHorizontal].Position;
		} else
		{
			v0 = m_Vertices[(vX + 1) + (vY + 1) * m_VCountHorizontal].Position;
			v1 = m_Vertices[(vX + 1) + (vY    ) * m_VCountHorizontal].Position;
			v2 = m_Vertices[(vX    ) + (vY + 1) * m_VCountHorizontal].Position;
		}
		float height = BarycentricY(v0, v1, v2, Vec2(point.X, point.Y));
		return height;
	}

	//
	// Gameloop Methods
	//
	void Terrain::update()
	{
	}
	void Terrain::render(const graphics::ViewFrustum& view) const
	{
		bindTextures();
		graphics::Renderer::StartShader(graphics::ZA_SHADER_TERRAIN_SHADER);

		m_ParrentNode->render(view);
	}

	void Terrain::bindTextures() const
	{
		for (uint i = 0; i < 4; i++)
			m_Textures[i]->bind(i);
	}
}}

