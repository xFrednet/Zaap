#include "GUIComponent.h"

#include <util/UUID.h>
#include <util/Log.h>

#include <graphics/shader/Shader.h>
#include <graphics/API/VertexBuffer.h>

namespace zaap { namespace gui {

	//static value
	bool GUIComponent::s_IsRedrawRequested = true;

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

		ZA_ASSERT((vertexCount != 0 || indexCount == 0))
		if (vertexCount != 0 || indexCount != 0)
		{
			using namespace graphics::API;
			m_VertexBuffer = VertexBufferCore::CreateVertexBufferCore(sizeof(graphics::ZA_GUI_VERTEX), vertexCount, indexCount);
		}

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
	void GUIComponent::changedMargin()
	{
	}
	void GUIComponent::childHasNewPreferrences(GUIComponent* child)
	{
	}

	void GUIComponent::requestRedraw() const
	{
		s_IsRedrawRequested = true;
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
		requestRedraw();
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
			requestRedraw();
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
		requestRedraw();
	}

	/* ********************************************************* */
	// * margin *
	/* ********************************************************* */
	void GUIComponent::setTopMargin(const uint& topMargin)
	{
		setMargin(m_MarginTop, m_MarginBottom, m_MarginLeft, m_MarginRight);
	}
	void GUIComponent::setBottomMargin(const uint& bottomMargin)
	{
		setMargin(m_MarginTop, m_MarginBottom, m_MarginLeft, m_MarginRight);
	}
	void GUIComponent::setLeftMargin(const uint& leftMargin)
	{
		setMargin(m_MarginTop, m_MarginBottom, m_MarginLeft, m_MarginRight);
	}
	void GUIComponent::setRightMargin(const uint& rightMargin)
	{
		setMargin(m_MarginTop, m_MarginBottom, m_MarginLeft, m_MarginRight);
	}
	
	void GUIComponent::setMargin(const uint& topMargin, const uint& bottomMargin, const uint& leftMargin, const uint& rightMargin)
	{
		m_MarginTop = topMargin;
		m_MarginBottom = bottomMargin;
		m_MarginLeft = leftMargin;
		m_MarginRight = rightMargin;

		changedMargin();
		updateVertexBuffer();
		requestRedraw();
	}

	/* ##################################### */
	// # content area #
	/* ##################################### */
	Point GUIComponent::getContentPosition() const
	{
		return (getPosition() + Point(m_MarginLeft, m_MarginTop));
	}
	Point GUIComponent::getGlobalContentPosition() const
	{
		return (getGlobalPosition() + Point(m_MarginLeft, m_MarginTop));
	}
	uint GUIComponent::getContentWidth() const
	{
		if ((m_MarginLeft + m_MarginRight) >= getWidth())
			return 0;
		
		return getWidth() - (m_MarginLeft + m_MarginRight);
	}
	uint GUIComponent::getContentHeight() const
	{
		if ((m_MarginTop + m_MarginBottom) >= getHeight())
			return 0;

		return getHeight() - (m_MarginTop + m_MarginBottom);
	}

	Rectangle GUIComponent::getContentArea() const
	{
		return Rectangle(getPosition(), getContentWidth(), getContentHeight());
	}
	Rectangle GUIComponent::getGlobalContentArea() const
	{
		return Rectangle(getGlobalPosition(), getContentWidth(), getContentHeight());
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
