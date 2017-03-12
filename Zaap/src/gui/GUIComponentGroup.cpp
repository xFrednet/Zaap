#include "GUIComponentGroup.h"

namespace zaap { namespace gui {

	GUIComponentGroup::~GUIComponentGroup()
	{
		while (!m_Members.empty())
		{
			delete m_Members[0];
			m_Members.erase(m_Members.begin());
		}
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUIComponentGroup::update()
	{
		for (GUIComponent* child : m_Members)
		{
			child->update();
		}
	}
	void GUIComponentGroup::render(graphics::GUIRenderer* renderer)
	{
		for (GUIComponent* child : m_Members)
		{
			child->render(renderer);
		}
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // changed info informers //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUIComponentGroup::moved()
	{
		for (GUIComponent* child : m_Members)
		{
			child->moved();
		}
	}
	void GUIComponentGroup::resized()
	{
		updateLayout();
	}
	void GUIComponentGroup::childHasNewPreferrences(GUIComponent* child)
	{
		updateLayout();
	}
	void GUIComponentGroup::newChild(GUIComponent* child)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Setters and Getters //
	/* //////////////////////////////////////////////////////////////////////////////// */
	uint GUIComponentGroup::getWrappedWidth() const
	{
		uint pWidth;
		uint width = 0;
		for (GUIComponent* child : m_Members)
		{
			pWidth = child->getPreferredWidth();

			if (pWidth > 0)
				width += pWidth;
			else
				width += getWrappedWidth();
		}
		return width;
	}
	uint GUIComponentGroup::getWrappedHeight() const
	{
		uint pHeight;
		uint height = 0;
		for (GUIComponent* child : m_Members)
		{
			pHeight = child->getPreferredHeight();

			if (pHeight > 0)
				height += pHeight;
			else
				height += getWrappedHeight();
		}
		return height;
	}

	GUIComponent* GUIComponentGroup::findComponentByID(const String& ID)
	{
		if (ID == m_ID)
			return this;

		GUIComponent* component;
		for (GUIComponent* child : m_Members)
		{
			if (child->getID() == ID)
				return child;

			component = child->findComponentByID(ID);
			if (component)
				return component;
		}

		return nullptr;
	}
}}

