#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/mesh/Mesh.h>
#include <graphics/Material.h>
#include <graphics/shader/Shader.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API MaterialMesh : public Mesh
	{
	private:
		Material m_Materials[ZAAP_SHADER_MATERIAL_COUNT];
		uint m_MaterialCount;
	public:
		MaterialMesh(String name, API::VertexBuffer *vertexBuffer, Material materials[], uint materialCount);

		//getters
		Material const* getMaterials(void) const;
		uint getMaterialCount() const;

	};
		
}}
