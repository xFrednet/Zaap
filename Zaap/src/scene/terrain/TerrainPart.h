#pragma once

#include <Common.h>
#include <Types.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace scene {
	class Terrain;

	class ZAAP_API TerrainPart
	{
	private:
		friend class Terrain;
	
	protected:
		uint m_VertexX;
		uint m_VertexY;
		uint m_VCountHorizontal;
		uint m_VCountVertical;
	
		TerrainPart(uint VertexX, uint VertexY, uint vCountHorizontal, uint vCountVertical);

	public:
		virtual ~TerrainPart();
		
		//creation
		static TerrainPart* CreateTerrainPart(uint vertexX, uint vertexY, uint width, uint height, Terrain* terrain);

		//getters
		uint getVCountHorizontal() const;
		uint getVCountVertical() const;
		uint getVCount() const;
		
		virtual void cleanup();

		virtual void render() = 0;
	};
	
	class ZAAP_API TerrainTreePart : public TerrainPart
	{
	protected:
		TerrainPart* m_Members[4];
	public:
		TerrainTreePart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain);

		void cleanup() override;

		void render() override;
	};

	class ZAAP_API TerrainTreeEndPart : public TerrainPart
	{
	protected:
		graphics::API::VertexBuffer* m_VBuffer;
	public:
		TerrainTreeEndPart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain);

		void render() override;
	};
}}
