#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>
#include <graphics/mesh/Mesh.h>

namespace zaap { namespace graphics {
	class ZAAP_API TexturedMesh : public Mesh
	{
	private:
		API::Texture2D *m_Texture;

	public:
		TexturedMesh(String name, API::VertexBuffer* vertexBuffer, API::Texture2D* texture);

		API::Texture2D* getTexture(void) const;
		void setTexture(API::Texture2D *texture);
	};
}}
