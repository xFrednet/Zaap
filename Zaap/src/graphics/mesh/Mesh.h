#pragma once

#include <Common.h>
#include <Types.h>

#include <maths/Maths.h>
#include <graphics/API/VertexBuffer.h>
#include <graphics/API/Texture2D.h>
#include <graphics/Material.h>

namespace zaap { namespace graphics {

	// <Struct>
	//		ZA_D_VERTEX
	//
	// <Description>
	//		This struct represents a vertex  for the @DefaultShader.
	//
	// <Note>
	//		... Yes that is a "d" joke I'm sorry!!!<\n>
	//		Just be happy that I didn't add anything about the 
	//		"sizeof" function.... ups.
	//
	// <Members>
	//		Position::
	//			The position of this vertex.;;
	//		Normal::
	//			The Normal of this Vertex.;;
	//		TexCoord::
	//			The texture coordinate of this vertex.;;
	//		Material::
	//			The index of the material in the @Mesh class and therefor also
	//			in the shader.;;
	//
	struct ZAAP_API ZA_D_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		Vec2 TexCoord;
		uint Material;
	};

	struct ZAAP_API ZA_TERRAIN_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		Vec3 TexMapColor;
		Vec2 TexCoord;

		ZA_TERRAIN_VERTEX(Vec3 position, Vec3 normal, Vec3 texMapColor, Vec2 texCoord);
		ZA_TERRAIN_VERTEX();
	};

	class ZAAP_API Mesh
	{
	private:
		friend class Loader;
	public:
		static Mesh GetOrLoad(const String& file);
	protected:

		// <Value>
		//		m_Name
		//
		// <Description>
		//		This stores the name of the @Mesh. If the @Mesh is loaded from 
		//		a file, the file name is used for this value.
		//
		// <Note>
		//		The name is used by the @MeshManager for something.
		//
		String m_Name;

		// <Value>
		//		m_VertexBuffer
		//
		// <Description>
		//		This is the @VertexBuffer of the @Mesh.
		//
		API::VertexBuffer* m_VertexBuffer;

		// <Value>
		//		m_Texture
		//
		// <Description>
		//		This is the Texture of this mesh.
		//
		API::Texture2D* m_Texture;

		// <Value>
		//		m_Materials
		//
		// <Description>
		//		This is a array of the @Materials that are used 
		//		by this mesh.
		//
		Material* m_Materials;

		// <Value>
		//		m_MaterialCount
		//
		// <Descritpion>
		//		This is the amount of @Materials that are stored 
		//		inside m_Materials.
		//
		uint m_MaterialCount;

	public:
		Mesh();
		Mesh(String name, API::VertexBuffer* vertexBuffer);
		Mesh(String name, API::VertexBuffer* vertexBuffer, Material const* materials, uint materialCount);
		
		~Mesh();

		// vertex buffer
		inline API::VertexBuffer* getVertexBuffer() const;
		inline uint getVertexCount() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Texture //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline void setTexture(API::Texture2D* texture);
		inline API::Texture2D* getTexture() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Material //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline void setMaterials(const Material* &materials, const uint& materialCount);
		inline Material* getMaterials() const;
		inline uint getMaterialCount() const;

		inline String getName() const;
	};

}}
