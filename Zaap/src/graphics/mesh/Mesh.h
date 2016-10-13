#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/VertexBuffer.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {

	struct ZAAP_API TEXTURE_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		Vec2 TexCoord;

		TEXTURE_VERTEX();
		TEXTURE_VERTEX(Vec3 position, Vec3 normal, Vec2 texCoord);
	};
	
	struct ZAAP_API MATERIAL_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		uint Material;

		MATERIAL_VERTEX(Vec3 Position, Vec3 Normal, uint Material);
		MATERIAL_VERTEX();
	};

	struct ZAAP_API TERRAIN_VERTEX
	{
		Vec3 Position;
		Vec3 Normal;
		Vec3 TexMapColor;
		Vec2 TexCoord;

		TERRAIN_VERTEX(Vec3 position, Vec3 normal, Vec3 texMapColor, Vec2 texCoord);
		TERRAIN_VERTEX();
	};

	enum class ZAAP_API MeshType
	{
		NONE,
		TEXTURED_MESH,
		MATERIAL_MESH,
		TERRAIN
	};

	class ZAAP_API Mesh
	{
	protected:
		String m_Name;
		API::VertexBuffer* m_VertexBuffer;
		const MeshType m_TYPE;

		Mesh();
		Mesh(String name, API::VertexBuffer* vertexBuffer, MeshType type);
	public:

		//vertex buffer
		API::VertexBuffer* getVertexBuffer(void) const;
		uint getVertexCount(void) const;

		String getName(void) const;

		MeshType getType(void) const;
 	};

}}