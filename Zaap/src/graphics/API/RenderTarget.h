#pragma once

#include <Common.h>
#include <graphics/Format.h>

namespace zaap {namespace graphics {
	struct Color;
	// <Enum>
	//		ZA_RENDERER_TARGET_TYPE
	//
	// <Description>
	//		This is only defined for the renderer.
	//
	typedef enum ZAAP_API ZA_RENDERER_TARGET_TYPE_ {
		ZA_RENDERER_TARGET_DEFAULT = 0,
		ZA_RENDERER_TARGET_CONTEXT_TARGET = 1,
		ZA_RENDERER_TARGET_CUSTOME_TARGET = 2
	} ZA_RENDERER_TARGET_TYPE;
}}

namespace zaap { namespace graphics { namespace API {
	
	class ZAAP_API RenderTarget
	{
	protected:
		typedef std::function<void()> UpdateListener;
		
		uint m_Width;
		uint m_Height;

		std::vector<UpdateListener> m_UpdateListeners;
		
		void informUpdateListeners() const;

		RenderTarget(const uint& width = 0, const uint& height = 0);
	public:
		virtual ~RenderTarget();

		void addUpdateListener(const UpdateListener& listener);

		virtual ZA_RESULT createTarget(const uint& width, const uint& height, const ZA_FORMAT& format) = 0;

		virtual void bindTexture(uint index) = 0;
		virtual void unbindTexture(uint index) = 0;

		uint getWidth() const;
		uint getHeight() const;

		virtual void clearRenderTarget(const Color& color) = 0;
		virtual void startTarget(void* depthStencil = nullptr) = 0;
	};

}}}

