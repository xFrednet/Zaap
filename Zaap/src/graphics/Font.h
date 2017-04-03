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
	// // Font //
	/* //////////////////////////////////////////////////////////////////////////////// */

	class FontCore;

	typedef za_ptr<FontCore> Font;

	/* ********************************************************* */
	// * FontCore *
	/* ********************************************************* */
	class ZAAP_API FontCore
	{
	public:
		static uint const ZAAP_FONT_DEFAULT_BITMAP_SIZE = 1024;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Loaders //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:

		// <Method>
		//      LoadFont
		//
		// <Description>
		//      This loads a font from the source file.
		//
		// <Input>
		//      srcFile::
		//          The source file where the @FontCore should be loaded from.;;
		//      font::
		//           The resulting object.;;
		//
		// <Return>
		//      This returns a @ZA_RESULT that indicated if the loading was successful.
		//
		static ZA_RESULT LoadFont(const String& srcFile, Font* font);

		// <Method>
		//      LoadFontCore
		//
		// <Description>
		//      This loads a @FontCore from the source file.
		//
		// <Input>
		//      srcFile::
		//          The source file where the @FontCore should be loaded from.;;
		//      font::
		//           The resulting object.;;
		//
		// <Return>
		//      This returns a @ZA_RESULT that indicated if the loading was successful.
		//
		static ZA_RESULT LoadFontCore(const String& srcFile, FontCore** fontCore);

		//This methods loads a FTT file and creates a Font object from it
		static ZA_RESULT LoadFTTFile(const String& srcFile, FontCore** fontCore);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Class //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:

		String m_Chars;
		std::vector<ZA_FONT_CHAR_INFO> m_CharInfo;
		API::Texture2D* m_CharSheet;

		FontCore();
	public:
		~FontCore();

		/* ********************************************************* */
		// * Util *
		/* ********************************************************* */

		/* ##################################### */
		// # Chars #
		/* ##################################### */
		uint getCharIndex(const char& c) const;
		uint getCharCount() const;

		bool isCharValid(const char& c) const;

		/* ##################################### */
		// # String #
		/* ##################################### */


		/* ##################################### */
		// # CharSheet Util #
		/* ##################################### */
		void bindCharShreet(const uint& index) const;
		void unbindCharShreet(const uint& index) const;

		void setCharSheet(API::Texture2D* charSheet);
		API::Texture2D* getCharSheet() const;
	};
		
}}
