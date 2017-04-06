#include "GUILabel.h"
#include <gui/VertexBufferHelper.h>
#include <util/Log.h>

namespace zaap { namespace gui{

	void GUILabel::updateVertexBuffer()
	{
		using namespace graphics;
		using namespace API;

		uint sqares = (m_Font.get()) ? m_Text.length() : 0; 
		sqares++; // +1 for the background
		uint vCount = sqares * 4; //vertexCount
		uint iCount = sqares * 6; //indexCount
		//this test if m_Vertexbuffer is valid/okay to use
		if (m_VertexBuffer)
			if ((m_VertexBuffer->getVertexCount() != vCount) || (m_VertexBuffer->getIndexCount() != iCount))
			{
				delete m_VertexBuffer;
				m_VertexBuffer = nullptr;
			}

		if (!m_VertexBuffer)
			m_VertexBuffer = VertexBufferCore::CreateVertexBufferCore(sizeof(ZA_GUI_VERTEX), vCount, iCount);

		/* ********************************************************* */
		// * drawing *
		/* ********************************************************* */
		VertexBufferHelper helper(&m_VertexBuffer);

		helper.drawRectangle(getGlobalPosition(), getWidth(), getHeight(), m_BackgroundColor);
		if (m_Font.get())
			helper.drawString(m_Text, m_Font, m_TextSize, getGlobalContentPosition());

		helper.save();
	}

	uint GUILabel::getWrappedWidth() const
	{
		if (m_Font.get())
			return m_MarginLeft + m_Font->getStringWidth(m_Text, m_TextSize) + m_MarginRight;

		return m_MarginLeft + m_MarginRight;
	}
	uint GUILabel::getWrappedHeight() const
	{
		if (m_Font.get())
			return m_MarginTop + m_Font->getStringHeight(m_Text, m_TextSize) + m_MarginBottom;
		
		return m_MarginTop + m_MarginBottom;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructors //
	/* //////////////////////////////////////////////////////////////////////////////// */
	GUILabel::GUILabel(const Point& pos, const String& text, const graphics::Font& font, 
		const float& textSize, const graphics::Color& textColor, const graphics::Color& background)
		: GUILabel(Rectangle(pos, ZA_GUI_SIZE_WRAP_CONTENT, ZA_GUI_SIZE_WRAP_CONTENT), text, font, textSize, textColor, background)
	{
	}
	GUILabel::GUILabel(const Rectangle& size, const String& text, const graphics::Font& font,
		const float& textSize, const graphics::Color& textColor, const graphics::Color& background)
		: GUIComponent(0, 0),
		m_Text(text),
		m_TextSize(textSize),
		m_Font(font),
		m_TextColor(textColor),
		m_BackgroundColor(background)
	{
		m_Size = size;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUILabel::render(graphics::GUIRenderer* renderer)
	{
		renderer->setFont(m_Font, m_TextColor);
		m_VertexBuffer->draw();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Getters/Setters //
	/* //////////////////////////////////////////////////////////////////////////////// */
	/* ********************************************************* */
	// * Text *
	/* ********************************************************* */
	void GUILabel::setText(const String& text)
	{
		m_Text = text;
		updateVertexBuffer();
		requestRedraw();
	}
	String GUILabel::getText() const
	{
		return m_Text;
	}

	void GUILabel::setTextSize(const float& size)
	{
		m_TextSize = size;
		updateVertexBuffer();
		requestRedraw();
	}
	float GUILabel::getTextSize() const
	{
		return m_TextSize;
	}

	void GUILabel::setTextColor(const graphics::Color& color)
	{
		m_TextColor = color;
		requestRedraw();
	}
	graphics::Color GUILabel::getTextColor() const
	{
		return m_TextColor;
	}

	/* ********************************************************* */
	// * Font *
	/* ********************************************************* */
	void GUILabel::setFont(const graphics::Font& font)
	{
		m_Font = font;
	}
	graphics::Font GUILabel::getFont() const
	{
		return m_Font;
	}

	/* ********************************************************* */
	// * Background *
	/* ********************************************************* */
	void GUILabel::setBackgroundColor(const graphics::Color& color)
	{
		m_BackgroundColor = color;
		updateVertexBuffer();
		requestRedraw();
	}
	graphics::Color GUILabel::getBackgroundColor() const
	{
		return m_BackgroundColor;
	}
}}
