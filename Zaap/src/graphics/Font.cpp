#include "Font.h"
#include <util/Log.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include "API/Texture.h"
#include <util/StringUtil.h>

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_FONT_CHAR_MATRIX //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {

	ZA_FONT_CHAR_MATRIX Multiply(const ZA_FONT_CHAR_MATRIX& a, const float& b)
	{
		ZA_FONT_CHAR_MATRIX charMarix;
		memcpy(&charMarix, &a, sizeof(ZA_FONT_CHAR_MATRIX));

		charMarix.XOffset *= b;
		charMarix.YOffset *= b;
		charMarix.Width *= b;
		charMarix.Height *= b;
		charMarix.TotalWidth *= b;
		charMarix.TotalHeight *= b;

		return charMarix;
	}
	
	ZA_FONT_CHAR_MATRIX Divide(const ZA_FONT_CHAR_MATRIX& a, const float& b)
	{
		if (!b)
			return Multiply(a, 1.0f / b);
		
		ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
		return a;
	}

}}

namespace zaap { namespace graphics {

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Loaders //
	/* //////////////////////////////////////////////////////////////////////////////// */

	ZA_RESULT FontCore::LoadFont(const String& srcFile, Font* font)
	{
		FontCore* fontCore;
		ZA_RESULT result = LoadFontCore(srcFile, &fontCore);
		*font = Font(fontCore);
		return result;
	}

	ZA_RESULT FontCore::LoadFontCore(const String& srcFile, FontCore** fontCore)
	{
		if (StringUtil::EndsWith(srcFile, ".ftt"))
			return LoadFTTFile(srcFile, fontCore);

		return ZA_ERROR_FONT_UNSUPPROTED_FORMAT;
	}

	/* ********************************************************* */
	// * FTT file *
	/* ********************************************************* */
	void copyToBitmap(const uint &x, const uint &y, const FT_Bitmap &source, Bitmap &target)
	{
		uint xx, yy, xa, ya;
		int color;
		//TODO add memcpy
		for (yy = 0; yy < source.rows; yy++)
		{
			ya = y + yy;
			for (xx = 0; xx < source.width; xx++)
			{
				xa = x + xx;
				color = source.buffer[xx + yy * source.width];
				
				if (target.getFormat() == ZA_FORMAT_R8G8B8A8_UINT) //RGBA
					target.setColor(xa, ya, Color(color, color, color));
				else 
					target.setA(xa, ya, color);
			}
		}
	}
	
	ZA_RESULT FontCore::LoadFTTFile(const String& srcFile, FontCore** fontCore)
	{
		ZA_ASSERT(fontCore, "The pointer is null.");
		ZA_ASSERT(!*fontCore, "The font core points to a FontCore");

		clock_t timer = clock();
		FontCore* font = new FontCore();

		char* chars = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		uint charCount = strlen(chars);
		uint bitmapSize = ZAAP_FONT_DEFAULT_BITMAP_SIZE;
		uint fontSize;
		Bitmap charSheet(bitmapSize, bitmapSize, ZA_FORMAT_A8_UINT);

		FT_Library FTLib;
		FT_Face face;
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Init //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			uint charsPerLine = (uint)sqrtf((float)charCount) + 1; //+1 because 1.999 will be a 1 uint
			fontSize = (bitmapSize / charsPerLine) - ((bitmapSize / charsPerLine) % 64);
			font->m_CharInfo.resize(charCount);
			
			/* ********************************************************* */
			// * Init FreeType *
			/* ********************************************************* */
			FT_Error error = FT_Init_FreeType(&FTLib);
			if (error)
				return ZA_ERROR_FONT_FREETYPE_INIT_ERROR;

			/* ********************************************************* */
			// * Init face *
			/* ********************************************************* */
			error = FT_New_Face(FTLib, srcFile.c_str(), 0, &face);
			if (error != FT_Err_Ok){
				if (error == FT_Err_Unknown_File_Format)
					return ZA_ERROR_FONT_UNSUPPROTED_FORMAT;

				return ZA_ERROR_FONT_ERROR;
			}

			FT_Set_Char_Size(face, fontSize * 64, 0, 100, 0);
			FT_Set_Transform(face, nullptr, nullptr);
		}

		FT_GlyphSlot ftCharInfo = face->glyph;
		ZA_FONT_CHAR_INFO* charInfo;

		FT_Glyph_Metrics ftCharMatrix;
		ZA_FONT_CHAR_MATRIX* charMatrix;
		
		FT_Bitmap ftBitmap;
		uint bitmapX = 0;
		uint bitmapY = 0;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Finally the loading part //
		/* //////////////////////////////////////////////////////////////////////////////// */
		for (uint i = 0; i < charCount; i++)
		{
			FT_Load_Char(face, chars[i], FT_LOAD_RENDER);
			ftBitmap = ftCharInfo->bitmap;
			ftCharMatrix = ftCharInfo->metrics;

			/* ********************************************************* */
			// * ZA_FONT_CHAR_MATRIX *
			/* ********************************************************* */
			{
				charInfo = &(font->m_CharInfo[i]);
				charMatrix = &charInfo->CharMatrix;

				charInfo->Character = chars[i];

				charMatrix->XOffset		= (float(ftCharMatrix.horiBearingX) / 64.0f);
				charMatrix->YOffset		= (float(ftCharMatrix.horiBearingY) / 64.0f); // charSize - ftCharMatrix.horiBearingY / 64.0f
				charMatrix->Width		= (float(ftCharMatrix.width) / 64.0f);
				charMatrix->Height		= (float(ftCharMatrix.height) / 64.0f);
				charMatrix->TotalWidth	= (float(ftCharMatrix.horiAdvance) / 64.0f);
				charMatrix->TotalHeight = (float(ftCharMatrix.vertAdvance) / 64.0f);
			}

			/* ********************************************************* */
			// * copy charSheet *
			/* ********************************************************* */
			{
				if ((bitmapX + ftBitmap.width + 1) >= charSheet.getWidth())
				{
					bitmapX = 0;

					if (bitmapY + fontSize < charSheet.getHeight())
						bitmapY += fontSize;
					else
						bitmapY = 0;
				}

				copyToBitmap(bitmapX, bitmapY, ftBitmap, charSheet);

				bitmapX += ftBitmap.width + 1;

				charInfo->TexMinCoords = charSheet.getPixelCoord(bitmapX, bitmapY);
				charInfo->TexMaxCoords = charSheet.getPixelCoord(bitmapX + uint(charMatrix->Width), bitmapY + uint(charMatrix->Height));
			}

			/* ********************************************************* */
			// * Loop end *
			/* ********************************************************* */
			*charMatrix = Divide(*charMatrix, (float)fontSize);
		}

		/* ********************************************************* */
		// * Finishing *
		/* ********************************************************* */
		font->m_CharSheet = API::Texture::CreateTexture2D("charSheet", charSheet, false);
		*fontCore = font;

		FT_Done_Face(face);
		FT_Done_FreeType(FTLib);

		timer -= clock();
		ZA_INFO("I loaded ", srcFile, " in ", timer, "ms");

		return ZA_OK;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Class //
	/* //////////////////////////////////////////////////////////////////////////////// */

	FontCore::FontCore()
		: m_Chars(),
		m_CharInfo(0),
		m_CharSheet(nullptr)
	{
	}

	FontCore::~FontCore()
	{
		m_CharInfo.clear();
		//TODO Delete m_CharInfo;
	}

	/* ********************************************************* */
	// * Util *
	/* ********************************************************* */

	/* ##################################### */
	// # Chars #
	/* ##################################### */
	uint FontCore::getCharIndex(const char& c) const
	{
		String::size_type n = m_Chars.find(c);
		if (n != m_Chars.npos)
			return (uint)n;

		return 0;
	}
	uint FontCore::getCharCount() const
	{
		return m_Chars.length();
	}
	bool FontCore::isCharValid(const char& c) const
	{
		return m_Chars.find(c) != m_Chars.npos;
	}

	/* ##################################### */
	// # String #
	/* ##################################### */


	/* ##################################### */
	// # CharSheet Util #
	/* ##################################### */
	void FontCore::bindCharShreet(const uint& index) const
	{
		m_CharSheet->bind(0);
	}
	void FontCore::unbindCharShreet(const uint& index) const
	{
		m_CharSheet->unbind(0);
	}

	void FontCore::setCharSheet(API::Texture2D* charSheet)
	{
		m_CharSheet = charSheet;
	}
	API::Texture2D* FontCore::getCharSheet() const
	{
		return m_CharSheet;
	}

}}
