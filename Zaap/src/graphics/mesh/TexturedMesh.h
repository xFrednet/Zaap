#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>
#include <graphics/mesh/Mesh.h>

namespace zaap { namespace graphics {
	class ZAAP_API TexturedMesh : public Mesh
	{
	private:
		Texture2D *m_Texture;

	public:
		TexturedMesh(String name, API::VertexBuffer* vertexBuffer, Texture2D* texture);
		TexturedMesh(void);

		Texture2D* getTexture(void) const;
		void setTexture(Texture2D *texture);
	};
}}
