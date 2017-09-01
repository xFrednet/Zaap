#include "GUILabel.h"
#include <gui/VertexBufferHelper.h>

namespace zaap { namespace gui{
	using namespace graphics;

	void GUILabel::updateVertexBuffer()
	{
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
		if (m_Font)
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
	GUILabel::GUILabel(const Point& pos, const String& text, const Font& font, 
		const float& textSize, const Color& textColor, const Color& background)
		: GUILabel(pos, ZA_GUI_SIZE_WRAP_CONTENT, ZA_GUI_SIZE_WRAP_CONTENT, text, font, textSize, textColor, background)
	{
	}
	GUILabel::GUILabel(const Point& pos, const int& prefWidth, const int& prefHeight, const String& text, 
		const Font& font, const float& textSize, const Color& textColor, const Color& background)
		: GUIComponent(0, 0),
		m_Text(text),
		m_TextSize(textSize),
		m_Font(font),
		m_TextColor(textColor),
		m_BackgroundColor(background)
	{
		m_Size.Position = pos;
		setPreferredSize(prefWidth, prefHeight);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUILabel::render(GUIRenderer* renderer)
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
		changedContent();
	}
	String GUILabel::getText() const
	{
		return m_Text;
	}

	void GUILabel::setTextSize(const float& size)
	{
		m_TextSize = size;
		changedContent();
	}
	float GUILabel::getTextSize() const
	{
		return m_TextSize;
	}

	void GUILabel::setTextColor(const Color& color)
	{
		m_TextColor = color;
		requestRedraw();
	}
	Color GUILabel::getTextColor() const
	{
		return m_TextColor;
	}

	/* ********************************************************* */
	// * Font *
	/* ********************************************************* */
	void GUILabel::setFont(const Font& font)
	{
		m_Font = font;
	}
	Font GUILabel::getFont() const
	{
		return m_Font;
	}

	/* ********************************************************* */
	// * Background *
	/* ********************************************************* */
	void GUILabel::setBackgroundColor(const Color& color)
	{
		m_BackgroundColor = color;
		updateVertexBuffer();
		requestRedraw();
	}
	Color GUILabel::getBackgroundColor() const
	{
		return m_BackgroundColor;
	}
}}
