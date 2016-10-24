#include "Context.h"

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/DX/DXContext.h>
#include <util/Console.h>

using namespace zaap;
using namespace graphics;
using namespace API;

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
		ZAAP_CLEANUP_LOG("Context");
	}

	void Context::SwapBuffers()
	{
		s_Context->swapBuffers();
	}

}}}
