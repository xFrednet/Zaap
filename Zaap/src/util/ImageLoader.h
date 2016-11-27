#pragma once

#include <Common.h>
#include <Types.h>

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

		static ZA_RESULT Load(const char *filePath, uint *width, uint *height, uint *bits, byte** bytes, bool flipY = true);
		static ZA_RESULT Load(String &filePath, uint *width, uint *height, uint *bits, byte** bytes, bool flipY = true);
	};
}
