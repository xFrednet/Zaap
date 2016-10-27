#pragma once

#include <Types.h>
#include <Common.h>

#include <graphics/Bitmap.h>
#include "API/Texture2D.h"
#include "API/VertexBuffer.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace zaap { namespace graphics {

	// x = origin             
	//                        
	//    ##########     ^    
	//        ##         |    
	//        ##       Height 
	//        ##         |    
	//        ##         v    
	//  <--  Width  -->      
	// This explanation is so bad :P
	// The values should be the values for a fontSize of 1.
	// To translate the struct members to the current size they are multiplied by the size.
	struct ZAAP_API ZA_CharMarix
	{
		float OrigenXOffset;
		float OrigenYOffset;

		float Width;
		float Height;

		ZA_CharMarix();
		ZA_CharMarix(const ZA_CharMarix &charMarix);

		ZA_CharMarix operator/(float a) const;
		ZA_CharMarix operator*(float a) const;
		
	};
	
	struct ZAAP_API ZA_CharacterInfo
	{
		char Character;
			
		Vec2 TexMinCoords;
		Vec2 TexMaxCoords;

		ZA_CharMarix CharMatirx;

		ZA_CharacterInfo();
		ZA_CharacterInfo(char c);
	};

	struct ZAAP_API ZA_CharVertex
	{
		Vec3 Position;
		Vec2 TexCoord;
	};

	typedef ZAAP_API enum FONT_FORMAT
	{
		// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
		ZAAP_FONT_128_CHARACTERS     = 0,
		//This format requires the user to set the chars to load
		ZAAP_FONT_UNKNOWN_CHARACTERS = 1
	} FONT_FORMAT;

	//
	// Font class
	//
	class ZAAP_API Font
	{
		//static methods
	public:

		static Mat4 CreateFontTransformationMatrix(const Vec3 &position, const float &fontSize);

		//This methods returns all the characters that are supported by a certain FONT_FORMAT
		static String GetFormatCharacters(FONT_FORMAT format);

		//This methods loads a FTT file and creates a Font object from it
		static Font LoadFTTFile(String file, FONT_FORMAT format);
		static Font LoadFTTFile(String file, String chars);

		//Members
	private:
		static uint const ZAAP_FONT_DEFAULT_BITMAP_SIZE = 1024;

		float m_Size;
		String m_Chars;

		// loaded chars
		API::Texture2D* m_CharSheet;
		std::vector<ZA_CharacterInfo> m_CharInfo;
		ZA_CharMarix m_MaxCharSize;

		//Methods
	public:
		Font();
		Font(String chars);

		//render
		API::VertexBuffer* getVertexBuffer(String string);
		void render(API::VertexBuffer *vb);

		//util
		uint getCharIndex(char c) const;
		uint getCharCount() const;
	};
		
}}
