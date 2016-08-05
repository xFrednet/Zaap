#pragma once

#include <Common.h>

#include <graphics/Bitmap.h>
#include <maths/Maths.h>
#include <graphics/Color.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace scene {
	
	struct TERRAIN_DESC;

	class ZAAP_API TerrainTile
	{
	private:
		math::Vec2 m_Position;
		TERRAIN_DESC const *m_TerrainDesc;
		float *m_HightMap = nullptr;
		graphics::API::VertexBuffer *m_VBuffer;

	public:
		TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc, graphics::Bitmap heightMap);
		TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc);
		~TerrainTile(void);

		//game loop
		void render();

		//getter
		math::Mat4 getTransformationMatrix() const;

		//Util
		void makeFlat(float height);
	protected:
		float calculateHeight(graphics::Color color) const;
		void createVertexBuffer();
	};

}}
