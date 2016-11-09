#include "Font.h"
#include <util/Console.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include "API/Texture.h"
#include "Renderer.h"

//
// ZA_CharMatrix
//
namespace zaap { namespace graphics {
	ZA_CharMarix::ZA_CharMarix()
		: OrigenXOffset(0),
		OrigenYOffset(0),
		Width(0),
		Height(0)
	{
	}

	ZA_CharMarix::ZA_CharMarix(const ZA_CharMarix& charMarix)
	{
		memcpy(this, &charMarix, sizeof(ZA_CharMarix));
	}

	ZA_CharMarix ZA_CharMarix::operator/(float a) const
	{
		return *this * (1.0f / a);
	}

	ZA_CharMarix ZA_CharMarix::operator*(float a) const
	{
		ZA_CharMarix charMatrix(*this);

		charMatrix.OrigenXOffset *= a;
		charMatrix.OrigenYOffset *= a;
		charMatrix.Width *= a;
		charMatrix.Height *= a;

		return charMatrix;
	}
}}

//
// ZA_CharacterInfo
//
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
	//Static Methods
	//
	Mat4 Font::CreateFontTransformationMatrix(const Vec3& position, const float& fontSize)
	{
		Mat4 mat(fontSize);
		
		mat.m41 = position.X;
		mat.m42 = position.Y;
		mat.m43 = position.Z;

		return mat;
	}

	String Font::GetFormatCharacters(FONT_FORMAT format)
	{
		switch (format)
		{
		case ZAAP_FONT_128_CHARACTERS:
			return " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		default:
			return String();
		}
	}

	//
	// FTT loader
	//
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
	Font Font::LoadFTTFile(String file, FONT_FORMAT format)
	{
		return LoadFTTFile(file, GetFormatCharacters(format));
	}
	Font Font::LoadFTTFile(String file, String chars)
	{
		clock_t timer = clock();
		FT_Error error;
		
		Font font(chars);
		FT_Library FTLib;
		FT_Face face;
		
		//Init
		{
			//
			// Init FreeType
			//
			error = FT_Init_FreeType(&FTLib);
			if (error)
			{
				//TODO deal with the Error
				return Font();
			}

			//
			// Init face
			//
			error = FT_New_Face(FTLib, file.c_str(), 0, &face);
			if (error != FT_Err_Ok){
				//TODO add error message
				if (error == FT_Err_Unknown_File_Format)
				{

				} else
				{
					//Another error code means that the font file could not
					//be opened or read or that it is broken.
				}
			
				return Font();
			}
			
		}
		
		//Bitmap values
		uint charSize;
		if (chars.size() < 200)
			charSize = 50;
		else
			charSize = 10;
		

		//Setting size
		FT_Set_Char_Size(face, charSize * 64, 0, 100, 0);
		FT_Set_Transform(face, 0, 0);

		//getting the current char information
		FT_GlyphSlot charFTInfo = face->glyph;

		//creating objects for the loop
		FT_Glyph_Metrics ftCharMatrix;
		ZA_CharMarix charMatirx;
		FT_Bitmap bitmap;
		ZA_CharacterInfo charInfo;
		uint bitMapX = 0;
		uint bitmapY = 0;

		//
		// init charSheet
		//
		Bitmap charSheet;
		{
			for (uint i = 0; i < chars.size(); i++)
			{
				if (chars.at(i) != ' ')
				{
					FT_Load_Char(face, chars.at(i), FT_LOAD_RENDER);
					break;
				}
				
			}
			
			bitmap = charFTInfo->bitmap;
			uint width = ZAAP_FONT_DEFAULT_BITMAP_SIZE;
			uint height = ZAAP_FONT_DEFAULT_BITMAP_SIZE;
			//creating the charSheet
			if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
				charSheet = Bitmap(width, height, ZA_FORMAT_A8_UINT);
			else if (bitmap.pixel_mode == FT_PIXEL_MODE_LCD)
				charSheet = Bitmap(width, height, ZA_FORMAT_R8G8B8A8_UINT);
			else
			{
				charSheet = Bitmap(width, height, ZA_FORMAT_R8G8B8A8_UINT);
				ZAAP_ERROR("Font: FreeType loaded the font with a unknown bitmap format");
			}
			
		}

		//
		// Loading the chars
		//
		for (uint i = 0; i < chars.size(); i++)
		{
			FT_Load_Char(face, chars.at(i), FT_LOAD_RENDER);
			bitmap = charFTInfo->bitmap;

			//setting charInfo
			{
				ftCharMatrix = charFTInfo->metrics;
				charInfo = ZA_CharacterInfo(chars.at(i));
				
				charMatirx.Width			= float(ftCharMatrix.horiAdvance / 64.0f);
				charMatirx.Height			= float(ftCharMatrix.vertAdvance / 64.0f);
				charMatirx.OrigenYOffset	= float(ftCharMatrix.horiBearingY / 64.0f);
				charMatirx.OrigenXOffset	= float(ftCharMatrix.horiBearingX / 64.0f);

				charInfo.CharMatirx = charMatirx;

				if (charMatirx.Width > font.m_MaxCharSize.Width)
					font.m_MaxCharSize.Width = charMatirx.Width;

				if (charMatirx.Height > font.m_MaxCharSize.Height)
					font.m_MaxCharSize.Height = charMatirx.Height;

				if (charMatirx.OrigenYOffset > font.m_MaxCharSize.OrigenYOffset)
					font.m_MaxCharSize.OrigenYOffset = charMatirx.OrigenYOffset;
			}

			//test bitmapX and bitmapY
			{
				if (bitMapX + charMatirx.Width * 1.5f >= charSheet.getWidth())
				{
					bitMapX = 0;
					bitmapY += charSize * 2;
					if (bitmapY + charSize >= charSheet.getHeight())
					{
						bitmapY = 0;
						ZAAP_ERROR("Font: the given bitmap is to small for the selected char set");
					}
				}
			}

			//filling charInfo
			{
				charInfo.TexMinCoords = charSheet.getPixelCoord(bitMapX, bitmapY);
				charInfo.TexMaxCoords = charSheet.getPixelCoord(bitMapX + uint(charMatirx.Width), bitmapY + uint(charMatirx.Height));
			}

			copyToBitmap(bitMapX, bitmapY, bitmap, charSheet);

			//resizing the charMatrix to a fontSize of 1
			charInfo.CharMatirx = charInfo.CharMatirx / float(charSize); 
			//adding the char
			font.m_CharInfo[i] = charInfo;

			bitMapX += uint(charMatirx.Width  * 1.5f);
		}

		//resize the MaxCharSize
		font.m_MaxCharSize = font.m_MaxCharSize / float(charSize);

		// generate the texture
		font.m_CharSheet = API::Texture::CreateTexture2D("font", charSheet);

		//cleaning up the FreeType library
		FT_Done_Face(face);
		FT_Done_FreeType(FTLib);

		long time = clock() - timer;
		ZAAP_INFO("Font: loaded" + file + " in " + std::to_string(time) + "ms");

		return font;
	}

	//
	// Class Members
	//
	Font::Font()
		: m_Size(11),
		m_Chars(),
		m_CharInfo(0)
	{
	}
	Font::Font(String chars)
		: m_Size(11),
		m_Chars(chars),
		m_CharSheet(nullptr),
		m_CharInfo(chars.size())
	{
	}

	API::VertexBuffer* Font::getVertexBuffer(String string)
	{
		using namespace std;

		vector<ZA_CharVertex> vertices(string.size() * 4);
		vector<uint> indices(string.size() * 6);

		float zValue = 0.0f;

		//the x value of the character
		float drawX = 0.0f;
		// v0  v3
		// v1  v2
		uint v0, v1, v2, v3;
		//Index of the indices
		uint iIndex = 0;
		//the current character
		char c;
		ZA_CharacterInfo cInfo;
		ZA_CharMarix cMatrix;
		for (uint i = 0; i < string.size(); i++)
		{
			c = string.at(i);
			cInfo = m_CharInfo[getCharIndex(c)];
			cMatrix = cInfo.CharMatirx;
			v0 = i * 4;
			v1 = i * 4 + 1;
			v2 = i * 4 + 2;
			v3 = i * 4 + 3;
			
			//setting indices
			{
				// v0, v2, v1
				indices[iIndex++] = v0;
				indices[iIndex++] = v2;
				indices[iIndex++] = v1;

				// v0, v3, v2
				indices[iIndex++] = v0;
				indices[iIndex++] = v3;
				indices[iIndex++] = v2;
			}
			// 0 3
			// 1 2 
			//v0
			vertices[v0].Position = Vec3(cMatrix.OrigenXOffset + drawX, cMatrix.OrigenYOffset, zValue);
			vertices[v0].TexCoord = Vec2(cInfo.TexMinCoords.X, cInfo.TexMaxCoords.Y);

			//v1
			vertices[v1].Position = Vec3(cMatrix.OrigenXOffset + drawX, cMatrix.OrigenYOffset + cMatrix.Height, zValue);
			vertices[v1].TexCoord = cInfo.TexMinCoords;

			//v2
			vertices[v2].Position = Vec3(cMatrix.OrigenXOffset + cMatrix.Width + drawX, cMatrix.OrigenYOffset + cMatrix.Height, zValue);
			vertices[v2].TexCoord = Vec2(cInfo.TexMaxCoords.X, cInfo.TexMinCoords.Y);

			//v3
			vertices[v3].Position = Vec3(cMatrix.OrigenXOffset + cMatrix.Width + drawX, cMatrix.OrigenYOffset, zValue);
			vertices[v3].TexCoord = cInfo.TexMaxCoords;

			drawX += cMatrix.Width;
		}

		return API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(ZA_CharVertex), vertices.size(), &indices[0], indices.size(), ZA_SHADER_FONT_SHADER_2D);
	}

	uint temp = 0;
	bool up = true;
	Color color(1.0f, 1.0f, 1.0f, 1.0f);
	void Font::render(API::VertexBuffer *vb)
	{
		
		/*if (up)
		{
			temp += 1;
			if (temp >= 255)
			{
				up = false;
				color = Color(rand() % 255, rand() % 255, rand() % 255);
			}
		} else
		{
			temp -= 1;
			if (temp <= 125)
			{
				up = true;
				color = Color(rand() % 255, rand() % 255, rand() % 255);
			}
		}*/

		
		Renderer::StartShader(ZA_SHADER_FONT_SHADER_2D);
		((FontShader2D*)Renderer::GetShader(ZA_SHADER_FONT_SHADER_2D))->setSize(26.0f);
		((FontShader2D*)Renderer::GetShader(ZA_SHADER_FONT_SHADER_2D))->setPixelCoords(10, 100);
		((FontShader2D*)Renderer::GetShader(ZA_SHADER_FONT_SHADER_2D))->setColor(color);
		m_CharSheet->bind(0);
		vb->draw();

	}

	//
	// Util
	//
	uint Font::getCharIndex(char c) const
	{
		return (uint)m_Chars.find(c);
	}
	uint Font::getCharCount() const
	{
		return (uint)m_Chars.size();
	}
}}
