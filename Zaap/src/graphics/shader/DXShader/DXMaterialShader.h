#pragma once

#include <Common.h>

#include <graphics/shader/DXShader/DXShader.h>

#include <graphics/Material.h>
#include <graphics/mesh/Mesh.h>
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

		struct PS_LIGHTCOLOR_BUFFER
		{
			Color lightColor;
		};

		static const uint MAX_MATERIAL_COUNT = 8;
		struct PS_MATERIAL
		{
			math::Vec3 Color;
			float Reflectivity;
		};
		struct PS_MATERIAL_BUFFER
		{
			PS_MATERIAL Materials[MAX_MATERIAL_COUNT];
		};

	protected:
		//Matrix buffer
		VS_MATRIX_BUFFER m_MatrixStruct;
		ID3D11Buffer *m_MatrixBuffer;
		void loadMatrixBuffer() const;

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
		void loadTransformationMatrix(math::Mat4 &matrix);
		void loadProjectionMatrix(math::Mat4 &matrix);
		void loadViewMatrix(math::Mat4 &matrix);

		//light loader
		void loadLight(const Light* light);

		//material loader
		void loadMaterials(Material const* materials, uint count);

		void start() const override;
		void cleanup() override;

	};

}}}
