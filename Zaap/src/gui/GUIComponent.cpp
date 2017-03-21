#include "GUIComponent.h"

#include <util/UUID.h>
#include <util/Log.h>

#include <graphics/shader/Shader.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace gui {

	GUIComponent::GUIComponent(uint vertexCount, uint indexCount, GUIComponent* parent)
		: m_PaddingTop(0), m_PaddingBottom(0),
		m_PaddingLeft(0), m_PaddingRight(0),
		m_PreferredWidth(ZA_GUI_SIZE_WRAP_CONTENT), 
		m_PreferredHeight(ZA_GUI_SIZE_WRAP_CONTENT),
		m_Size(), m_Parent(parent),
		m_IsVisible(true)
	{
		// m_ID
		UUID uuid;
		RandomUUID(&uuid);
		char str[17] = {0};
		memcpy(str, uuid.Data, 16);
		m_ID = str;

		using namespace graphics::API;
		m_VertexBuffer = VertexBuffer::CreateVertexbuffer(sizeof(graphics::ZA_GUI_VERTEX), vertexCount, indexCount);

		ZA_INFO("New component with the ID: ", m_ID);
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
		// The default method does nothing yay
	}

	void GUIComponent::render(graphics::GUIRenderer* renderer)
	{
		m_VertexBuffer->draw();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // changed info informers // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUIComponent::newParent()
	{
		// A new parent... how does this even work?
	}

	void GUIComponent::moved()
	{
		// A child that learned moving how cute the parring is
		// probably the reason for this.
		// I think that this can be called funny anymore.
	}
	void GUIComponent::resized()
	{
	}

	void GUIComponent::childHasNewPreferrences(GUIComponent* child)
	{
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Setters and Getters // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	/* ********************************************************* */
	// * Parent *
	/* ********************************************************* */

	void GUIComponent::setParent(GUIComponent* parent)
	{
		m_Parent = parent;

		newParent();
		moved();
		updateVertexBuffer();
	}

	/* ********************************************************* */
	// * Position/X/Y *
	/* ********************************************************* */

	void GUIComponent::setPosition(const int& x, const int& y)
	{
		m_Size.X = x;
		m_Size.Y = y;

		// inform component
		moved();
		updateVertexBuffer();
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

	/* ********************************************************* */
	// * preferred size *
	/* ********************************************************* */

	void GUIComponent::setPreferredWidth(const int& width)
	{
		setPreferredSize(width, m_PreferredHeight);
	}
	void GUIComponent::setPreferredHeight(const int& height)
	{
		setPreferredSize(m_PreferredWidth, height);
	}
	void GUIComponent::setPreferredSize(const int& width, const int& height)
	{
		m_PreferredWidth = width;
		m_PreferredHeight = height;

		if (m_Parent)
		{
			m_Parent->childHasNewPreferrences(this);
		} 
		else {
			int pWidth = m_PreferredWidth;
			int pHeight = m_PreferredHeight;

			if (pWidth == ZA_GUI_SIZE_MATCH_PARENT)
				pWidth = ZA_GUI_SIZE_WRAP_CONTENT;

			if (pHeight == ZA_GUI_SIZE_MATCH_PARENT)
				pHeight = ZA_GUI_SIZE_WRAP_CONTENT;

			m_Size.Width = (pWidth == ZA_GUI_SIZE_WRAP_CONTENT) ? getWrappedWidth() : (uint)pWidth;
			m_Size.Height = (pHeight == ZA_GUI_SIZE_WRAP_CONTENT) ? getWrappedHeight() : (uint)pHeight;

			resized();
			updateVertexBuffer();
		}
	}

	/* ********************************************************* */
	// * size *
	/* ********************************************************* */
	void GUIComponent::setWidth(uint width)
	{
		setSize(width, m_Size.Height);
	}
	void GUIComponent::setHeight(uint height)
	{
		setSize(m_Size.Width, height);
	}
	void GUIComponent::setSize(uint width, uint height)
	{
		m_Size.Width = width;
		m_Size.Height = height;

		resized();
		updateVertexBuffer();
	}

	/* ********************************************************* */
	// * ID *
	/* ********************************************************* */
	void GUIComponent::setID(String ID)
	{
		m_ID = ID;
	}

	GUIComponent* GUIComponent::findComponentByID(const String& ID)
	{
		return nullptr;
	}
}}
