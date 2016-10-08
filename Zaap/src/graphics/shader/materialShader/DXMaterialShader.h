#pragma once

#include <Common.h>

#include <graphics/Material.h>
#include <graphics/camera/Camera.h>
#include <maths/Maths.h>
#include <graphics/light/LightSetup.h>
#include <graphics/shader/DXShader.h>
#include "MaterialShader.h"

namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXMaterialShader : public MaterialShader, public DXShader
	{
	protected:
		//Matrix buffer
		ID3D11Buffer *m_MatrixBuffer;
		void loadMatrixBuffer() const override;

		//Scene buffer
		ID3D11Buffer *m_SceneBuffer;
		void loadSceneBuffer() const override;

		//Light buffers
		ID3D11Buffer *m_VSLightBuffer;
		ID3D11Buffer *m_PSLightBuffer;
		void loadLightBuffers() const override;

		//Material buffer
		ID3D11Buffer *m_MaterialBuffer;
		void loadMaterialBuffer() const override;

	public:
		DXMaterialShader();

		//Util
		void start() const override;
		void stop() const override;
		void cleanup() override;
	};

}}}
