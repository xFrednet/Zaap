#pragma once

#include <Common.h>

#include <gui/Rectangle.h>
#include <gui/Point.h>

#include <graphics/GUIRenderer.h>
#include <graphics/API/VertexBuffer.h>

#define ZA_GUI_SIZE_WRAP_CONTENT 0
#define ZA_GUI_SIZE_MATCH_PARENT -1

namespace zaap {namespace graphics {namespace API {
	class VertexBuffer;
}}}

namespace zaap { namespace gui {

	class GUIComponentGroup;
	class GUIManager;

	class ZAAP_API GUIComponent
	{
	private:
		friend class GUIComponentGroup;
		friend class GUIManager;
	protected:
		static bool s_IsRedrawRequested;

		uint m_PaddingTop;
		uint m_PaddingBottom;
		uint m_PaddingLeft;
		uint m_PaddingRight;

		uint m_MarginTop;
		uint m_MarginBottom;
		uint m_MarginLeft;
		uint m_MarginRight;

		// <Value>
		//		m_PreferredWidth
		//
		// <Descritpion>
		//		This holds the info about the preferred width. <\n>
		//		A value above zero indicates a pixel value, a value below or equal
		//		zero indicates a special width like: "wrap_content", "match_parent".
		//
		int m_PreferredWidth;
		// <Value>
		//		m_PreferredHeight
		//
		// <Descritpion>
		//		This holds the info about the preferred height. <\n>
		//		A positive value indicates a pixel value, a negative value
		//		indicates a special width like: "wrap_content", "match_parent".
		//
		int m_PreferredHeight;

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

		// <Value>
		//		m_IsVisible
		//
		// <Descritpion>
		//		This value indicates if the object is visible or
		//		hidden. A hidden value will/should not be rendered by the parent.
		//
		// <Note>
		//		This state also influences it's children.
		//
		bool m_IsVisible;

		// <Value>
		//		m_ID
		//
		// <Description>
		//		This holds the ID of the object. The object ID
		//		can be used by layouts.
		//
		// <Note>
		//		The object ID will be created using a UUDI if 
		//		none is set by outside sources.
		//
		String m_ID;

		graphics::API::VertexBuffer* m_VertexBuffer;

		GUIComponent(uint vertexCount, uint indexCount, GUIComponent* parent = nullptr);
	public:
		virtual ~GUIComponent();

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
		virtual void render(graphics::GUIRenderer* renderer);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // changed info informers // 
		/* //////////////////////////////////////////////////////////////////////////////// */
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
		virtual void moved();
		// <Method>
		//		resized
		//
		// <Description>
		//		This is called by the parent when the child 
		//		was resized. This is usually done by the parent.
		//
		virtual void resized();
		// <Method>
		//		updateVertexBuffer
		//
		// <Descritpion>
		//		This method is called when the object is moved, resized or
		//		changed in any shape or from that probably effects the VertexBuffer.
		//
		virtual void updateVertexBuffer() = 0;

		// <Method>
		//		childHasNewPreferrences
		//
		// <Description>
		//		This is called by the child wen a new 
		//		preferred width or height is set.
		//
		virtual void childHasNewPreferrences(GUIComponent* child);

		// <Function>
		//		requestRedraw
		//
		// <Description>
		//		This requests a redraw from the GUIManager.
		//
		void requestRedraw() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Setters and Getters // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		/* ********************************************************* */
		// * Parent *
		/* ********************************************************* */
	public:
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

		/* ********************************************************* */
		// * Position/X/Y *
		/* ********************************************************* */
	public:
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
		// * preferred size *
		/* ********************************************************* */
	public:
		// <Method>
		//		getPreferredWidth
		//
		// <Return>
		//		This returns the value of m_PreferredWidth.
		//
		inline int getPreferredWidth() const
		{
			return m_PreferredWidth;
		}
		// <Method>
		//		getPreferredHeight
		//
		// <Return>
		//		This returns the value of m_PreferredHeight.
		//
		inline int getPreferredHeight() const
		{
			return m_PreferredWidth;
		}

		// <Method>
		//		setPreferredWidth
		//
		// <Input>
		//		width::
		//			The new width for m_PreferredWidth.;;
		//
		void setPreferredWidth(const int& width);
		// <Method>
		//		setPreferredHeight
		//
		// <Input>
		//		height::
		//			The new preferred height of this object.;;
		//
		void setPreferredHeight(const int& height);
		// <Method>
		//		setPreferredSize
		//
		// <Input>
		//		width::
		//			The new preferred width.;;
		//		height::
		//			The new preferred height.;;
		//
		void setPreferredSize(const int& width, const int& height);

	protected:
		// <Method>
		//		getWrappedWidth
		//
		// <Return>
		//		This returns the width that the object would take
		//		if the preferred width is set to wrap_content.
		//
		virtual uint getWrappedWidth() const = 0;
		// <Method>
		//		getWrappedHeight
		//
		// <Return>
		//		This returns the height that the object would take
		//		if the preferred height is set to wrap_content.
		//
		virtual uint getWrappedHeight() const = 0;
		
		/* ********************************************************* */
		// * size *
		/* ********************************************************* */
	public:
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

	protected:
		// <Method>
		//		setWidth
		//
		// <Note>
		//	  - The width is set without any extra checks.
		//	  - This calls the resized method.
		//	  - This calls the updateVertexBuffer method.
		//
		// <Input>
		//		width::
		//			The new width of the object.;;
		//
		inline void setWidth(uint width);
		// <Method>
		//		setHeight
		//
		// <Note>
		//	  - The height is set without any extra checks.
		//	  - This calls the @resized method.
		//	  - This calls the @updateVertexBuffer method.
		//	  - This uses the @setSize method to 
		//------------------------------
		//		width::
		//			The new height of the object.;;
		//
		inline void setHeight(uint height);
		// <Method>
		//		setSize
		//
		// <Note>
		//	  - The width and height are set without any extra checks.
		//	  - This calls the resized method.
		//	  - This calls the updateVertexBuffer method.
		//
		// <Input>
		//		width::
		//			The new width of the object.;;
		//		height::
		//			The new height of the object.;;
		//
		inline void setSize(uint width, uint height);

		/* ********************************************************* */
		// * margin *
		/* ********************************************************* */
	public:
		// <Method>
		//		getTopMargin
		//
		// <Return>
		//		The returns the margin for the top.
		//
		inline uint getTopMargin() const
		{
			return m_MarginTop;
		}
		// <Method>
		//		getBottomMargin
		//
		// <Return>
		//		The returns the margin for the bottom.
		//
		inline uint getBottomMargin() const
		{
			return m_MarginBottom;
		}
		// <Method>
		//		getLeftMargin
		//
		// <Return>
		//		The returns the margin for the left side.
		//
		inline uint getLeftMargin() const
		{
			return m_MarginLeft;
		}
		// <Method>
		//		getRightMargin
		//
		// <Return>
		//		The returns the margin for the right side.
		//
		inline uint getRightMargin() const
		{
			return m_MarginRight;
		}

		// <Method>
		//		setMargin
		//
		// <Note>
		//		
		void setMargin(const uint& topMargin, const uint& bottomMargin, 
			const uint& leftMargin, const uint& rightMargin);

		/* ********************************************************* */
		// * hidden value *
		/* ********************************************************* */
	public:
		// <Method>
		//		isVisible
		//
		// <Return>
		//		This returns the state of the m_Visible value;
		//
		inline bool isVisible() const
		{
			return m_IsVisible;
		}
		// <Method>
		//		setVisibility
		//
		// <Input>
		//		visible::
		//			The new value for m_Visible.;;
		//
		inline void setVisibility(bool visible)
		{
			m_IsVisible = visible;
		}

		/* ********************************************************* */
		// * ID *
		/* ********************************************************* */
		
		// <Method>
		//		getID
		//
		// <Return>
		//		This returns the current ID of this object.
		//
		inline String getID() const
		{
			return m_ID;
		}
		// <Method>
		//		setID
		//
		// <Input>
		//		ID::
		//			The new ID of the object.;;
		//
		inline void setID(String ID);
		// <Method>
		//		findComponentByID
		//
		// <Description>
		//		This method searches for the given ID among
		//		it's children and their children. This returns
		//		NULL if no component was found.
		//
		// <Input>
		//		ID::
		//			The ID of the object that is searched for.;;
		//
		// <Return>
		//		This returns the GUIComponent if it was found. This method
		//		returns a null pointer otherwise.
		//
		virtual GUIComponent* findComponentByID(const String& ID);

	};

}}
