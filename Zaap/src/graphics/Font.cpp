#include "Font.h"

namespace zaap { namespace graphics {
		
	FT_Library Font::s_FTLib;
	bool Font::s_IsFTLibInitialized;

	void Font::Init()
	{
		FT_Error error = FT_Init_FreeType(&s_FTLib);
		if (error)
		{
			//TODO deal with the Error
		}
	}

}}
