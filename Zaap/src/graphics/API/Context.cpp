#include "Context.h"

#include <graphics/API/DXContext.h>
#include <util/Console.h>

using namespace zaap;
using namespace graphics;
using namespace API;

namespace zaap { namespace graphics { namespace API {

	Context* Context::s_Context = nullptr;

	void Context::Create(Window& window)
	{
		s_Context = new DX::DXContext(window);
	}

	void Context::Cleanup()
	{
		s_Context->cleanup();
		delete s_Context;
		ZAAP_CLEANUP_LOG("Context");
	}

	void Context::Resize(uint width, uint height)
	{
		if (s_Context) s_Context->resize(width, height);
	}

	void Context::SwapBuffers()
	{
		s_Context->swapBuffers();
	}

}}}
