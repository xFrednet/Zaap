#pragma once

#include <Common.h>

#include <gui/Rectangle.h>
#include <gui/Point.h>

namespace zaap
{
	namespace graphics
	{
		class GUIRenderer;
	}
}

namespace zaap { namespace gui {

	class ZAAP_API GUIComponent
	{
	protected:
		uint m_PaddingTop;
		uint m_PaddingBottom;
		uint m_PaddingLeft;
		uint m_PaddingRight;

		// <Value>
		//		m_Size
		//
		// <Description>
		//		This holds the information about the position 
		//		and the size of this object.
		//
		// <Note>
		//	  - The position is the position in parent space.
		//		this means that the position is offset by 
		//		the parent object.
		//	  - Any change to the Position that is done though methods 
		//		calls the moved method. You might want to call
		//		it for every change.
		//	  - The size only refers to the actual size of the object
		//		the padding is not included and has to be handled by the 
		//		layout thing that should be created... add it to the to-do list!!
		//
		Rectangle m_Size;
		
		// <Value>
		//		m_Parrent
		//
		// <Descritpion>
		//		This is a pointer to the parent object.
		//		the parent usually influences the position color
		//		and some other stuff.<\n>
		//		A null pointer indicates that no parent is set.
		//
		// <Note>
		//		Most of the functional methods like render, update
		//		resize... are called from the parent. This means that 
		//		a object that has no parent is/can be pretty useless.
		//		But I wont tell you what to do and what not to do.
		//
		GUIComponent* m_Parent;

		GUIComponent(GUIComponent* parent = nullptr, Rectangle size = Rectangle(0, 0, 0, 0));
		virtual ~GUIComponent();
	public:

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Method>
		//		update
		//
		// <Description>
		//		This is a virtual method that is can be overridden
		//		by the GUIComponents.
		//
		// <Note>
		//	  - This is usually called by the parent. 
		//	  - This does nothing by default.
		//
		virtual void update();
		// <Method>
		//		render
		//
		// <Description>
		//		This method should render the GUIComponent
		//		and it's children.
		//
		// <Input>
		//		renderer::
		//			The GUIRenderer that is used to render the GUI.
		//
		virtual void render(graphics::GUIRenderer* renderer) = 0;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Setters and Getters // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		/* ********************************************************* */
		// * Parent *
		/* ********************************************************* */

		// <Method>
		//		hasParent
		//
		// <Return>
		//		This returns true if the m_parent value is something
		//		different than a null pointer.
		//
		inline bool hasParent() const
		{
			return (m_Parent) ? true : false;
		}
		// <Method>
		//		getParent
		//
		// <Return>
		//		This returns the pointer to the parent object
		//		this can also return null if m_Parent wasn't set.
		//
		inline GUIComponent* getParent()
		{
			return m_Parent;
		}
		// <Method>
		//		getParent
		//
		// <Return>
		//		This returns the pointer to the parent object
		//		this can also return null if m_Parent wasn't set.
		//
		inline GUIComponent const* getParent() const
		{
			return m_Parent;
		}

	protected:
		// <Method>
		//		newParent
		//
		// <Description>
		//		This method is called if a new parent was set
		//		by a method.
		//
		// <Note>
		//	  - The m_Parent value is already changed to the new parent.
		//	  - The moved method will also be called after this call.
		//	  - This method is also called if the parent is set to null.
		//
		virtual void newParent();
		
		// <Method>
		//		setParent
		//
		// <Descritpion>
		//		This sets the m_Parent to the submitted value. <\n>
		//		This method will call the @newParent and the @moved method.
		//
		// <Note>
		//		This function is protected because it should be called
		//		by the parent.
		//
		// <Input>
		//		parent::
		//			The new value for m_Parent.;;
		//
		void setParent(GUIComponent* parent);
	public:
		/* ********************************************************* */
		// * Position/X/Y *
		/* ********************************************************* */

		// <Method>
		//		getX
		//
		// <Return>
		//		This returns the X value without any padding.
		//
		inline int getX() const
		{
			return m_Size.X;
		}
		// <Method>
		//		getY
		//
		// <Return>
		//		This returns the Y value without any padding.
		//
		inline int getY() const
		{
			return m_Size.Y;
		}
		// <Method>
		//		getPosition
		//
		// <Return>
		//		This returns the position of this object without any padding.
		//
		inline Point getPosition() const
		{
			return m_Size.Position;
		}

		// <Method>
		//		getGlobalX
		//
		// <Return>
		//		This returns the X value with the offset of the parent.
		//
		inline int getGlobalX() const
		{
			if (m_Parent)
				return m_Parent->getGlobalX() + getX();
			else
				return getX();
		}
		// <Method>
		//		getGlobalY
		//
		// <Return>
		//		This returns the Y value with the offset of the parent.
		//
		inline int getGlobalY() const
		{
			if (m_Parent)
				return m_Parent->getGlobalY() + getY();
			else
				return getY();
		}
		// <Method>
		//		getGlobalPosition
		//
		// <Return>
		//		This returns the position with the offset of the parent.
		//
		inline Point getGlobalPosition() const
		{
			if (m_Parent)
				return m_Parent->getGlobalPosition() + getPosition();
			else
				return getPosition();
		}
	protected:
		// <Method>
		//		moved
		//
		// <Description>
		//		This method is called if the object is moved.
		//		This is also the case if the parent object is moved.
		//
		// <Note>
		//		The X and Y value of m_Size is already set when this
		//		method is called.
		//
		// <Input>
		//		oldPos::
		//			The old position of the Component.;;
		//		newPos::
		//			The new position of the Component.;;
		//		globalPos::
		//			The new position in global space. This is
		//			only different if it has a parent;;
		//
		virtual void moved(const Point& oldPos, const Point& newPos, const Point& globalPos);
	public:
		// <Method>
		//		setPosition
		//
		// <Note>
		//		This calls the moved method.
		//
		// <Input>
		//		x::
		//			The new X value.;;
		//		y::
		//			The new Y Value.;;
		//
		inline void setPosition(const int& x, const int& y);
		// <Method>
		//		setPosition
		//
		// <Note>
		//		This calls the moved method.
		//
		// <Input>
		//		position::
		//			The new position.;;
		//
		inline void setPosition(const Point& position);
		// <Method>
		//		setX
		//
		// <Note>
		//		This calls the moved method.
		//
		// <Input>
		//		x::
		//			The new X value.;;
		//
		inline void setX(const int& x);
		// <Method>
		//		setY
		//
		// <Note>
		//		This calls the moved method.
		//
		// <Input>
		//		y::
		//			The new y value.;;
		//
		inline void setY(const int& y);

		/* ********************************************************* */
		// * size *
		/* ********************************************************* */

		// <Method>
		//		getWidth
		//
		// <Return>
		//		This returns the actual width of this object.
		//
		inline uint getWidth() const
		{
			return m_Size.Width;
		}
		// <Method>
		//		getHeight
		//
		// <Return>
		//		This returns the actual height of this object
		//
		inline uint getHeight() const
		{
			return m_Size.Height;
		}
		// <Method>
		//		getSize
		//
		// <Return>
		//		This returns the size of this component.
		//
		inline Rectangle getSize() const
		{
			return m_Size;
		}

		// <Method>
		//		getTotalWidth
		//
		// <Return>
		//		This returns the total width including the padding.
		//
		inline uint getTotalWidth() const
		{
			return m_PaddingLeft + getWidth() + m_PaddingRight;
		}
		// <Method>
		//		getTotalHeight
		//
		// <Return>
		//		This returns the total height including the padding.
		//
		inline uint getTotalHeight() const
		{
			return m_PaddingTop + getHeight() + m_PaddingBottom;
		}
		// <Method>
		//		getTotalSize
		//
		// <Return>
		//		This returns the total size including the padding.
		//
		inline Rectangle getTotalSize() const
		{
			return Rectangle(m_Size.X - m_PaddingLeft,
				m_Size.Y - m_PaddingTop,
				getTotalWidth(),
				getTotalHeight());
		}

	};

}}