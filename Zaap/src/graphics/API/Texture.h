#pragma once

#include <Common.h>
#include <Types.h>
#include <util/UUID.h>

#pragma warning( disable : 4251)

//TODO add a validation method


namespace zaap { namespace graphics { 
	
	class Bitmap;
	namespace API {
	class Texture2D;

	typedef enum ZAAP_API ZA_TEXTURE_TYPE_
	{
		ZA_TEXTURE_TYPE_UNKNOWN,
		ZA_TEXTURE_TYPE_TEXTURE_1D,
		ZA_TEXTURE_TYPE_TEXTURE_2D,
		ZA_TEXTURE_TYPE_TEXTURE_3D
	} ZA_TEXTURE_TYPE;

	// <Class>
	//      Texture
	//
	// <Description>
	//      This class is the base class for all the other textures.
	//
	// <Note>
	//      This is only a representational object for the API textures.
	//      
	class ZAAP_API Texture
	{
		////////////////////////////////////////////////////////////////////////////////
		// Static texture management // 
		////////////////////////////////////////////////////////////////////////////////
	private:
		static std::map<UUID, Texture*> s_Textures;
		static bool s_IsCleanup;

		// <Function>
		//      AddTexture
		//
		// <Description>
		//      This method adds the given texture to s_Textures(A list
		//      of all created textures.)
		// 
		// <Note>
		//      The method is(should be) called automatically. I would
		//      advice you to just ignore it.... You have to do that anyways
		//      because it's protected... Just go! Okay! GO NOW! 
		//      
		static void AddTexture(Texture* texture);

		// <Function>
		//      RemoveTexture
		//
		// <Description>
		//      This method removes the given texture from s_Textures(A list
		//      of all created textures.)
		// 
		// <Note>
		//      The method is(should be) called automatically. It can be 
		//      ignored by outside classed and projects.
		//      
		static void RemoveTexture(Texture* texture);

		// <Function>
		//      RemoveTexture
		//
		// <Description>
		//      This method removes the given texture from s_Textures(A list
		//      of all created textures.)
		// 
		// <Note>
		//      The method is(should be) called automatically. It can be 
		//      ignored by outside classed and projects.
		//      
		static void RemoveTexture(UUID textureUUID);
	
	public:
		// <Function>
		//      Cleanup
		//
		// <Description>
		//      This method deletes every Texture from the s_Texture list.
		//      This is done by calling the destroy function from every 
		//      list member.
		//      
		static void Cleanup();

	public:
		////////////////////////////////////////////////////////////////////////////////
		// Texture creation // 
		////////////////////////////////////////////////////////////////////////////////
		
		//******************************
		// Texture2D
		//******************************
		
		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API from the given file path.
		//
		// <Input>
		//      name:   
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.
		//      
		//      filePath:   
		//          The path for the image file.
		//      
		//      addToTextureManager :   
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.
		//      
		// <Return>
		//      The created Texture2D.
		//
		static Texture2D* CreateTexture2D(char const* name, char const* filePath, bool addToTextureManager = true);
		
		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API from the given file path.
		//
		// <Input>
		//      name:   
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.
		//      
		//      filePath:   
		//          The path for the image file.
		//      
		//      addToTextureManager :   
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.
		//      
		// <Return>
		//      The created Texture2D.
		//
		static Texture2D* CreateTexture2D(String name, String filePath, bool addToTextureManager = true);
		
		// <Function>
		//      CreateTexture2D
		//
		// <Description>
		//      This constructor creates a @Texture2D object for the current 
		//      API from the given @Bitmap.
		//
		// <Note>
		//      Loading a file to a @Bitmap can take some more time
		//      than just loading the bytes to the @Texture2D.
		//      So don't just use a @Bitmap to load a file for
		//      a @Texture.
		//
		// <Input>
		//      name:   
		//          The name for the @TextureManager. The name is 
		//          also used for debugging.
		//      
		//      bitmap:   
		//          A Bitmap that is used to create a @Texture2D.
		//      
		//      addToTextureManager :   
		//          This boolean indicated if the created @Texture2D should be 
		//          added to the @TextureManager.
		//      
		// <Return>
		//      The created Texture2D.
		//
		static Texture2D* CreateTexture2D(String name, Bitmap bitmap, bool addToTextureManager = true);

		////////////////////////////////////////////////////////////////////////////////
		// Texture Class // 
		////////////////////////////////////////////////////////////////////////////////
	protected:
		String m_TextureName;

		// <Value>
		//      m_UUID
		//
		// <Description>
		//      This is a unique ID to identify the texture. It's used
		//      to compare two textures.
		//      
		UUID m_UUID;

		ZA_TEXTURE_TYPE m_TextureType;
		
		Texture(const String& textureName, ZA_TEXTURE_TYPE textureType);
	public:
		virtual ~Texture();

		// <Function>
		//      destroy
		//
		// <Description>
		//      This method destroys the texture object.
		//
		void destroy();

		////////////////////////////////////////////////////////////////////////////////
		// Operators // 
		////////////////////////////////////////////////////////////////////////////////
		
		// <Function>
		//      operator==
		//
		// <Description>
		//      This method compares this and the given texture.
		//      
		// <Return>
		//      This returns the test result in from of a boolean.
		//      
		inline bool operator==(Texture const* other) const;

		// <Function>
		//      operator!=
		//
		// <Description>
		//      This method compares this and the given texture.
		//      
		// <Return>
		//      This returns the test result in from of a boolean.
		//      
		inline bool operator!=(Texture const* other) const;

		////////////////////////////////////////////////////////////////////////////////
		// Getters // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      getTextureName
		//
		// <Return>
		//      This method returns the name of the texture stored in 
		//      m_TextureName
		// 
		inline String getTextureName() const;

		// <Function>
		//      getTextureType
		//
		// <Return>
		//      This method returns the texture type stored in 
		//      m_TextureType
		// 
		inline ZA_TEXTURE_TYPE getTextureType() const;

		// <Function>
		//      getUUID
		//
		// <Return>
		//      This method returns the UUID of this texture stored in 
		//      m_UUID
		// 
		inline UUID getUUID() const;
	};

	// <Function>
	//      Equal
	//      
	// <Description>
	//      This tests if the given textures are the same.
	//      
	// <Return>
	//      This returns the test result in from of a boolean.
	//      
	ZAAP_API inline bool Equal(Texture const* a, const Texture const* b);


}}}
