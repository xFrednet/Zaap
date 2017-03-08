#include "GUIComponent.h"

namespace zaap { namespace gui {
	GUIComponent::GUIComponent(GUIComponent* parent, Rectangle size)
		: m_PaddingTop(0), m_PaddingBottom(0),
		m_PaddingLeft(0), m_PaddingRight(0),
		m_Size(size), m_Parent(parent)
	{
	}

	GUIComponent::~GUIComponent()
	{
		// I may want to inform the parent that it's child just died... nawww
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUIComponent::update()
	{
		// The default function does nothing yay
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Setters and Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	/* ********************************************************* */
	// * Parent *
	/* ********************************************************* */
	void GUIComponent::newParent()
	{
		// A new parent... how does this even work?
	}

	void GUIComponent::setParent(GUIComponent* parent)
	{
		m_Parent = parent;

		newParent();
		moved(getPosition(), getPosition(), getGlobalPosition());
	}

	/* ********************************************************* */
	// * Position/X/Y *
	/* ********************************************************* */
	void GUIComponent::moved(const Point& oldPos, const Point& newPos, const Point& globalPos)
	{
		// A child that learned moving how cute the parring is
		// probably the reason for this.
		// I think that this can be called funny anymore.
	}

	void GUIComponent::setPosition(const int& x, const int& y)
	{
		Point oldPoint = m_Size.Position;
		m_Size.X = x;
		m_Size.Y = y;
		moved(oldPoint, getPosition(), getGlobalPosition());
	}
	void GUIComponent::setPosition(const Point& position)
	{
		setPosition(position.X, position.Y);
	}
	void GUIComponent::setX(const int& x)
	{
		setPosition(x, m_Size.Y);
	}
	void GUIComponent::setY(const int& y)
	{
		setPosition(m_Size.X, y);
	}
}}