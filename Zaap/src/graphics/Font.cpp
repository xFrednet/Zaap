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
	// // FTT loader // 
	/* //////////////////////////////////////////////////////////////////////////////// */
	void copyToBitmap(const uint &x, const uint &y, const FT_Bitmap &source, Bitmap &target)
	{
		uint xx, yy, xa, ya;
		int color;
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
	
	void Font::LoadFTTFile(String file, Font* font)
	{
		clock_t timer = clock();

		char chars[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		uint charCount = strlen(chars);
		uint bitmapSize = ZAAP_FONT_DEFAULT_BITMAP_SIZE;
		float fontSize;
		Bitmap charSheet(bitmapSize, bitmapSize, ZA_FORMAT_A8_UINT);

		FT_Library FTLib;
		FT_Face face;
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Init //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			uint charsPerLine = (uint)sqrtf(charCount) + 1; //+1 because 1.999 will be a 1 uint
			fontSize = (bitmapSize / charsPerLine) - ((bitmapSize / charsPerLine) % 64);
			font->m_CharInfo.resize(charCount);

			/* ********************************************************* */
			// * Init FreeType *
			/* ********************************************************* */
			FT_Error error = FT_Init_FreeType(&FTLib);
			if (error)
			{
				ZA_SUBMIT_ERROR(ZA_ERROR_FONT_FREETYPE_INIT_ERROR);
				return;
			}

			/* ********************************************************* */
			// * Init face *
			/* ********************************************************* */
			error = FT_New_Face(FTLib, file.c_str(), 0, &face);
			if (error != FT_Err_Ok){
				if (error == FT_Err_Unknown_File_Format)
					ZA_SUBMIT_ERROR(ZA_ERROR_FONT_UNSUPPROTED_FORMAT);
				else
					ZA_SUBMIT_ERROR(ZA_ERROR_FONT_ERROR);
			
				return;
			}

			FT_Set_Char_Size(face, uint(fontSize) * 64, 0, 100, 0);
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

					if (bitmapY + fontSize * 1.5f < charSheet.getHeight())
						bitmapY += fontSize * 1.5f;
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
			*charMatrix = Divide(*charMatrix, fontSize);
		}

		font->m_CharSheet = API::Texture::CreateTexture2D("charSheet", charSheet, false);

		FT_Done_Face(face);
		FT_Done_FreeType(FTLib);

		timer -= clock();
		ZA_INFO("I loaded ", file, " in ", timer, "ms");
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Font class //
	/* //////////////////////////////////////////////////////////////////////////////// */

}}
