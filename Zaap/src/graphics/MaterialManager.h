﻿#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/Material.h>

namespace zaap { namespace graphics {
	
	// <Class>
	//      MaterialManager
	//
	// <Description>
	//      This manages all loaded @Materials. They can be accessed by name.
	//
	//
	class ZAAP_API MaterialManager
	{
	private:
		static std::map<String, Material> s_Materials;

		MaterialManager() {}
	public:
		// <Function>
		//      LoadMTLFile
		//
		// <Description>
		//      This load the @Materials from the submitted MTL file.
		//
		// <Note>
		//      The @Materials are directly added to this manager.
		//
		// <Input>
		//      file:
		//          The file path for the MTLFile.
		//
		// <Return>
		//      This returns a @ZA_RESULT which indicates if the method 
		//      executed successfully. 
		//
		static ZA_RESULT LoadMTLFile(String file);

		// <Function>
		//      Add
		//
		// <Description>
		//      Adds the submitted @Material to the @Material list.
		//
		// <Note>
		//      This method also checks if the submitted name already 
		//      links to a different @Material. The old @Material 
		//      wont be overridden.
		//
		// <Input>
		//      name:
		//          The name for the submitted @Material.
		//      material:
		//          The @Material that should be stored under the name.
		//
		static void Add(String name, Material material);

		// <Function>
		//      Get
		//
		// <Description>
		//      Returns the submitted @Material from the @Material list.
		//
		// <Note>
		//      This method returns a default @Material if there is no
		//      @Material with the requested name.
		//
		// <Input>
		//      name:
		//          The name of the requested @Material.
		//
		// <Return>
		//      This function returns the stored @Material or a default
		//      @Material if there is no entry under the name
		//
		static Material Get(const String& name);

		// <Function>
		//      Contains
		//
		// <Description>
		//      This method checks if there is a @Material
		//      with the requested name.
		//
		// <Input>
		//      name:
		//          The name that should be checked.
		//
		// <Return>
		//      This returns the test result.
		//
		static bool Contains(const String& name);

		// <Function>
		//      Cleanup
		//
		// <Description>
		//      This method releases all materials that are in the 
		//      @Material list.
		//
		// <Note>
		//      -   This method is called by the @Application class. It should
		//          only be called if the @Application class isn't used for some
		//          reason.
		//      -   Calling this method causes all materials to be released. 
		//          rendering after calling this could lead to some errors.
		//
		static void Cleanup();
	};
		
}}
