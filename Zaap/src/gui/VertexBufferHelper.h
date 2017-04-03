#pragma once

#include <Common.h>

#include <graphics/API/VertexBuffer.h>

#include <maths/Maths.h>
#include <graphics/shader/Shader.h>

namespace zaap { namespace gui {

	typedef enum ZAAP_API GUI_VERTEX_TYPES_ {
		ZA_GUI_VERTEX_TYPE_COLOR   = 0,
		ZA_GUI_VERTEX_TYPE_TEXTURE = 1
	} GUI_VERTEX_TYPES;

	class ZAAP_API VertexBufferHelper
	{
		uint m_VertexCount;
		uint m_IndexCount;
		
		uint m_CurrentVIndex;
		uint m_CurrentIIndex;
		
		uint* m_Indices;
		graphics::ZA_GUI_VERTEX* m_Vertices;
		
		graphics::API::VertexBufferCore* m_VertexBuffer;
	public:
		VertexBufferHelper(graphics::API::VertexBufferCore** vb);
		~VertexBufferHelper();
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */
		void save();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Shapes //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		/* ********************************************************* */
		// * Util *
		/* ********************************************************* */
		void addRectangle(graphics::ZA_GUI_VERTEX vertices[4]);
	public:
		/* ********************************************************* */
		// * Rectangle *
		/* ********************************************************* */
		void drawRectangle(const Point& pos, const uint& width, const uint& height,
			const graphics::Color& color);
		void drawRectangle(const Vec2& posMin, const Vec2& posMax,
			const graphics::Color& color);
		void drawRectangle(const Vec2& v0, const Vec2& v1,  const Vec2& v2, const Vec2& v3, 
			const graphics::Color& color);
		
		/* ********************************************************* */
		// * Texture *
		/* ********************************************************* */
		void drawTexture(const Point& pos, const uint& width, const uint& height,
			Vec2 texMin = Vec2(0, 0), Vec2 texMax = Vec2(1, 1));
		void drawTexture(const Vec2& posMin, const Vec2& posMax,
			Vec2 texMin = Vec2(0, 0), Vec2 texMax = Vec2(1, 1));
		void drawTexture(const Vec2& v0, const Vec2& v1, const Vec2& v2, const Vec2& v3,
			Vec2 texMin, Vec2 texMax);
		
		/* ********************************************************* */
		// * Other *
		/* ********************************************************* */
		void drawTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2,
			const graphics::Color& color);
	};

}}
