#pragma once

#include <Common.h>

#include "..\GUIComponent.h"

namespace zaap { namespace gui {
		
	class ZAAP_API GUIBackground : public GUIComponent
	{
	protected:
		void updateVertexBuffer() override;
		uint getWrappedWidth() const override;
		uint getWrappedHeight() const override;
	public:
		GUIBackground(GUIComponent* parent = nullptr);
		GUIBackground(Point pos, uint width, uint height);
	};
}}
