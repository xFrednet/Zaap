#pragma once

#include <Types.h>
#include <Common.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace zaap { namespace graphics {

	class ZAAP_API Font
	{
	private:
		static FT_Library s_FTLib;
		static bool s_IsFTLibInitialized;
	
	public:
		static void Init();
		static void Cleanup();
	};
		
}}
