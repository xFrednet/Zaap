#pragma once

#include <Common.h>
#include "GUIComponent.h"

namespace zaap { namespace gui {
	
	class ZAAP_API GUIComponentGroup : public GUIComponent
	{
	protected:
		std::vector<GUIComponent*> m_Members;
	public:    vb
		virtual ~GUIComponentGroup() override;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // util //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		virtual void update() override;
		virtual void render(graphics::GUIRenderer* renderer) override;


		/* //////////////////////////////////////////////////////////////////////////////// */
		// // changed info informers //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		virtual void moved() override;
		virtual void resized() override;

		// <Method>
		//		childHasNewPreferrences
		//
		// <Description>
		//		This is called by the child wen a new 
		//		preferred width or height is set.
		//
		virtual void childHasNewPreferrences(GUIComponent* child) override;
		// <Method>
		//		newChild
		//
		// <Description>
		//		This is called when a new child is added to
		//		the m_Members list.;;
		//
		virtual void newChild(GUIComponent* child);

		// <Method>
		//		updateLayout
		//
		// <Description>
		//		This is a pure virtual function that is called when the
		//		layout of this group should be updated/recalculated.
		//
		virtual void updateLayout() = 0;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Setters and Getters //
		/* //////////////////////////////////////////////////////////////////////////////// */
		virtual uint getWrappedWidth() const override;
		virtual uint getWrappedHeight() const override;

		/* ********************************************************* */
		// * Members *
		/* ********************************************************* */
	public:
		virtual GUIComponent* findComponentByID(const String& ID) override;

		// <Method>
		//		add
		//
		// <Note>
		//	  - This calls the @newChild method.
		//	  - This calls the @updateLayout method.
		//
		// <Input>
		//		component::
		//			The new GUIComponent that should be added to 
		//			this GUIComponentGroup.;;
		//
		virtual void add(GUIComponent* component);
		// <Method>
		//		remove
		//
		// <Note>
		//	  - This calls the @remove method with the ID
		//		of the object.
		//	  - This calls the @updateLayout method.
		//
		// <Input>
		//		component::
		//			The component that should be removed.;;
		//
		virtual void remove(GUIComponent* component);
		// <Method>
		//		remove
		//
		// <Note>
		//	  - This calls the @updateLayout method.
		//
		// <Input>
		//		ID::
		//			The ID of the component that should be removed.;;
		//
		virtual void remove(const String& ID);
	};

}}

