#include "Context.h"

#include <graphics/API/DX/DXContext.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace API {

	Context* Context::s_Context = nullptr;

	ZA_RESULT Context::Create()
	{
		s_Context = new DX::DXContext();
		return s_Context->init();
	}

	void Context::Cleanup()
	{
		delete s_Context;
		ZA_LOG_CLEANUP();
	}

	RenderTarget* Context::GetRenderTarget()
	{
		return s_Context->getRenderTarget();
	}
	void Context::PrepareFrame()
	{
		s_Context->prepareFrame();
	}
	void Context::PresentFrame()
	{
		s_Context->presentFrame();
	}

}}}
