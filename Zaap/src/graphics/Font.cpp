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
		Height(0),
		TotalWidth(0)
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
	math::Mat4 Font::CreateFontTransformationMatrix(const math::Vec3& position, const float& fontSize)
	{
		math::Mat4 mat(fontSize);
		
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
				target.setColor(xa, ya, Color(color, color, color));
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
				
				charMatirx.Width			= float(ftCharMatrix.width / 64.0f);
				charMatirx.Height			= float(ftCharMatrix.height / 64.0f);
				charMatirx.OrigenYOffset	= float(ftCharMatrix.vertBearingY / 64.0f);
				charMatirx.OrigenXOffset	= float(ftCharMatrix.horiBearingX / 64.0f);
				charMatirx.TotalWidth		= float(ftCharMatrix.horiAdvance / 64.0f);

				charInfo.CharMatirx = charMatirx;
			}

			//test bitmapX and bitmapY
			{
				
				if (bitMapX + charMatirx.Width >= font.m_Bitmap.getWidth())
				{
					bitMapX = 0;
					bitmapY += charSize * 2;
					if (bitmapY + charSize >= font.m_Bitmap.getHeight())
					{
						bitmapY = 0;
						ZAAP_ERROR("Font: the given bitmap is to small for the selected char set");
					}
				}
			}

			//filling charInfo
			{
				charInfo.TexMinCoords = font.getPixelCoord(bitMapX, bitmapY);
				charInfo.TexMaxCoords = font.getPixelCoord(bitMapX + charMatirx.Width, bitmapY + charMatirx.Height);
			}

			copyToBitmap(bitMapX, bitmapY, bitmap, font.m_Bitmap);

			//resizing the charMatrix to a fontSize of 1
			charInfo.CharMatirx = charInfo.CharMatirx / float(charSize); 
			//adding the char
			font.m_CharInfo[i] = charInfo;

			bitMapX += charMatirx.Width;
		}

		// generate the texture
		font.m_CharSheet = API::Texture::CreateTexture2D("font", font.m_Bitmap);
		font.generateVertexBuffer();

		//cleaning up the FreeType library
		FT_Done_Face(face);
		FT_Done_FreeType(FTLib);

		long time = clock() - timer;
		ZAAP_INFO("Font: loaded" + file + " in " + std::to_string(time) + "ms");

		return font;
	}

	//
	// Private util methods
	//
	void Font::generateVertexBuffer()
	{
		using namespace math;

		//every char has 4 vertices
		std::vector<ZA_CharVertex> vertices(getCharCount() * 4);
		//every char has 6 indices
		std::vector<uint> indices(getCharCount() * 6);
		float zValue = 0.0f;

		// v0   v3
		//
		// v1   v2
		uint iIndex = 0;
		uint v0, v1, v2, v3;
		ZA_CharMarix matrix;
		ZA_CharacterInfo charInfo;
		for (uint i = 0; i < getCharCount(); i++)
		{
			charInfo = m_CharInfo[i];
			matrix = charInfo.CharMatirx;
			v0 = i * 4;
			v1 = v0 + 1;
			v2 = v0 + 2;
			v3 = v0 + 3;

			// v0 v1 v2
			indices[iIndex++] = v0;
			indices[iIndex++] = v1;
			indices[iIndex++] = v2;

			// v0 v2 v3
			indices[iIndex++] = v0;
			indices[iIndex++] = v2;
			indices[iIndex++] = v3;

			// v0
			vertices[v0].Position = Vec3(matrix.OrigenXOffset, matrix.OrigenYOffset, zValue);
			vertices[v0].TexCoord = charInfo.TexMinCoords;

			// v1
			vertices[v1].Position = Vec3(matrix.OrigenXOffset, matrix.OrigenYOffset + matrix.Height, zValue);
			vertices[v1].TexCoord = Vec2(charInfo.TexMinCoords.X, charInfo.TexMaxCoords.Y);

			// v2
			vertices[v2].Position = Vec3(matrix.OrigenXOffset + matrix.Width, matrix.OrigenYOffset + matrix.Height, zValue);
			vertices[v2].TexCoord = charInfo.TexMaxCoords;

			// v3
			vertices[v3].Position = Vec3(matrix.OrigenXOffset + matrix.Width, matrix.OrigenYOffset, zValue);
			vertices[v3].TexCoord = Vec2(charInfo.TexMaxCoords.X, charInfo.TexMinCoords.Y);
		}

		m_VertexBuffer = API::VertexBuffer::CreateVertexbuffer(&vertices[0], sizeof(ZA_CharVertex), vertices.size(), &indices[0], indices.size());
	}

	//
	// Class Members
	//
	Font::Font()
		: m_Size(11),
		m_Chars(),
		m_Bitmap(ZAAP_FONT_DEFAULT_BITMAP_SIZE, ZAAP_FONT_DEFAULT_BITMAP_SIZE, 32),
		m_CharSheet(nullptr),
		m_VertexBuffer(nullptr),
		m_CharInfo(0)
	{
	}
	Font::Font(String chars)
		: m_Size(11),
		m_Chars(chars),
		m_Bitmap(ZAAP_FONT_DEFAULT_BITMAP_SIZE, ZAAP_FONT_DEFAULT_BITMAP_SIZE, 32), 
		m_CharSheet(nullptr),
		m_VertexBuffer(nullptr),
		m_CharInfo(chars.size())
	{
	}

	//
	// Render
	//
	float temp = 1.0f;
	void Font::render(String string) const
	{
		Renderer::StartFontShader2D();
		FontShader2D* shader = Renderer::GetFontShader2D();

		shader->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

		m_VertexBuffer->bind(0);
		m_CharSheet->bind(0);

		Shader::VS_MATRIX_BUFFER b;
		b.TransformationMatrix = CreateTransformationMatrix(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3(0.0f, 180, 0.0f), math::Vec3(0.1f, 0.1f, 0.1f));
		b.ProjectionMatrix = Renderer::GetProjectionMatrix();
		b.ViewMatrix = Renderer::GetCamera()->getViewMatrix();

		for (uint i = 0; i < string.size(); i++)
		{
			shader->setTransformationMatrix(b);
			
			m_VertexBuffer->draw(getCharIndex(string.at(i)) * 6, 6);
			//m_VertexBuffer->draw(0, getCharCount() * 6);
		}
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

	math::Vec2 Font::getPixelCoord(uint x, uint y) const
	{
		return math::Vec2(float(x / m_Bitmap.getWidth()), float(y / m_Bitmap.getHeight()));
	}
}}
