#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/API/DX/DXCommon.h>
#include <graphics/API/DX/shader/DXShader.h>
#include <graphics/shader/types/FontShader2D.h>

namespace zaap { namespace graphics { namespace DX {
	
	class DXFontShader2D : public FontShader2D, public DXShader
	{
	protected:
		ID3D11Buffer* m_MatrixBuffer;
		void loadMatrixBuffer() const override;

		ID3D11Buffer* m_ColorBuffer;
		void loadTextColor() const override;
	public:
		DXFontShader2D();

		void cleanup() override;

		void start() const override;
		void stop() const override;
	};

}}}
