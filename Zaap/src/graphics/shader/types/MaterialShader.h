#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/shader/Shader.h>
#include <graphics/light/LightSetup.h>
#include <graphics/Material.h>

namespace zaap { namespace graphics {
	class MaterialMesh;

	class ZAAP_API MaterialShader : public Shader
	{
	protected:
		//Matrix buffer
		ZA_VS_MATRIX_BUFFER m_MatrixBufferStruct;
		virtual void loadMatrixBuffer() const = 0;

		//Scene buffer
		ZA_VS_SCENE_BUFFER m_SceneBufferStruct;
		virtual void loadSceneBuffer() const = 0;
		
		//Light buffers
		ZA_VS_LIGHT_BUFFER m_VSLightBufferStruct;
		ZA_PS_LIGHT_BUFFER m_PSLightBufferStruct;
		virtual void loadLightBuffers() const = 0;

		//Material buffer
		ZA_PS_MATERIAL_BUFFER m_MaterialBufferStruct;
		virtual void loadMaterialBuffer() const = 0;
	public:
		//Matrix buffer
		void setMatrixBuffer(ZA_VS_MATRIX_BUFFER matrixBuffer);
		void setProjectionMatrix(Mat4 projectionMatrix);
		void setTransformationMatrix(Mat4 transformationMatrix);
		void setViewMatrix(Mat4 viewMatrix);

		//Scene buffer
		void setCameraPosition(Vec3 cameraPosition);

		//Light buffer
		void loadLightSetup(const LightSetup const* lightSetup);

		//Material buffer
		void loadMaterials(const MaterialMesh const* mesh);
		void loadMaterials(const Material const* materials, uint materialCount);

	};

}}

