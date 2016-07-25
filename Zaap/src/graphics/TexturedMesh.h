#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/Texture2D.h>
#include <graphics/Mesh.h>

namespace zaap
{
	namespace graphics
	{
		class ZAAP_API TexturedMesh
		{
		private:
			Mesh m_Mesh;
			Texture2D *m_Texture;
			String m_Name;

		public:
			TexturedMesh(String name, Mesh &mesh, Texture2D* texture);
			TexturedMesh(void);
			~TexturedMesh(void);

			inline Mesh* getMesh(void) {return &m_Mesh;}
			inline Texture2D* getTexture(void) const { return m_Texture; };
			inline String getName(void) const { return m_Name; };
		};
	}
}
