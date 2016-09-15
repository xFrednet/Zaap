#include "TexturedMesh.h"

namespace zaap { namespace graphics {
	
	TexturedMesh::TexturedMesh(String name, API::VertexBuffer* vertexBuffer, API::Texture2D* texture)
		: Mesh(name, vertexBuffer, MeshType::TEXTURED_MESH),
		m_Texture(texture)
	{}

	TexturedMesh::TexturedMesh()
		: m_Texture(nullptr)
	{}

	API::Texture2D* TexturedMesh::getTexture() const
	{
		return m_Texture;
	}

	void TexturedMesh::setTexture(API::Texture2D* texture)
	{
		m_Texture = texture;
	}
}}