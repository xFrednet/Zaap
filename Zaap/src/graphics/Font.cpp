#include "Font.h"
#include <util/Log.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "Bitmap.h"
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
		if (b)
			return Multiply(a, 1.0f / b);
		
		ZA_SUBMIT_ERROR(ZA_ERROR_DIVISION_BY_ZERO);
		return a;
	}

}}

namespace zaap { namespace graphics {

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Loaders //
	/* //////////////////////////////////////////////////////////////////////////////// */

	Font FontCore::LoadFont(const String& srcFile, ZA_RESULT* result)
	{
		return Font(LoadFontCore(srcFile, result));
	}

	FontCore* FontCore::LoadFontCore(const String& srcFile, ZA_RESULT* result)
	{
		if (StringUtil::EndsWith(srcFile, ".ttf"))
			return LoadTTFFile(srcFile, result);

		*result = ZA_ERROR_FONT_UNSUPPROTED_FORMAT;
		return nullptr;
	}

	/* ********************************************************* */
	// * FTT file *
	/* ********************************************************* */
	inline void copyToBitmap(const uint &x, const uint &y, const FT_Bitmap &source, Bitmap &target)
	{
		uint stride = source.width;
		byte* bytes = target.getPixelArray();

		if (target.getFormat() == ZA_FORMAT_R8G8B8A8_UINT) //RGBA
			stride *= 4;

		for (uint yy = 0; yy < source.rows; yy++)
		{
			memcpy(&bytes[x + (yy + y) * target.getWidth()], &source.buffer[yy * source.width], stride);
		}
	}
	inline int getUTF8Code(const char& c)
	{
		if (c >= ' ' && c <= '~')
			return int(c);

		//¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ
		return int(0x00A1 + (c - '¡'));
	}

	FontCore* FontCore::LoadTTFFile(const String& srcFile, ZA_RESULT* result)
	{
		clock_t timer = clock();
		FontCore* font = new FontCore();

		const char* chars = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ";
		uint charCount = strlen(chars);
		uint bitmapSize = ZAAP_FONT_DEFAULT_BITMAP_SIZE;
		uint fontSize;
		float fontSizeF;
		Bitmap charSheet(bitmapSize, bitmapSize, ZA_FORMAT_A8_UINT);

		FT_Library FTLib;
		FT_Face face;
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Init //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			uint charsPerLine = (uint)sqrtf((float)charCount) + 1; //+1 because 1.999 will be a 1 uint
			fontSize = (bitmapSize / charsPerLine) - ((bitmapSize / charsPerLine) % 64);
			fontSizeF = float(fontSize);
			font->m_CharInfo.resize(charCount);
			
			/* ********************************************************* */
			// * Init FreeType *
			/* ********************************************************* */
			FT_Error error = FT_Init_FreeType(&FTLib);
			if (error)
			{
				*result = ZA_ERROR_FONT_FREETYPE_INIT_ERROR;
				return nullptr;
			}

			/* ********************************************************* */
			// * Init face *
			/* ********************************************************* */
			error = FT_New_Face(FTLib, srcFile.c_str(), 0, &face);
			if (error != FT_Err_Ok){
				if (error == FT_Err_Unknown_File_Format)
					*result = ZA_ERROR_FONT_UNSUPPROTED_FORMAT;
				else 
					*result = ZA_ERROR_FONT_ERROR;
				return nullptr;
			}

			FT_Set_Char_Size(face, fontSize * 64, 0, 100, 0);
			FT_Set_Transform(face, nullptr, nullptr);

			font->m_LineHeight = (float(face->max_advance_height + face->height) / 26.6f) / fontSizeF;
		}

		FT_GlyphSlot ftCharInfo = face->glyph;
		ZA_FONT_CHAR_INFO* charInfo;

		FT_Glyph_Metrics ftCharMatrix;
		ZA_FONT_CHAR_MATRIX* charMatrix;
		
		FT_Bitmap ftBitmap;
		uint bitmapX = 10;
		uint bitmapY = 10;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Finally the loading part //
		/* //////////////////////////////////////////////////////////////////////////////// */
		for (uint i = 0; i < charCount; i++)
		{
			FT_Load_Char(face, getUTF8Code(chars[i]), FT_LOAD_RENDER);
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
				charMatrix->YOffset		= (fontSizeF - float(ftCharMatrix.horiBearingY) / 64.0f); // charSize - ftCharMatrix.horiBearingY / 64.0f
				charMatrix->Width		= (float(ftCharMatrix.width) / 64.0f);
				charMatrix->Height		= (float(ftCharMatrix.height) / 64.0f);
				charMatrix->TotalWidth	= (float(ftCharMatrix.horiAdvance) / 64.0f);
				charMatrix->TotalHeight = (float(ftCharMatrix.vertAdvance) / 64.0f);
			}

			/* ********************************************************* */
			// * copy charSheet *
			/* ********************************************************* */
			{
				if ((bitmapX + ftBitmap.width + 10) >= charSheet.getWidth())
				{
					bitmapX = 10;

					if (bitmapY + fontSize * 1.5f < charSheet.getHeight())
						bitmapY += (uint)(fontSizeF * 1.5f);
					else
						bitmapY = 10;
				}

				copyToBitmap(bitmapX, bitmapY, ftBitmap, charSheet);

				charInfo->TexMinCoords = charSheet.getPixelCoord(bitmapX - 1, bitmapY - 1);
				charInfo->TexMaxCoords = charSheet.getPixelCoord(bitmapX + ftBitmap.width + 1, bitmapY + ftBitmap.rows + 1);
				
				bitmapX += ftBitmap.width + 10;
			}

			/* ********************************************************* */
			// * Loop end *
			/* ********************************************************* */
			*charMatrix = Divide(*charMatrix, fontSizeF);
		}

		/* ********************************************************* */
		// * Finishing *
		/* ********************************************************* */
		ZA_TEX2D_DESC desc(charSheet.getFormat(), ZA_TEXTURE_FILTER_POINT, false, 1);
		font->m_CharSheet = API::TextureCore::CreateTexture2D(charSheet, "charSheet", desc, false);
		font->m_Chars = String(chars);

		FT_Done_Face(face);
		FT_Done_FreeType(FTLib);

		timer = clock() - timer;
		ZA_INFO("I loaded ", srcFile, " in ", timer, "ms");

		*result = ZA_OK;
		return font;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Class //
	/* //////////////////////////////////////////////////////////////////////////////// */

	FontCore::FontCore()
		: m_Chars(),
		m_CharInfo(0),
		m_CharSheet(nullptr),
		m_LineHeight(0)
	{
	}

	FontCore::~FontCore()
	{
		m_CharInfo.clear();
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
	uint FontCore::getStringWidth(const String& string, const float& fontSize) const
	{
		return getStringSize(string, fontSize).Width;
	}
	uint FontCore::getStringHeight(const String& string, const float& fontSize) const
	{
		return getStringSize(string, fontSize).Height;
	}

	Dimensions FontCore::getStringSize(const String& string, const float& fontSize) const
	{
		uint strSize = string.length();
		if (strSize == 0)
			return Dimensions();

		ZA_FONT_CHAR_MATRIX const* matrix = &m_CharInfo[getCharIndex(string.at(0))].CharMatrix;
		float width = -(matrix->TotalWidth - (matrix->XOffset + matrix->Width));
		float maxWidth = 0;
		float maxHeight = 0;
		uint line = 0;
		char c;

		for (uint i = 0; i < strSize; i++)
		{
			c = string.at(i);
			matrix = &m_CharInfo[getCharIndex(c)].CharMatrix;

			/* ##################################### */
			// # new line #
			/* ##################################### */
			if (c == '\n')
			{
				line++;
				
				if (i > 0)
				{
					matrix = &m_CharInfo[getCharIndex(string.at(i - 1))].CharMatrix;
					width -= matrix->TotalWidth - (matrix->XOffset + matrix->Width);
				}
				if (width > maxWidth)
					maxWidth = width;

				if (i + 1 < strSize)
					width = -m_CharInfo[getCharIndex(string.at(i + 1))].CharMatrix.XOffset;
				maxHeight = 0;

				continue;
			}

			/* //////////////////////////////////////////////////////////////////////////////// */
			// // current line //
			/* //////////////////////////////////////////////////////////////////////////////// */
			//width
			width += matrix->TotalWidth;
			//height
			if (matrix->Height + matrix->YOffset > maxHeight)
				maxHeight = matrix->Height + matrix->YOffset;
		}

		width -= matrix->TotalWidth - (matrix->XOffset + matrix->Width);
		if (width > maxWidth)
			maxWidth = width;

		return Dimensions((uint)(maxWidth * fontSize), (uint)((maxHeight + line * m_LineHeight) * fontSize));
	}

	/* ##################################### */
	// # CharSheet Util #
	/* ##################################### */
	void FontCore::bindCharShreet(const uint& index) const
	{
		m_CharSheet->bind(index);
	}
	void FontCore::unbindCharShreet(const uint& index) const
	{
		m_CharSheet->unbind(index);
	}

	void FontCore::setCharSheet(API::Texture2D charSheet)
	{
		m_CharSheet = charSheet;
	}
	API::Texture2D FontCore::getCharSheet() const
	{
		return m_CharSheet;
	}

}}
