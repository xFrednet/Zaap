#pragma once

#include <Common.h>

#include "../GUIComponent.h"
#include "graphics/Font.h"

namespace zaap { namespace gui {
	
	class ZAAP_API GUILabel : public GUIComponent
	{
	protected:
		String m_Text;
		float m_TextSize;
		graphics::Font m_Font;
		graphics::Color m_TextColor;

		graphics::Color m_BackgroundColor;
	protected:
		void updateVertexBuffer() override;
		uint getWrappedWidth() const override;
		uint getWrappedHeight() const override;
	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructors //
		/* //////////////////////////////////////////////////////////////////////////////// */
		
		GUILabel(const Point& pos, const String& text, const graphics::Font& font, 
			const float& textSize = 12.0f,
			const graphics::Color& textColor = graphics::Color(0.0f, 0.0f, 0.0f, 1.0f), 
			const graphics::Color& background = graphics::Color(1.0f, 1.0f, 1.0f, 0.0f));
		GUILabel(const Rectangle& size, const String& text, const graphics::Font& font,
			const float& textSize = 12.0f,
			const graphics::Color& textColor = graphics::Color(0.0f, 0.0f, 0.0f, 1.0f),
			const graphics::Color& background = graphics::Color(1.0f, 1.0f, 1.0f, 0.0f));

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */

		void render(graphics::GUIRenderer* renderer) override;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Getters/Setters //
		/* //////////////////////////////////////////////////////////////////////////////// */

		/* ********************************************************* */
		// * Text *
		/* ********************************************************* */
		void setText(const String& text);
		String getText() const;

		void setTextSize(const float& size);
		float getTextSize() const;

		void setTextColor(const graphics::Color& color);
		graphics::Color getTextColor() const;

		/* ********************************************************* */
		// * Font *
		/* ********************************************************* */
		void setFont(const graphics::Font& font);
		graphics::Font getFont() const;

		/* ********************************************************* */
		// * Background *
		/* ********************************************************* */
		void setBackgroundColor(const graphics::Color& color);
		graphics::Color getBackgroundColor() const;
	};

}}

