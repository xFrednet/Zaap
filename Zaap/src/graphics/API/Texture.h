#pragma once

#include <Common.h>

#include <graphics/Format.h>

#include <util/UUID.h>

#pragma warning( disable : 4251)

/* //////////////////////////////////////////////////////////////////////////////// */
// // Texture options //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {
	/* ********************************************************* */
	// * ZA_TEXTURE_TYPE *
	/* ********************************************************* */
	typedef enum ZAAP_API ZA_TEXTURE_TYPE_
	{
		ZA_TEXTURE_TYPE_UNKNOWN,
		ZA_TEXTURE_TYPE_TEXTURE_1D,
		ZA_TEXTURE_TYPE_TEXTURE_2D,
		ZA_TEXTURE_TYPE_TEXTURE_3D
	} ZA_TEXTURE_TYPE;

	/* ********************************************************* */
	// * ZA_TEXTURE_FILER *
	/* ********************************************************* */
	typedef enum ZAAP_API ZA_TEXTURE_FILTER_ {
		ZA_TEXTURE_FILTER_LINAR = 0,
		ZA_TEXTURE_FILTER_POINT = 1
	} ZA_TEXTURE_FILTER;

	/* ********************************************************* */
	// * Texture 2D *
	/* ********************************************************* */
	
	// <Struct>
	//      ZA_TEX2D_DESC
	//
	// <Descritpion>
	//      This holds the generation information for the Texture2DCore.
	//
	// <Note>
	//    - The buffer will be static if IsDymaic is set to false.
	//    - MipMapCount has to be set to "1" if the buffer is dynamic.
	//    - A MipMapCount of 0 will regenerate all possible MipMaps for this
	//      texture.
	//
	typedef struct ZAAP_API ZA_TEX2D_DESC_ {
		ZA_FORMAT Format;
		ZA_TEXTURE_FILTER FilterType;
		bool IsDynamic;
		uint MipMapCount;

		ZA_TEX2D_DESC_(ZA_FORMAT format = ZA_FORMAT_UNKNOWN, 
			ZA_TEXTURE_FILTER filterType = ZA_TEXTURE_FILTER_LINAR, 
			bool isDynamic = false, 
			uint mipMapCount = 0)
			: Format(format),
			FilterType(filterType),
			IsDynamic(isDynamic),
			MipMapCount(mipMapCount)
		{
			
		}
	} ZA_TEX2D_DESC;

#define ZA_TEX2D_DESC_LINEAR_STATIC  zaap::graphics::ZA_TEX2D_DESC_(zaap::ZA_FORMAT_R8G8B8A8_UINT, zaap::graphics::ZA_TEXTURE_FILTER_LINAR, false, 0)
#define ZA_TEX2D_DESC_POINT_STATIC  zaap::graphics::ZA_TEX2D_DESC_(zaap::ZA_FORMAT_R8G8B8A8_UINT, zaap::graphics::ZA_TEXTURE_FILTER_POINT, false, 0)
#define ZA_TEX2D_DESC_LINEAR_DYNAMIC zaap::graphics::ZA_TEX2D_DESC_(zaap::ZA_FORMAT_R8G8B8A8_UINT, zaap::graphics::ZA_TEXTURE_FILTER_LINAR, true, 1)
#define ZA_TEX2D_DESC_POINT_DYNAMIC zaap::graphics::ZA_TEX2D_DESC_(zaap::ZA_FORMAT_R8G8B8A8_UINT, zaap::graphics::ZA_TEXTURE_FILTER_POINT, true, 1)

#define ZA_TEX2D_DESC_STATIC ZA_TEX2D_DESC_LINEAR_STATIC
#define ZA_TEX2D_DESC_DYNAMIC ZA_TEX2D_DESC_LINEAR_DYNAMIC

#ifndef ZA_TEX2D_DESC_DEFAULT
	#define ZA_TEX2D_DESC_DEFAULT ZA_TEX2D_DESC_LINEAR_STATIC
#endif

}}

namespace zaap { namespace graphics { 
	class Bitmap;
	
	namespace API {
	class TextureCore;
	class Texture2DCore;

	typedef za_ptr<TextureCore> Texture;
	typedef za_ptr<Texture2DCore> Texture2D;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // TextureCore //
	/* //////////////////////////////////////////////////////////////////////////////// */

	// <Class>
	//      TextureCore
	//
	// <Description>
	//      This class is the base class for all the other textureCores.
	//
	// <Note>
	//      This is only a representational object for the API textures.
	//
	class ZAAP_API TextureCore
	{

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Static Util //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Texture creation // 
		/* //////////////////////////////////////////////////////////////////////////////// */
		
		/* ********************************************************* */
		// * Texture2D *
		/* ********************************************************* */

		/* ##################################### */
		// # Texture2D #
		/* ##################################### */

		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API and from the given file path.
		//
		// <Input>
		//      filePath::
		//          The path for the image file.;;
		//      desc::
		//          This struct holds the information how the Texture2D should be created.;;
		//      addToTextureManager::
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.;;
		//
		// <Return>
		//      The created Texture2D.
		//
		static Texture2D CreateTexture2D(
			const String& filePath,
			const ZA_TEX2D_DESC& desc = ZA_TEX2D_DESC_DEFAULT,
			const bool& addToTextureManager = true);
		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This Function creates a @Texture2D object for the current 
		//      API from the given @Bitmap.
		//
		// <Note>
		//      Loading a file to a @Bitmap can take some more time
		//      than just loading the bytes to the @Texture2D.
		//      So don't just use a @Bitmap to load a file for
		//      a @Texture.
		//
		// <Input>
		//      bitmap::
		//          A Bitmap that is used to create a @Texture2D.;;
		//      name::
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.;;
		//      desc::
		//          This struct holds the information how the Texture2D should be created.;;
		//      addToTextureManager::
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.;;
		//
		// <Return>
		//      The created Texture2D.
		//
		static Texture2D CreateTexture2D(const Bitmap& bitmap, 
			const String& name, 
			const ZA_TEX2D_DESC& desc = ZA_TEX2D_DESC_DEFAULT,
			const bool& addToTextureManager = true);

		/* ##################################### */
		// # Texture2DCore #
		/* ##################################### */

		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API and from the given file path.
		//
		// <Input>
		//      filePath::
		//          The path for the image file.;;
		//      desc::
		//          This struct holds the information how the Texture2D should be created.;;
		//
		// <Return>
		//      The created Texture2D.
		//
		static Texture2DCore* CreateTexture2DCore(const String& filePath, const ZA_TEX2D_DESC& desc = ZA_TEX2D_DESC_DEFAULT);

		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This Function creates a @Texture2D object for the current 
		//      API from the given @Bitmap.
		//
		// <Note>
		//      Loading a file to a @Bitmap can take some more time
		//      than just loading the bytes to the @Texture2D.
		//      So don't just use a @Bitmap to load a file for
		//      a @Texture.
		//
		// <Input>
		//      bitmap::
		//          A Bitmap that is used to create a @Texture2D.;;
		//      name::
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.;;
		//      desc::
		//          This struct holds the information how the Texture2D should be created.;;
		//
		// <Return>
		//      The created Texture2D.
		//
		static Texture2DCore* CreateTexture2DCore(const Bitmap& bitmap, const String& name, const ZA_TEX2D_DESC& desc = ZA_TEX2D_DESC_DEFAULT);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Texture Class // 
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		String m_Name;

		// <Value>
		//      m_UUID
		//
		// <Description>
		//      This is a unique ID to identify the texture. It's used
		//      to compare two textures.
		//      
		UUID m_UUID;

		/* ********************************************************* */
		// * Constructor / Destructor *
		/* ********************************************************* */

		TextureCore(const String& textureName);
	public:
		virtual ~TextureCore();

		/* ********************************************************* */
		// * Operators *
		/* ********************************************************* */
		
		// <Method>
		//      operator==
		//
		// <Description>
		//      This method compares this and the given @Texture.
		//      
		// <Return>
		//      This returns the test result in form of a boolean.
		//      
		inline bool operator==(TextureCore const* other) const;
		// <Method>
		//      operator!=
		//
		// <Description>
		//      This method compares this and the given texture.
		//      
		// <Return>
		//      This returns the test result in form of a boolean.
		//      
		inline bool operator!=(TextureCore const* other) const;

		/* ********************************************************* */
		// * Getters *
		/* ********************************************************* */

		// <Method>
		//      getTextureName
		//
		// <Return>
		//      This method returns the name of the texture stored in 
		//      m_Name
		// 
		inline String getTextureName() const
		{
			return m_Name;
		}
		// <Method>
		//      getUUID
		//
		// <Return>
		//      This method returns the UUID of this texture stored in 
		//      m_UUID
		// 
		inline UUID getUUID() const
		{
			return m_UUID;
		}

		// <Method>
		//      getTextureType
		//
		// <Return>
		//      This method returns the texture type.
		//
		virtual ZA_TEXTURE_TYPE getTextureType() const = 0;

	};

	// <Function>
	//      Equal
	//      
	// <Description>
	//      This tests if the given @Textures are the same.
	//      
	// <Return>
	//      This returns the test result in form of a boolean.
	//      
	ZAAP_API inline bool Equal(TextureCore const* a, TextureCore const* b);

}}}

#include "Texture2D.h"
