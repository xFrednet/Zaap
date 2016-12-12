#pragma once

#include <Common.h>
#include <Types.h>

namespace zaap { namespace graphics { namespace API {
	
	class ZAAP_API Context
	{
	protected:
		static Context *s_Context;
		
		virtual void cleanup(void) = 0;
		virtual void swapBuffers(void) = 0;

		virtual ~Context() {}
	public:
		static void Create();

		static inline void Cleanup();
		static inline void SwapBuffers();
	};

}}}