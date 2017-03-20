#pragma once

#include <Common.h>

#include <gui/GUIComponent.h>

namespace zaap { namespace gui {

	class ZAAP_API GUIManager
	{
	private:
		graphics::GUIRenderer* m_Renderer;

		std::vector<GUIComponent*> m_Members;

	public:
		GUIManager();
		ZA_RESULT init();

		~GUIManager();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */
		void render();
		void update();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Members //
		/* //////////////////////////////////////////////////////////////////////////////// */
		GUIComponent* findComponentByID(const String& ID);

		virtual void add(GUIComponent* component);
		virtual void remove(GUIComponent* component);
		virtual void remove(const String& ID);
	};
}}
