#pragma once

#include "graphics/Loader.h"
#include "graphics/DX/DXVertexBuffer.h"
#include "Common.h"

#pragma warning( disable : 4251)

namespace zaap { namespace graphics	{ namespace DX {

	class ZAAP_API DXLoader : public Loader
	{
	private:
		std::vector<ID3D11Buffer*> m_Buffers;
		std::vector<DXVertexBuffer*> m_VertexBuffers;
	public: 
		Mesh loadMesh(VERTEX vertices[], uint vCount, uint indexBuffer[], uint indexCount) override;
		
		void cleanup(void) const override;
	};

}}}
