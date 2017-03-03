#pragma once

#include <Common.h>
#include "API/Texture2D.h"
#include <events/EventManager.h>

namespace zaap { namespace graphics {
	struct Color;

	class ZAAP_API GUIRenderer
	{
	public:
		// <Method>
		//		CreateNewInstance
		//
		// <Descritpion>
		//		This creates a new GUIRenderer instance for the
		//		current API.
		//
		// <Note>
		//		The returned instance is created using the "new" keyword
		//		the requester should/has to delete the instance.
		//
		// <Input>
		//		instance::
		//			A pointer to a pointer of a uninitialized GUIRenderer;;
		//
		// <Return>
		//		A ZA_RESULT that indicates if the creation and 
		//		initialization was successful.
		//
		static ZA_RESULT CreateNewInstance(GUIRenderer** instance);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Class content //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		uint m_TargetWidth;
		uint m_TargetHeight;

		// <Value>
		//      m_RenderTarget
		// 
		// <Description>
		//      This is the rendering target.
		//
		// <Note>
		//      This usually gets created by the API renderer. 
		//      The last instance gets deleted in the 
		//      cleanupBaseRenderer3D method. This is only done if 
		//      m_HasCustomRenderTarget is false.
		//
		API::Texture2D* m_RenderTarget;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Initialization / Deconstruction //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		// <Constructor>
		//		GUIRenderer
		//
		// <Description>
		//		This initializes most values with 0 and adds 
		//		the windowCallback method to the event system.
		//
		GUIRenderer();

		// <Method>
		//		init
		//
		// <Description>
		//		This is called by CreateNewInstance it should
		//		initialize all components of the renderer and
		//		return a @ZA_RESULT that indicates the result.
		//
		// <Return>
		//		A @ZA_RESULT that indicates if the method executed
		//		successfully.
		//
		virtual ZA_RESULT init() = 0;

	public:
		// <Deconstructor>
		//		GUIRenderer
		//
		// <Description>
		//      This method deletes all the values that are created
		//      using the new operator. (This only includes the values that
		//      are inside this base GUIRenderer)
		//
		virtual ~GUIRenderer() {}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Window callback //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		// <Method>
		//      windowCallback
		//
		// <Description>
		//      The constructor adds this method as a windowCallback function.
		//      Resize events are passed to the resize method.
		//      
		void windowCallback(const Event& windowEvent);
	protected:
		// <Method>
		//      resize
		//
		// <Description>
		//      This method configures the RenderTarget size and
		//      some API related things.
		//
		// <Note>
		//      This method will be changed to add extra resize options 
		//      or to enable the user to set a target frame part
		//
		// <Input>
		//      width: 
		//          the new width.
		//      height: 
		//          the new height.
		//
		virtual void resize(uint width, uint height) = 0;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		// <Method>
		//		startRenderer
		//
		// <Descritpion>
		//		This prepares the RenderTarget, starts the GUIRenderer
		//		and probably does some other stuff.
		//
		void startRenderer();
	protected:
		// <Method>
		//      prepareFrame
		//
		// <Description>
		//      This method is called by startRenderer. <\n>
		//      It prepares the Frame in some different ways, just call it
		//      for the greater good of the engine.
		//      (Note: Some APIs might have some extra functions in here.)
		//
		virtual void prepareFrame() const = 0;
	
	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Draw Util //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// Nothing yet this will be done when I'm sure how this should work.

	};

}}

