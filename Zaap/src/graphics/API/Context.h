#pragma once

#include <Common.h>

#include <graphics/API/RenderTarget.h>

namespace zaap { namespace graphics { namespace API {
	
	class ZAAP_API Context
	{
	protected:
		static Context *s_Context;
		
		virtual ZA_RESULT init() = 0;

		virtual RenderTarget* getRenderTarget() = 0;
		virtual void prepareFrame() = 0;
		virtual void presentFrame() = 0;

	public:
		static ZA_RESULT Create();
		static void Cleanup();

		virtual ~Context() {}
		

		static RenderTarget* GetRenderTarget();
		static void PrepareFrame();
		static void PresentFrame();
	};

}}}
