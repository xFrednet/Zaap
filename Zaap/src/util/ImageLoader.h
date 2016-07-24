#pragma once

#include "Types.h"

namespace zaap
{
	namespace graphics{
	}

	class ZAAP_API ImageLoader
	{
	private:
		static bool isFreeImageInit;
	public:
		static void Init();
		static void Cleanup();

		static byte* Load(const char *filePath, uint *width, uint *height, uint *bits, bool flipY = true);
		static byte* Load(String &filePath, uint *width, uint *height, uint *bits, bool flipY = true);
	};
}
