#pragma once

#include "Common.h"

namespace zaap { namespace graphics {
	
	class ZAAP_API Shader
	{
	public:
		virtual void start() const = 0;
		virtual void stop() const = 0;

		virtual void cleanup() = 0;
	};

}}