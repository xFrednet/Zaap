#include "Terrain.h"

//
// TerrainOption
//
namespace ZaapCLI {

	TerrainOptions::TerrainOptions()
		: ManagedClass(new zaap::scene::TERRAIN_DESC())
	{
	}
	TerrainOptions::TerrainOptions(zaap::scene::TERRAIN_DESC* instance)
		: ManagedClass(instance)
	{
	}

	void TerrainOptions::setup()
	{
		m_Instance->setup();
	}

	zaap::scene::TERRAIN_DESC to_CPP_TERRAIN_DESC(TerrainOptions^ terrainDesc)
	{
		return *terrainDesc->getHandle();
	}
	TerrainOptions^ to_CLI_TERRAIN_DESC(zaap::scene::TERRAIN_DESC terrainDesc)
	{
		return gcnew TerrainOptions(&terrainDesc);

	}

}

//
// Terrain
//
namespace ZaapCLI {
	
	Terrain::Terrain(System::String^ folder, TerrainOptions^ terrainDesc)
		: ManagedClass(new zaap::scene::Terrain(to_CPP_String(folder), to_CPP_TERRAIN_DESC(terrainDesc)))
	{
	}
	Terrain::Terrain(zaap::scene::Terrain* instance)
		: ManagedClass(instance)
	{
	}

	//Util
	void Terrain::cleanup()
	{
		m_Instance->cleanup();
	}

	//getters
	TerrainOptions^ Terrain::getTerrainOptions()
	{
		return to_CLI_TERRAIN_DESC(m_Instance->getTerrainDesc());
	}

	float Terrain::getMinHeight()
	{
		return m_Instance->getMinHeight();
	}
	float Terrain::getMaxHeight()
	{
		return m_Instance->getMaxHeight();
	}

	float Terrain::getHorizontalSize()
	{
		return m_Instance->getHorizontalSize();
	}
	float Terrain::getVerticalSize()
	{
		return m_Instance->getVerticalSize();
	}
	uint Terrain::getVCountHorizontal()
	{
		return m_Instance->getVCountHorizontal();
	}
	uint Terrain::getVCountVertical()
	{
		return m_Instance->getVCountVertical();
	}

	//HeightMap
	float Terrain::getVertexHeight(uint vertexX, uint vertexY)
	{
		return m_Instance->getVertexHeight(vertexX, vertexY);
	}
	float Terrain::getHeight(Vector2^ point)
	{
		return m_Instance->getHeight(*point->getHandle());
	}

	//game loop methods
	void Terrain::update()
	{
		m_Instance->update();
	}
	void Terrain::render()
	{
		// TODO m_Instance->render();
	}

	//render
	void Terrain::bindTextures()
	{
		m_Instance->bindTextures();
	}
	
}