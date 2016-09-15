#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Loader.h>
#include <app/Window.h>

namespace zaap { namespace graphics { namespace API {
	
	class ZAAP_API Context
	{
	protected:
		static Context *s_Context;
		
		virtual void cleanup(void) = 0;
		virtual void swapBuffers(void) = 0;
		virtual void resize(uint width, uint height) = 0;

	public:
		static void Create(Window &window);

		static void Cleanup();
		static void SwapBuffers();

		static void Resize(uint width, uint height);
	};

}}}