#pragma once

#include <Common.h>

#include <graphics/Image.h>
#include <maths/Maths.h>
#include <graphics/Color.h>
#include <graphics/API/VertexBuffer.h>
#include <graphics/API/Texture2D.h>

namespace zaap { namespace scene {
	
	struct TERRAIN_DESC;

	class ZAAP_API TerrainTile
	{
	private:
		math::Vec2 m_Position;
		TERRAIN_DESC const *m_TerrainDesc;
		std::vector<float> m_HightMap;
		graphics::API::VertexBuffer *m_VBuffer;
		graphics::Texture2D *m_Texture;
	public:
		TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc, graphics::Image heightMap);
		TerrainTile(math::Vec2 position, const TERRAIN_DESC const *terrainDesc);
		~TerrainTile(void);

		//game loop
		void render();

		//getter
		math::Mat4 getTransformationMatrix(void) const;
		graphics::Texture2D* getTexture(void) const;
		graphics::API::VertexBuffer* getVertexBuffer(void) const;

		//setter
		void setTexture(graphics::Texture2D* texture);

		//Util
		void makeFlat(float height);
	protected:
		float calculateHeight(graphics::Color color) const;
		void createVertexBuffer();
	};

}}
