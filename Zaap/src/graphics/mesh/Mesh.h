#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/VertexBuffer.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {

	struct ZAAP_API ZA_TEXTURE_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		Vec2 TexCoord;

		ZA_TEXTURE_VERTEX();
		ZA_TEXTURE_VERTEX(Vec3 position, Vec3 normal, Vec2 texCoord);
	};
	
	struct ZAAP_API ZA_MATERIAL_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		uint Material;

		ZA_MATERIAL_VERTEX(Vec3 Position, Vec3 Normal, uint Material);
		ZA_MATERIAL_VERTEX();
	};

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

	typedef enum ZAAP_API ZA_MESH_TYPE_
	{
		ZA_MESH_TYPE_UNKNOWN,
		ZA_MESH_TYPE_TEXTURED,
		ZA_MESH_TYPE_MATERIAL
	} ZA_MESH_TYPE;

	class ZAAP_API Mesh
	{
	public:
		static Mesh* GetOrLoad(const String& file, bool isTexturedMesh = true);
	protected:
		String m_Name;
		API::VertexBuffer* m_VertexBuffer;
		const ZA_MESH_TYPE m_TYPE;

		Mesh(String name, API::VertexBuffer* vertexBuffer, ZA_MESH_TYPE type);
	public:

		//vertex buffer
		API::VertexBuffer* getVertexBuffer() const;
		uint getVertexCount() const;

		String getName() const;

		ZA_MESH_TYPE getType() const;
		ZA_SHADER_TYPE getTargetShader() const;
	};

}}