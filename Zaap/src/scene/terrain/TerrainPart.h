#pragma once

#include <Common.h>
#include <Types.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace scene {
	struct TERRAIN_DESC;
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
		
		float m_MinX, m_MinZ;
		float m_MaxX, m_MaxZ;
		float m_MinHeight, m_MaxHeight;

		TerrainPart(uint VertexX, uint VertexY, uint vCountHorizontal, uint vCountVertical, Terrain const* terrain);

	public:
		virtual ~TerrainPart();
		
		//creation
		static TerrainPart* CreateTerrainPart(uint vertexX, uint vertexY, uint width, uint height, Terrain* terrain);

		bool isVisible(const graphics::ViewFrustum& view) const;

		//getters
		uint getVCountHorizontal() const;
		uint getVCountVertical() const;
		uint getVCount() const;
		
		virtual void cleanup();

		virtual void render(const graphics::ViewFrustum& view) = 0;
	};
	
	class ZAAP_API TerrainTreePart : public TerrainPart
	{
	protected:
		TerrainPart* m_Members[4];
	public:
		TerrainTreePart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain);

		void cleanup() override;

		void render(const graphics::ViewFrustum& view) override;
	};

	class ZAAP_API TerrainTreeEndPart : public TerrainPart
	{
	protected:
		graphics::API::VertexBufferCore* m_VBuffer;
	public:
		TerrainTreeEndPart(uint vertexX, uint vertexY, uint vCountHorizontal, uint vCountVertical, Terrain* terrain);

		void render(const graphics::ViewFrustum& view) override;
	};

	class ZAAP_API TerrainNullPart : public TerrainPart
	{
	public:
		TerrainNullPart();

		void render(const graphics::ViewFrustum& view) override;
	};
}}
