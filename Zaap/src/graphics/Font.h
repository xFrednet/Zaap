#pragma once

#include <Types.h>
#include <Common.h>

#include <graphics/Bitmap.h>
#include "API/Texture2D.h"
#include "API/VertexBuffer.h"

#pragma warning(push)
#pragma warning(disable: 4251)

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_FONT_CHAR_MATRIX //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {

	// ZA_FONT_CHAR_MATRIX
	//      +-----------------------------+<\n>
	//      |                             |<\n>
	//      |  #<XO><---Width---->        |<\n>
	//      |  ^                      ^   |<\n>
	//      |  YO                     |   |<\n>
	//      |  v                      |   |<\n>
	//      |  ^    ##############    |   |<\n>
	//      |  |    ##############    |   |<\n>
	//      |  |          ##          TH  |<\n>
	//      |  H          ##          |   |<\n>
	//      |  |          ##          |   |<\n>
	//      |  |          ##          |   |<\n>
	//      |  v          ##          v   |<\n>
	//      |                             |<\n>
	//      |   <---------TW--------->    |<\n>
	//      |                             |<\n>
	//      +-----------------------------+<\n>
	// XO = XOffset
	// YO = YOffset
	// H  = Height
	// TW = TotalWidth
	// TH = TotalHeight

	// <Struct>
	//      ZA_FONT_CHAR_MATRIX
	//
	// <Description>
	//      This stores info about a character.
	//
	// <Members>
	//      XOffset::
	//          The horizontal offset from the origin.;;
	//      YOffset::
	//          The vertical offset from the origin.;;
	//          
	//      TotalWidth::
	//          The total width of the char. This includes 
	//          the padding and the offset.;;
	//          
	struct ZAAP_API ZA_FONT_CHAR_MATRIX
	{
		float XOffset;
		float YOffset;

		float Width;
		float Height;

		float TotalWidth;
		float TotalHeight;
	};

	ZAAP_API inline ZA_FONT_CHAR_MATRIX Multiply(const ZA_FONT_CHAR_MATRIX& a, const float& b);
	ZAAP_API inline ZA_FONT_CHAR_MATRIX Divide(const ZA_FONT_CHAR_MATRIX& a, const float& b);

}}

namespace zaap { namespace graphics {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_FONT_CHAR_INFO //
	/* //////////////////////////////////////////////////////////////////////////////// */
	struct ZAAP_API ZA_FONT_CHAR_INFO
	{
		char Character;
		
		Vec2 TexMinCoords;
		Vec2 TexMaxCoords;
		
		ZA_FONT_CHAR_MATRIX CharMatrix;
	};

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Font class //
	/* //////////////////////////////////////////////////////////////////////////////// */
	class ZAAP_API Font
	{
		//static methods
	public:

		//This methods loads a FTT file and creates a Font object from it
		static void LoadFTTFile(String file, Font* font);

		//Members
	private:

		String m_Chars;
		std::vector<ZA_FONT_CHAR_INFO> m_CharInfo;
		API::Texture2D* m_CharSheet;
		static uint const ZAAP_FONT_DEFAULT_BITMAP_SIZE = 1024;

		//Methods
	public:
		Font();
		Font(String chars);

		//render
		API::VertexBuffer* getVertexBuffer(String string);

		//util
		uint getCharIndex(char c) const;
		uint getCharCount() const;
	};
		
}}
