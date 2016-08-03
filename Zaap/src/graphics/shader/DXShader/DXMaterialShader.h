#pragma once

#include <Common.h>

#include <graphics/shader/DXShader/DXShader.h>

#include <graphics/Material.h>
#include <graphics/camera/Camera.h>
#include <maths/Maths.h>
#include <graphics/light/LightSetup.h>

namespace zaap { namespace graphics { namespace DX {

	class ZAAP_API DXMaterialShader : public DXShader
	{
	private:
		static const uint SUPPORTET_LIGHT_COUNT = 8;

		struct VS_LIGHT_BUFFER
		{
		public:
			uint LightCount;
		private:
			math::Vec3 padding;
		public:
			math::Vec4 Position[SUPPORTET_LIGHT_COUNT];
		};

		struct VS_SCENE_BUFFER
		{
			math::Vec3 CameraPosition;
			float padding;
		};

		struct PS_LIGHT_BUFFER
		{
		public:
			uint LightCount;
		private:
			math::Vec3 padding;
		public:
			Color AmbientLightColor;
			Color LightColor[SUPPORTET_LIGHT_COUNT];
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
		VS_LIGHT_BUFFER m_VSLightStruct;
		ID3D11Buffer *m_VSLightBuffer;

		PS_LIGHT_BUFFER m_PSLightStruct;
		ID3D11Buffer *m_PSLightBuffer;
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
		void loadLightSetup(const LightSetup* lightSetup);

		//material loader
		void loadMaterials(Material const* materials, uint count);

		void start() const override;
		void cleanup() override;
	};

}}}
