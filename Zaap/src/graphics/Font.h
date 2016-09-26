#pragma once

#include <Types.h>
#include <Common.h>

#include <graphics/Bitmap.h>

struct FT_LibraryRec_;
struct FT_FaceRec_;
struct FT_Bitmap_;

namespace zaap { namespace graphics {

	//            <-Width-->   
	//                            
	//       ^    ##########     ^
	//       |        ##         |
	// yOffset        ##       Height
	//       |        ##         |
	//       v        ##         v
	//       x <--TotalWidth-->
	//       x = origen
	// This explanation is so bad :P
	struct ZAAP_API ZA_CharMarix
	{
		uint OrigenXOffset;
		uint OrigenYOffset;

		//width and height should be the actual width and height widthout any padding
		uint Width;
		uint Height;

		float TotalWidth;
	};
	
	struct ZAAP_API ZA_CharacterInfo
	{
		char Character;
			
		math::Vec2 TexMinCoords;
		math::Vec2 TexMaxCoords;

		ZA_CharMarix CharMatirx;

		ZA_CharacterInfo();
		ZA_CharacterInfo(char c);
	};

	typedef ZAAP_API enum FONT_FORMAT
	{
		ZAAP_FONT_128_CHARACTERS     = 0,
		ZAAP_FONT_UNKNOWN_CHARACTERS = 1
	} FONT_FORMAT;

	//
	// Font class
	//
	class ZAAP_API Font
	{
		//Static Values
	private:
		static FT_LibraryRec_ *s_FTLib;
		static bool s_IsFTLibInitialized;
		
		//static methods
	public:
		// This method is called to init the FreeType library. 
		// It is called by the Application class at the start of the program.
		static void Init();
		// This method is called to cleanup the FreeType library. 
		// It is called by the Application class from the cleanup method.
		static void Cleanup();

		//Members
	private:
		static uint const ZAAP_FONT_DEFAULT_BITMAP_SIZE = 1024;
		
		String m_File;

		uint m_Size;
		FONT_FORMAT m_Format;
		Bitmap m_Bitmap;
		std::map<char, ZA_CharacterInfo> m_CharInfo;
	private:
		void copyToBitmap(const uint &x, const uint &y, const FT_Bitmap_ &bitmap);
	public:
		Font(String file, FONT_FORMAT format);

		void loadFTTFile(String file);
		math::Vec2 getPixelCoord(uint x, uint y) const;
	};
		
}}
