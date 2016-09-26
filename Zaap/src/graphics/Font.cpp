#include "Font.h"
#include <util/Console.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include "API/Texture.h"


//ZA_CharacterInfo
namespace zaap { namespace graphics {

	ZA_CharacterInfo::ZA_CharacterInfo()
		: Character(0)
	{
	}
	
	ZA_CharacterInfo::ZA_CharacterInfo(char c)
		: Character(c)
	{
	}
}}

namespace zaap { namespace graphics {
	
	//
	// Static values
	//
	FT_Library Font::s_FTLib;
	bool Font::s_IsFTLibInitialized = false;

	//Static Methods
	void Font::Init()
	{
		if (s_IsFTLibInitialized) return;

		FT_Error error = FT_Init_FreeType(&s_FTLib);
		if (error)
		{
			//TODO deal with the Error
			s_IsFTLibInitialized = false;
			return;
		}
		s_IsFTLibInitialized = true;
	}

	void Font::Cleanup()
	{
		if (!s_IsFTLibInitialized) return;

		FT_Done_FreeType(s_FTLib);
	}

	FT_Vector GetFTVector(const math::Vec2& vec)
	{
		FT_Vector ftVec;
		
		ftVec.x = FT_Pos(vec.X);
		ftVec.y = FT_Pos(vec.Y);
		
		return ftVec;
	}

	void Font::copyToBitmap(const uint &x, const uint &y, const FT_Bitmap &bitmap)
	{
		uint xx, yy, xa, ya;
		int color;
		for (yy = 0; yy < bitmap.rows; yy++)
		{
			ya = y + yy;
			for (xx = 0; xx < bitmap.width; xx++)
			{
				xa = x + xx;
				color = bitmap.buffer[xx + yy * bitmap.width];
				m_Bitmap.setColor(xa, ya, Color(color, color, color));
			}
		}
	}

	//
	// Class Members
	//
	Font::Font(String file, FONT_FORMAT format)
		: m_Format(format),
		m_Bitmap(ZAAP_FONT_DEFAULT_BITMAP_SIZE, ZAAP_FONT_DEFAULT_BITMAP_SIZE, 32)
	{
		
		loadFTTFile(file);
	}

	void Font::loadFTTFile(String file)
	{
		clock_t timer = clock();
		if (!s_IsFTLibInitialized) Init();

		FT_Face face = nullptr;
		FT_Error error = FT_New_Face(s_FTLib, file.c_str(), 0, &face);
		
		//Error handling
		if (error != FT_Err_Ok){
			//TODO add error message
			if (error == FT_Err_Unknown_File_Format)
			{

			} else
			{
				//Another error code means that the font file could not
				//be opened or read or that it is broken.
			}
			
			return;
		}
		
		//Bitmap values
		uint charCount;
		uint charSize;
		switch (m_Format)
		{
		case ZAAP_FONT_128_CHARACTERS:
			charCount = 128;
			charSize = 50;
			break;
		default:
			ZAAP_ERROR("Font: unhandeled Error");
			return;
		}

		//setting size
		FT_Set_Char_Size(face, charSize * 64, 0, 100, 0);
		FT_Set_Transform(face, 0, 0);
		FT_GlyphSlot charFTInfo = face->glyph;
		FT_Glyph_Metrics ftCharMatrix;
		ZA_CharMarix charMatirx;
		FT_Bitmap bitmap;
		ZA_CharacterInfo charInfo;
		uint bitMapX = 0;
		uint bitmapY = 0;

		for (uint i = 0; i < charCount; i++)
		{
			FT_Load_Char(face, i, FT_LOAD_RENDER);
			bitmap = charFTInfo->bitmap;

			//setting charInfo
			{
				ftCharMatrix = charFTInfo->metrics;
				charInfo = ZA_CharacterInfo(char(i));
				
				charMatirx.Width			= float(ftCharMatrix.width / 64.0f);
				charMatirx.Height			= float(ftCharMatrix.height / 64.0f);
				charMatirx.OrigenYOffset	= float(ftCharMatrix.horiBearingY / 64.0f);
				charMatirx.OrigenXOffset	= float(ftCharMatrix.horiBearingX / 64.0f);
				charMatirx.TotalWidth		= float(ftCharMatrix.horiAdvance / 64.0f);

				charInfo.CharMatirx = charMatirx;
			}

			//test bitmapX and bitmapY
			{
				
				if (bitMapX + charMatirx.Width >= m_Bitmap.getWidth())
				{
					bitMapX = 0;
					bitmapY += charSize;
					if (bitmapY + charSize >= m_Bitmap.getHeight())
					{
						bitmapY = 0;
						ZAAP_ERROR("Font: the given bitmap is to small for the selected char set");
					}
				}
			}

			//filling charInfo
			{
				charInfo.TexMinCoords = getPixelCoord(bitMapX, bitmapY);
				charInfo.TexMaxCoords = getPixelCoord(bitMapX + charMatirx.Width, bitmapY + charMatirx.Height);
			}

			copyToBitmap(bitMapX, bitmapY, bitmap);

			//adding the char
			m_CharInfo[charInfo.Character] = charInfo;

			bitMapX += charMatirx.Width;
		}

		API::Texture::CreateTexture2D("font", m_Bitmap);

		long time = clock() - timer;
		ZAAP_INFO("Font: loaded" + file + " in " + std::to_string(time) + "ms");

		FT_Done_Face(face);
	}

	math::Vec2 Font::getPixelCoord(uint x, uint y) const
	{
		return math::Vec2(float(x / m_Bitmap.getWidth()), float(y / m_Bitmap.getHeight()));
	}
}}
