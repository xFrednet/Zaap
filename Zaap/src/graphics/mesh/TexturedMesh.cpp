#include "TexturedMesh.h"

namespace zaap { namespace graphics {
	
	TexturedMesh::TexturedMesh(String name, API::VertexBuffer* vertexBuffer, Texture2D* texture)
		: Mesh(name, vertexBuffer),
		m_Texture(texture)
	{}

	TexturedMesh::TexturedMesh()
		: m_Texture(nullptr)
	{}

	Texture2D* TexturedMesh::getTexture() const
	{
		return m_Texture;
	}
}}