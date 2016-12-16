#include "DXRenderer3D.h"

namespace zaap { namespace graphics { namespace DX {
	DXRenderer3D::DXRenderer3D()
	{
		m_Dev = DXContext::GetDevice();
		m_Devcon = DXContext::GetDevContext();
	}

	void DXRenderer3D::cleanupAPIRenderer()
	{
		//These values are created and therefore deleted by DXContest
		m_Dev = nullptr;
		m_Devcon = nullptr;
	}
}}}
