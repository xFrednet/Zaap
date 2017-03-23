#pragma once

#include <Common.h>

#include "..\GUIComponent.h"

namespace zaap { namespace graphics { namespace API {
	class Texture2D;
}}}

namespace zaap { namespace gui {
	
	class ZAAP_API GUITextureFrame : public GUIComponent
	{
	protected:
		graphics::API::Texture2D* m_Texture;

	public:
		GUITextureFrame(Point pos, int width, int height, graphics::API::Texture2D* texture, GUIComponent* parent = nullptr);
		GUITextureFrame(Point pos, int width, int height, String textureFile, GUIComponent* parent = nullptr);

	protected:
		void updateVertexBuffer() override;
		uint getWrappedWidth() const override;
		uint getWrappedHeight() const override;

		void render(graphics::GUIRenderer* renderer) override;

	public:
		void setTexture(graphics::API::Texture2D* texture);
		graphics::API::Texture2D* getTexture() const;
	};

}}
