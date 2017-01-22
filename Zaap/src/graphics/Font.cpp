#include "Font.h"
#include <util/Console.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include "API/Texture.h"
#include "shader/types/FontShader2D.h"
#include "Renderer3D.h"

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_CharMatrix //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {
	ZA_CharMarix::ZA_CharMarix()
		: OrigenXOffset(0),
		OrigenYOffset(0),
		TotalWidth(0),
		TotalHeight(0),
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
		charMatrix.TotalWidth *= a;
		charMatrix.TotalHeight *= a;

		return charMatrix;
	}
}}

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_CharacterInfo //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {
	ZA_CharacterInfo::ZA_CharacterInfo()
		: Character('\0')
	{
	}
	
	ZA_CharacterInfo::ZA_CharacterInfo(char c)
		: Character(c)
	{
	}
}}

namespace zaap { namespace graphics {

	/* //////////////////////////////////////////////////////////////////////////////// */
	// //Static Methods //
	/* //////////////////////////////////////////////////////////////////////////////// */
	Mat4 Font::CreateFontTransformationMatrix(const Vec3& position, const float& fontSize)
	{
		Mat4 mat(fontSize);
		
		mat.m41 = position.X;
		mat.m42 = position.Y;
		mat.m43 = position.Z;

		return mat;
	}

	String Font::GetFormatCharacters(ZA_FONT_CHAR_FORMAT format)
	{
		switch (format)
		{
		case ZAAP_FONT_128_CHARACTERS:
			return " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		default:
			return String();
		}
	}

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
	Font Font::LoadFTTFile(String file, ZA_FONT_CHAR_FORMAT format)
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
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Init //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			/* ********************************************************* */
			// * Init FreeType *
			/* ********************************************************* */
			error = FT_Init_FreeType(&FTLib);
			if (error)
			{
				//TODO deal with the Error
				return Font();
			}

			/* ********************************************************* */
			// * Init face *
			/* ********************************************************* */
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
			charSize = 60;
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

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // init charSheet //
		/* //////////////////////////////////////////////////////////////////////////////// */
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
				ZAAP_ERROR("FreeType loaded the font with a unknown bitmap format");
			}
			
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Loading the chars //
		/* //////////////////////////////////////////////////////////////////////////////// */
		for (uint i = 0; i < chars.size(); i++)
		{
			FT_Load_Char(face, chars.at(i), FT_LOAD_RENDER);
			bitmap = charFTInfo->bitmap;

			/* ********************************************************* */
			// * setting charInfo *
			/* ********************************************************* */
			{
				ftCharMatrix = charFTInfo->metrics;
				charInfo = ZA_CharacterInfo(chars.at(i));
				
				charMatirx.OrigenXOffset	= float(ftCharMatrix.horiBearingX / 64.0f);
				charMatirx.OrigenYOffset	= float(charSize - ftCharMatrix.horiBearingY / 64.0f);
				charMatirx.Width			= float(ftCharMatrix.width / 64.0f);
				charMatirx.Height			= float(ftCharMatrix.height / 64.0f);
				charMatirx.TotalWidth		= float(ftCharMatrix.horiAdvance / 64.0f);
				charMatirx.TotalHeight		= float(ftCharMatrix.vertAdvance / 64.0f);

				charInfo.CharMatirx = charMatirx;

				if (charMatirx.TotalWidth > font.m_MaxCharSize.Width)
					font.m_MaxCharSize.Width = charMatirx.Width;

				if (charMatirx.TotalHeight > font.m_MaxCharSize.Height)
					font.m_MaxCharSize.Height = charMatirx.Height;

				if (charMatirx.OrigenYOffset > font.m_MaxCharSize.OrigenYOffset)
					font.m_MaxCharSize.OrigenYOffset = charMatirx.OrigenYOffset;
			}
			/* ********************************************************* */
			// * test bitmapX and bitmapY *
			/* ********************************************************* */
			{
				if (bitMapX + charMatirx.Width * 1.5f >= charSheet.getWidth())
				{
					bitMapX = 0;
					bitmapY += charSize * 2;
					if (bitmapY + charSize >= charSheet.getHeight())
					{
						bitmapY = 0;
						ZAAP_ERROR("the given bitmap is to small for the selected char set");
					}
				}
			}

			/* ********************************************************* */
			// * filling charInfo *
			/* ********************************************************* */
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
		ZAAP_INFO("loaded" + file + " in " + std::to_string(time) + "ms");

		return font;
	}

	Font Font::LoadFontFromTXT(String file, String textureFile, uint size)
	{
		using namespace std;
		
		clock_t timer = clock();

		Font font;
		font.m_Size = (float)size;
		uint width;
		uint height;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Texture / m_CharSheet loading //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{
			font.m_CharSheet = API::Texture::CreateTexture2D(textureFile, textureFile, true);
			if (!font.m_CharSheet 
				|| (width = font.m_CharSheet->getWidth()) == 0
				|| (height = font.m_CharSheet->getHeight()) == 0)
			{
				ZAAP_ERROR("The texture could not be loaded");
				return font;
			}
		}
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // file loading //
		/* //////////////////////////////////////////////////////////////////////////////// */
		{

			font.m_CharInfo = vector<ZA_CharacterInfo>(); //font sets the size to zero
			
			fstream fileStream;
			fileStream.open(file);
			if (!fileStream.is_open())
			{
				ZAAP_ERROR("The given file could not be opened. File: " + file);
				return font;
			}

			String line;
			stringstream lStream;
			ZA_CharacterInfo charInfo;
			ZA_CharMarix* charMatrix;
			uint xPixel, yPixel, widthPixel, heightPixel;
			while (!fileStream.eof())
			{
				getline(fileStream, line);
				if (StringUtil::StartsWith(line, "##") || line.length() <= 1)
					continue; // it's a command
				
				/* ##################################### */
				// # init charInfo && charMatrix #
				/* ##################################### */
				{
					font.m_Chars += line[0];
					//char info
					charInfo = ZA_CharacterInfo(line[0]);

					// charMatrix;
					charMatrix = &charInfo.CharMatirx;
				}

				/* ##################################### */
				// # line processing #
				/* ##################################### */
				{
					line[0] = ' ';
					lStream = stringstream(line);

					// char- <     Bitmap stuff      >-<               char matrix                  >
					// char-xPixel-yPixel-width-height-lineXOffset-lineYOffset-totalWidth-totalHeight
					// A    0      0      610   724    723         25          660        724
					
					//
					// Bitmap stuff;
					//
					lStream >> xPixel;
					charInfo.TexMinCoords.X = (float)xPixel / (float)width;
					lStream >> yPixel;
					charInfo.TexMinCoords.Y = (float)yPixel / (float)height;

					lStream >> widthPixel;
					charInfo.TexMaxCoords.X = (float)(xPixel + widthPixel) / (float)width;
					lStream >> heightPixel;
					charInfo.TexMaxCoords.Y = (float)(yPixel + heightPixel) / (float)height;

					//
					// char matrix
					//
					lStream >> charMatrix->OrigenXOffset;
					lStream >> charMatrix->OrigenYOffset;
					lStream >> charMatrix->TotalWidth;
					lStream >> charMatrix->TotalHeight;
					charMatrix->Width = charMatrix->TotalWidth;
					charMatrix->Height = charMatrix->TotalHeight;

					charInfo.CharMatirx = *charMatrix / (float)size;
				}

				font.m_CharInfo.push_back(charInfo);
			}
		}

		long time = clock() - timer;
		ZAAP_INFO("loaded" + file + " in " + std::to_string(time) + "ms");

		return font;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Class Members //
	/* //////////////////////////////////////////////////////////////////////////////// */
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

		if (m_CharInfo.size() == 0)
			return nullptr;

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
				// v0, v1, v2
				indices[iIndex++] = v0;
				indices[iIndex++] = v1;
				indices[iIndex++] = v2;

				// v0, v2, v3
				indices[iIndex++] = v0;
				indices[iIndex++] = v3;
				indices[iIndex++] = v2;
			}
			// 0 3
			// 1 2 
			//v0
			vertices[v0].Position = Vec3(
				cMatrix.OrigenXOffset + drawX,
				(-cMatrix.OrigenYOffset), zValue);
			vertices[v0].TexCoord = cInfo.TexMinCoords;

			//v1
			vertices[v1].Position = Vec3(
				cMatrix.OrigenXOffset + drawX, 
				(-cMatrix.OrigenYOffset - cMatrix.Height), zValue);
			vertices[v1].TexCoord = Vec2(cInfo.TexMinCoords.X, cInfo.TexMaxCoords.Y);

			//v2
			vertices[v2].Position = Vec3(
				cMatrix.OrigenXOffset + cMatrix.Width + drawX, 
				(-cMatrix.OrigenYOffset - cMatrix.Height), zValue);
			vertices[v2].TexCoord = cInfo.TexMaxCoords;

			//v3
			vertices[v3].Position = Vec3(
				cMatrix.OrigenXOffset + cMatrix.Width + drawX, 
				(-cMatrix.OrigenYOffset), zValue);
			vertices[v3].TexCoord = Vec2(cInfo.TexMaxCoords.X, cInfo.TexMinCoords.Y);

			drawX += cMatrix.TotalWidth;
		}

		return API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(ZA_CharVertex), vertices.size(), &indices[0], indices.size(), ZA_SHADER_FONT_SHADER_2D);
	}

	float temp = 0;
	Color color;
	float size = 400.0;
	void Font::render(API::VertexBuffer *vb, Renderer3D* renderer)
	{
		if (!vb) 
			return;
		
		float c = 0.5 + 0.5 * sin(temp);
		color.R = c;
		color.G = c;
		color.B = c;

		temp += 0.005f;
		size = 40 + 20 * sin(temp*0.1);
		renderer->disableDepthTesting();
		renderer->setAlphaTestingState(true);
		renderer->startShader(ZA_SHADER_FONT_SHADER_2D);
		((FontShader2D*)renderer->getShader(ZA_SHADER_FONT_SHADER_2D))->setSize(size);
		((FontShader2D*)renderer->getShader(ZA_SHADER_FONT_SHADER_2D))->setPixelCoords(0, 2);
		((FontShader2D*)renderer->getShader(ZA_SHADER_FONT_SHADER_2D))->setColor(color);
		m_CharSheet->bind(0);
		vb->draw();
		renderer->enableDepthTesting();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	uint Font::getCharIndex(char c) const
	{
		std::string::size_type n = m_Chars.find(c);
		if (n != std::string::npos)
			return (uint)n;

		return 0;
	}
	uint Font::getCharCount() const
	{
		return (uint)m_Chars.size();
	}
}}
