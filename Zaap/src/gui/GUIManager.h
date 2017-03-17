#pragma once

#include <Common.h>

#include <gui/GUIComponent.h>
#include "GUIComponentGroup.h"

namespace zaap { namespace gui {

	class ZAAP_API GUIManager : GUIComponentGroup
	{
	private:
		graphics::GUIRenderer* m_Renderer;

	public:
		GUIManager();
	};
}}
