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
	// x  <-Width-->          
	//                        
	//    ##########     ^    
	//        ##         |    
	//        ##       Height 
	//        ##         |    
	//        ##         v    
	//  <--TotalWidth-->      
	// This explanation is so bad :P
	// The values should be the values for a fontSize of 1.
	// To translate the struct members to the current size they are multiplied by the size.
	struct ZAAP_API ZA_CharMarix
	{
		float OrigenXOffset;
		float OrigenYOffset;

		//width and height should be the actual width and height without any padding
		float Width;
		float Height;

		float TotalWidth;

		ZA_CharMarix();
		ZA_CharMarix(const ZA_CharMarix &charMarix);

		ZA_CharMarix operator/(float a) const;
		ZA_CharMarix operator*(float a) const;
		
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

	struct ZAAP_API ZA_CharVertex
	{
		math::Vec3 Position;
		math::Vec2 TexCoord;
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

		static math::Mat4 CreateFontTransformationMatrix(const math::Vec3 &position, const float &fontSize);

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
		Bitmap m_Bitmap;

		API::Texture2D* m_CharSheet;
		API::VertexBuffer* m_VertexBuffer;

		std::vector<ZA_CharacterInfo> m_CharInfo;

		//Methods
	private:
		void generateVertexBuffer();
	public:
		Font();
		Font(String chars);

		//render
		void render(String string) const;

		//util
		uint getCharIndex(char c) const;
		uint getCharCount() const;

		math::Vec2 getPixelCoord(uint x, uint y) const;
	};
		
}}
