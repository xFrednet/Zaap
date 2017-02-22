#pragma once

#include <Common.h>
#include <Types.h>

#include "Mesh.h"

namespace zaap { namespace graphics {
	namespace API {
		class Texture2D;
	}

	// <Class>
	//      MeshManager
	//
	// <Description>
	//      This class manages the loaded Meshes. It keeps track how many
	//      instance of the Mesh are used. The mesh gets deleted if the count
	//      drops to zero.
	//
	// <Note>
	//      This manager can be ignored by the normal user. (Well it's not
	//      like there are any other users than me right now...
	//      WTF am I doing with my life!!!)
	//
	class ZAAP_API MeshManager
	{
	private:
		friend class Mesh;
	public:
		// <Struct>
		//      ZA_MESHMANAGER_MESH_INFO_,
		//      ZA_MESHMANAGER_MESH_INFO
		//
		// <Description>
		//      This is a struct that is used in the @Mesh map.
		//      It stores the @Mesh and the UseCount.
		//
		// <Members>
		//      Mesh:
		//          This is a pointer to the @Mesh. The
		//          @Mesh also stores the name of the @Mesh.
		//     UseCount:
		//          This value keeps track how often the stored
		//          @Mesh is used. This is done by adding one on a
		//          request call and subtraction one on the @Mesh
		//          release.
		//          The @Mesh in the struct will be deleted if 
		//          UseCount hits zero. (I might add a option to
		//          keep it beyond that point. "might" is the 
		//          important word)
		//
		typedef struct ZAAP_API ZA_MESHMANAGER_MESH_INFO_
		{
			Mesh Mesh;
			uint UseCount;
		} ZA_MESHMANAGER_MESH_INFO;

	private:
		static std::map<String, ZA_MESHMANAGER_MESH_INFO> s_MeshMap;

		// <Private Constructor>
		//      This Constructor is private to prevent the
		//      user from creating a instance of this class.
		//
		MeshManager(void) {}
		
		// <Function>
		//      AddMesh
		//
		// <Description>
		//      This method adds the @Mesh to the @Mesh map.
		//
		// <Note>
		//    - The use count of the submitted @Mesh is set to 1
		//      because the submitted @Mesh is counted as a use.
		//    - This method will be called by the @Mesh class.
		//
		// <Input>
		//      mesh:
		//          The @Mesh that should be added to the @Mesh map.
		//
		static void Add(const Mesh& mesh);

		// <Function>
		//      ReleasedMesh
		//
		// <Description>
		//      This function subtracts one from the use count
		//      of the submitted @Mesh. The @Mesh will be deleted
		//      if the use count hits zero.
		//
		// <Note>
		//      This function is private it'll be called by the @Mesh
		//      class and other friends... Oh wait it has no other
		//      friends.
		//
		// <Input>
		//      mesh::
		//          The @Mesh that should that was released.;;
		//
		static void ReleasedMesh(const Mesh& mesh);
		
		// <Function>
		//      RemoveMesh
		//
		// <Description>
		//      This removes the entered @Mesh from the @Mesh map
		//      this is done without checking the use count or
		//      any other values.
		//
		// <Note>
		//      This calls the RemoveMesh method with the name
		//      of the submitted @Mesh.
		//
		// <Input>
		//      mesh::
		//          The @Mesh that should be removed from the map.;;
		//
		static void RemoveMesh(const Mesh& mesh);
		// <Function>
		//      RemoveMesh
		//
		// <Description>
		//      This removes the @Mesh that is stored under the 
		//      entered name this is done without checking the
		//      use count or any other values.
		//
		// <Input>
		//      name::
		//          The name of the @Mesh that should be removed
		//          from the map.;;
		//
		static void RemoveMesh(const String& name);
	public:
		// <Function>
		//      GetMesh
		//
		// <Description>
		//      This method returns the @Mesh that is stored under the 
		//      entered name.
		//
		// <Input>
		//      name::
		//          The name of the requested @Mesh.;;
		//
		// <Return>
		//      This returns the @Mesh that was stored under the entered 
		//      name. It can return Null if there is no @Mesh that is 
		//      linked to the name.
		//
		static Mesh Get(const String& name);

		// <Function>
		//      GetUseCount
		//
		// <Description>
		//      This returns the use count of the @Mesh.
		//      This can also return 0 if the @Mesh isn't a 
		//      member of the @Mesh map
		//
		// <Note>
		//      This calls the second GetUseCount method with
		//      the name of this @Mesh
		//
		// <Input>
		//      mesh::
		//          The @Mesh to receive the requested use count.;;
		//
		// <Return>
		//      This returns the use count value of the @Mesh.
		//
		static uint GetUseCount(const Mesh& mesh);
		// <Function>
		//      GetUseCount
		//
		// <Description>
		//      This returns the use count of the @Mesh that is 
		//      stored under the name. This can also return 0
		//      if the name is no a member of the @Mesh map.
		//
		// <Input>
		//      mesh::
		//          The @Mesh to receive the requested use count.;;
		//
		// <Return>
		//      This returns the use count value of the @Mesh.
		//
		static uint GetUseCount(const String& name);

		// <Function>
		//      Contains
		//
		// <Description>
		//      This method checks the submitted @Mesh
		//      is a member of this manager.
		//
		// <Note>
		//    - This should always return true because every
		//      @Mesh should be a member of the @Mesh map.
		//    - This used the name of the @Mesh to test if
		//      the @Mesh is a member of the @Mesh map.
		//
		// <Input>
		//      mesh::
		//          The @Mesh that should be checked.;;
		//
		// <Return>
		//      This returns the test result.
		//
		static bool Contains(const Mesh& mesh);
		// <Function>
		//      Contains
		//
		// <Description>
		//      This method checks if there is a @Mesh that
		//      is stored with submitted name.
		//
		// <Input>
		//      name::
		//          The name that should be checked.;;
		//
		// <Return>
		//      This returns the test result.
		//
		static bool Contains(const String& name);

		// <Function>
		//      Cleanup
		//
		// <Description>
		//      This method releases all meshes that are in the 
		//      @Mesh map list.
		//
		// <Note>
		//  -   This method is called by the @Application class. It should
		//      only be called if the @Application class isn't used for some
		//      reason.
		//  -   Calling this method causes all meshes to be released. 
		//      rendering after calling this could and will lead to 
		//      some errors.
		//
		static void Cleanup();
	};

}}
