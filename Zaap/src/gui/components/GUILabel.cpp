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
			helper.drawString(m_Text, m_Font, m_TextSize, getGlobalPosition());

		helper.save();
	}

	uint GUILabel::getWrappedWidth() const
	{
		return 0;
		// TODO font->getStringWidth(text, fontSize);
	}
	uint GUILabel::getWrappedHeight() const
	{
		return 0;
		// TODO font->getStringWidth(text, fontSize);

	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Constructors //
	/* //////////////////////////////////////////////////////////////////////////////// */
	GUILabel::GUILabel(String content, GUIComponent* parent)
		: GUILabel(content, 12.0f, parent)
	{
	}

	GUILabel::GUILabel(String content, float textSize, GUIComponent* parent)
		: GUIComponent(0, 0, parent),
		m_Text(content),
		m_TextSize(textSize),
		m_TextColor(),
		m_BackgroundColor(0.0f, 0.0f, 0.0f, 0.0f)
	{
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
