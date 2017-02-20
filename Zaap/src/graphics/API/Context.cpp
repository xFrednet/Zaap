#include "Context.h"

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/DX/DXContext.h>
#include <util/Log.h>

namespace zaap { namespace graphics { namespace API {

	Context* Context::s_Context = nullptr;

	void Context::Create()
	{
		s_Context = new DX::DXContext();
	}

	void Context::Cleanup()
	{
		s_Context->cleanup();
		delete s_Context;
		ZA_LOG_CLEANUP();
	}

	void Context::SwapBuffers()
	{
		s_Context->swapBuffers();
	}

}}}
