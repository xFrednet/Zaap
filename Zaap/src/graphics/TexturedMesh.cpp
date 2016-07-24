#include "TexturedMesh.h"

namespace zaap { namespace graphics {
	
	TexturedMesh::TexturedMesh(String name, Mesh& mesh, Texture2D* texture)
		: m_Mesh(mesh),
		m_Texture(texture),
		m_Name(name)
	{}

	TexturedMesh::TexturedMesh()
		: m_Texture(nullptr),
		m_Name(nullptr)
	{}

	TexturedMesh::~TexturedMesh()
	{}
}}