#include "RenderTarget.h"

#include <graphics/Color.h>

namespace zaap { namespace graphics { namespace API {
	
	void RenderTarget::informUpdateListeners() const
	{
		for (UpdateListener listener : m_UpdateListeners)
		{
			listener();
		}
	}

	RenderTarget::RenderTarget(const uint& width, const uint& height)
		: m_Width(width),
		m_Height(height)
	{
	}
	RenderTarget::~RenderTarget()
	{
	}

	void RenderTarget::addUpdateListener(const UpdateListener& listener)
	{
		m_UpdateListeners.push_back(listener);
	}

	uint RenderTarget::getWidth() const
	{
		return m_Width;
	}
	uint RenderTarget::getHeight() const
	{
		return m_Height;
	}

}}}
