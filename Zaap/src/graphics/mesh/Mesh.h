#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/VertexBuffer.h>
#include <maths/Maths.h>

namespace zaap { namespace graphics {

	struct ZAAP_API TEXTURE_VERTEX
	{
		math::Vec3 Position;
		math::Vec3 Normal;
		math::Vec2 TexCoord;

		TEXTURE_VERTEX();
		TEXTURE_VERTEX(math::Vec3 position, math::Vec3 normal, math::Vec2 texCoord);
	};
	
	struct ZAAP_API MATERIAL_VERTEX
	{
		math::Vec3 Position;
		math::Vec3 Normal;
		uint Material;

		MATERIAL_VERTEX(math::Vec3 Position, math::Vec3 Normal, uint Material);
		MATERIAL_VERTEX();
	};

	struct ZAAP_API TERRAIN_VERTEX
	{
		math::Vec3 Position;
		math::Vec3 Normal;
		math::Vec3 TexMapColor;
		math::Vec2 TexCoord;

		TERRAIN_VERTEX(math::Vec3 position, math::Vec3 normal, math::Vec3 texMapColor, math::Vec2 texCoord);
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