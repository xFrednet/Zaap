#pragma once

#include <Common.h>

#include <graphics/shader/DXShader/DXShader.h>

#include <graphics/Material.h>
#include <graphics/camera/Camera.h>
#include <maths/Maths.h>
#include <graphics/light/Light.h>

namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXMaterialShader : public DXShader
	{
	private:
		
		struct VS_LIGHTPOSITION_BUFFER
		{
			math::Vec4 Position;
		};

		struct VS_SCENE_BUFFER
		{
			math::Vec3 CameraPosition;
			float padding;
		};

		struct PS_LIGHTCOLOR_BUFFER
		{
			Color lightColor;
		};

		struct PS_MATERIAL
		{
			math::Vec3 Color;
			float Reflectivity;
		};
		struct PS_MATERIAL_BUFFER
		{
			PS_MATERIAL Materials[8];
		};
	protected:
		//Matrix buffer
		VS_MATRIX_BUFFER m_MatrixStruct;
		ID3D11Buffer *m_MatrixBuffer;
		void loadMatrixBuffer() const;

		//Scene buffer
		VS_SCENE_BUFFER m_SceneStruct;
		ID3D11Buffer *m_SceneBuffer;
		void loadSceneBuffer() const;

		//Light buffers
		VS_LIGHTPOSITION_BUFFER m_LightPositionStruct;
		ID3D11Buffer *m_LightPositionBuffer;

		PS_LIGHTCOLOR_BUFFER m_LightColorStruct;
		ID3D11Buffer *m_LightColorBuffer;
		void loadLightBuffers() const;

		//Material buffer
		PS_MATERIAL_BUFFER m_MaterialStruct;
		ID3D11Buffer *m_MaterialBuffer;
		void loadMaterialBuffer() const;

	public:
		DXMaterialShader();

		//matrix loader
		void loadTransformationMatrix(math::Mat4 matrix);
		void loadProjectionMatrix(math::Mat4 matrix);
		void loadViewMatrix(math::Mat4 matrix);

		//camera
		void loadCamera(Camera* camera);

		//light loader
		void loadLight(const Light* light);

		//material loader
		void loadMaterials(Material const* materials, uint count);

		void start() const override;
		void cleanup() override;

	};

}}}
