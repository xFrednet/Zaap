#include "GUITextureFrame.h"

#include <graphics/API/Texture2D.h>
#include <gui/VertexBufferHelper.h>

namespace zaap { namespace gui {

	GUITextureFrame::GUITextureFrame(Point pos, int width, int height, graphics::API::Texture2D texture, GUIComponent* parent)
		: GUIComponent(4, 6, parent)
	{
		setTexture(texture);
		setPosition(pos);
		setPreferredSize(width, height);
	}

	GUITextureFrame::GUITextureFrame(Point pos, int width, int height, String textureFile, GUIComponent* parent)
		: GUIComponent(4, 6, parent)
	{
		setTexture(graphics::API::TextureCore::CreateTexture2D(textureFile));
		setPosition(pos);
		setPreferredSize(width, height);
	}

	void GUITextureFrame::updateVertexBuffer()
	{
		VertexBufferHelper helper(&m_VertexBuffer);

		helper.drawTexture(getGlobalPosition(), getWidth(), getHeight());

		helper.save();
	}
	uint GUITextureFrame::getWrappedWidth() const
	{
		return 0;
	}
	uint GUITextureFrame::getWrappedHeight() const
	{
		return 0;
	}

	void GUITextureFrame::render(graphics::GUIRenderer* renderer)
	{
		renderer->setTexure(m_Texture.get());
		m_VertexBuffer->draw();
	}

	void GUITextureFrame::setTexture(graphics::API::Texture2D texture)
	{
		if (!texture)
			return;

		m_Texture = texture;
		requestRedraw();
	}
	graphics::API::Texture2D GUITextureFrame::getTexture() const
	{
		return m_Texture;
	}

}}
