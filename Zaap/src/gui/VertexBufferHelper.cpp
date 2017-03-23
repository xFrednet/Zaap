#include "VertexBufferHelper.h"
#include <util/Log.h>

namespace zaap { namespace gui {
	VertexBufferHelper::VertexBufferHelper(graphics::API::VertexBuffer** vb)
		: m_CurrentVIndex(0),
		m_CurrentIIndex(0),
		m_VertexBuffer(*vb)
	{
		m_VertexCount = m_VertexBuffer->getVertexCount();
		m_IndexCount = m_VertexBuffer->getIndexCount();

		m_Indices = new uint[m_VertexCount];
		m_Vertices = new graphics::ZA_GUI_VERTEX[m_VertexCount];
	}
	VertexBufferHelper::~VertexBufferHelper()
	{
		delete[] m_Vertices;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void VertexBufferHelper::start()
	{
		m_CurrentVIndex = 0;
		m_CurrentIIndex = 0;

		memset(m_Vertices, 0, sizeof(graphics::ZA_GUI_VERTEX) * m_VertexCount);
		memset(m_Indices , 0, sizeof(uint) * m_IndexCount);
	}
	void VertexBufferHelper::stop()
	{
		ZA_ASSERT(m_CurrentVIndex <= m_VertexCount);
		ZA_ASSERT(m_CurrentIIndex <= m_IndexCount);

		m_VertexBuffer->updateVertices(m_Vertices, m_CurrentVIndex);
		m_VertexBuffer->updateIndices(m_Indices, m_CurrentIIndex);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Shapes //
	/* //////////////////////////////////////////////////////////////////////////////// */

	/* ********************************************************* */
	// * Util *
	/* ********************************************************* */
	void VertexBufferHelper::addRectangle(graphics::ZA_GUI_VERTEX vertices[4])
	{
		ZA_ASSERT(m_CurrentVIndex + 4 <= m_VertexCount);
		ZA_ASSERT(m_CurrentIIndex + 6 <= m_IndexCount);

		if (m_CurrentVIndex + 4 > m_VertexCount)
			return;
		if (m_CurrentIIndex + 6 > m_IndexCount)
			return;
		
		////////////////////////////////////////////////////////////////////////////////
		// Vertices //
		////////////////////////////////////////////////////////////////////////////////
		{
			memcpy(&m_Vertices[m_CurrentVIndex], vertices, sizeof(graphics::ZA_GUI_VERTEX) * 4);
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Indices //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			// v0  v3
			// v1  v2

			uint i0 = m_CurrentVIndex++;
			uint i1 = m_CurrentVIndex++;
			uint i2 = m_CurrentVIndex++;
			uint i3 = m_CurrentVIndex++;

			// v0 | v1 | v2
			m_Indices[m_CurrentIIndex++] = i0;
			m_Indices[m_CurrentIIndex++] = i2;
			m_Indices[m_CurrentIIndex++] = i1;
			// v0 | v2 | v3
			m_Indices[m_CurrentIIndex++] = i0;
			m_Indices[m_CurrentIIndex++] = i2;
			m_Indices[m_CurrentIIndex++] = i3;
		}
	}

	/* ********************************************************* */
	// * Rectangle *
	/* ********************************************************* */
	void VertexBufferHelper::drawRectangle(const Point& pos, const uint& width, const uint& height, const graphics::Color& color)
	{
		drawRectangle(Vec2(pos.X, pos.Y), Vec2(pos.X + (float)width, pos.Y + (float)height), color);
	}
	void VertexBufferHelper::drawRectangle(const Vec2& posMin, const Vec2& posMax, const graphics::Color& color)
	{
		// v0  v3
		// v1  v2
		drawRectangle(
			posMin, Vec2(posMin.X, posMax.Y), 
			posMax, Vec2(posMax.X, posMin.Y),
			color);
	}
	void VertexBufferHelper::drawRectangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, const Vec2& v3, const graphics::Color& color)
	{
		// v0  v3
		// v1  v2
		graphics::ZA_GUI_VERTEX vertices[4];

		//Position
		vertices[0].Position = v0;//z is set to 0
		vertices[1].Position = v1;//z is set to 0
		vertices[2].Position = v2;//z is set to 0
		vertices[3].Position = v3;//z is set to 0

		//type data
		for (uint i = 0; i < 4; i++)
		{
			vertices[i].Type = ZA_GUI_VERTEX_TYPE_COLOR;
			vertices[i].TypeInfo = color.RGBA;
		}
		
		//adding the Rectangle
		addRectangle(vertices);
	}

	/* ********************************************************* */
	// * Texture *
	/* ********************************************************* */
	void VertexBufferHelper::drawTexture(const Point& pos, const uint& width, const uint& height, Vec2 texMin, Vec2 texMax)
	{
		drawTexture(Vec2(pos.X, pos.Y), Vec2(pos.X + float(width), pos.Y + float(height)), texMin, texMax);
	}
	void VertexBufferHelper::drawTexture(const Vec2& posMin, const Vec2& posMax, Vec2 texMin, Vec2 texMax)
	{
		// v0  v3
		// v1  v2
		drawTexture(
			posMin, Vec2(posMin.X, posMax.Y),
			posMax, Vec2(posMax.X, posMin.Y),
			texMin, texMax);
	}
	void VertexBufferHelper::drawTexture(const Vec2& v0, const Vec2& v1, const Vec2& v2, const Vec2& v3, Vec2 texMin, Vec2 texMax)
	{
		// v0  v3
		// v1  v2
		graphics::ZA_GUI_VERTEX vertices[4];

		//Position
		vertices[0].Position = v0;//z is set to 0
		vertices[1].Position = v1;//z is set to 0
		vertices[2].Position = v2;//z is set to 0
		vertices[3].Position = v3;//z is set to 0

		//type data
		for (uint i = 0; i < 4; i++)
			vertices[i].Type = ZA_GUI_VERTEX_TYPE_TEXTURE;
		
		//TypeInfo
		vertices[0].TypeInfo = texMin;
		vertices[1].TypeInfo = Vec2(texMin.X, texMax.Y);
		vertices[2].TypeInfo = texMax;
		vertices[3].TypeInfo = Vec2(texMax.X, texMin.Y);

		//adding the Rectangle
		addRectangle(vertices);
	}
	
	/* ********************************************************* */
	// * Other *
	/* ********************************************************* */
	void VertexBufferHelper::drawTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, const graphics::Color& color)
	{
		if (m_CurrentVIndex + 3 <= m_VertexCount)
			return;
		if (m_CurrentIIndex + 3 <= m_IndexCount)
			return;
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Vertex data //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			//Position
			m_Vertices[m_CurrentVIndex++].Position = v0;//z is set to 0
			m_Vertices[m_CurrentVIndex++].Position = v1;//z is set to 0
			m_Vertices[m_CurrentVIndex++].Position = v2;//z is set to 0
		
			//type data
			m_CurrentVIndex -= 3;
			for (uint i = 0; i < 3; i++)
			{
				m_Vertices[m_CurrentVIndex].Type = ZA_GUI_VERTEX_TYPE_COLOR;
				m_Vertices[m_CurrentVIndex].TypeInfo = color.RGBA;
				m_CurrentVIndex++;
			}
		}

		// indices
		m_Indices[m_CurrentIIndex++] = m_CurrentVIndex - 3;
		m_Indices[m_CurrentIIndex++] = m_CurrentVIndex - 2;
		m_Indices[m_CurrentIIndex++] = m_CurrentVIndex - 1;
	}
}}
