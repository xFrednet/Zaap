#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <graphics/Material.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API MaterialMesh : public Mesh
	{
	private:
		Material* m_Materials;
		uint m_MaterialCount;
	public:
		MaterialMesh();
		MaterialMesh(String name, API::VertexBuffer *vertexBuffer, Material* materials, uint materialCount);

		//getters
		Material* getMaterials(void) const;
		uint getMaterialCount() const;

	};
		
}}
