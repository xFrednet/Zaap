#pragma once

#include <Common.h>

#include "..\GUIComponent.h"

namespace zaap { namespace gui {
	
	class ZAAP_API GUILabel : public GUIComponent
	{
	protected:
		String m_Text;
		float m_TextSize;
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
		
		GUILabel(String text = "", GUIComponent* parent = nullptr);
		GUILabel(String text, float textSize, GUIComponent* parent = nullptr);
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Getters/Setters //
		/* //////////////////////////////////////////////////////////////////////////////// */
		void setText(const String& text);
		String getText() const;

		void setTextSize(const float& size);
		float getTextSize() const;

		void setTextColor(const graphics::Color& color);
		graphics::Color getTextColor() const;

		void setBackgroundColor(const graphics::Color& color);
		graphics::Color getBackgroundColor() const;
	};

}}

