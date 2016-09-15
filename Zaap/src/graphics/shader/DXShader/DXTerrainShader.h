#pragma once

#include <graphics/shader/DXShader/DXShader.h>

#include <Common.h>
#include <Types.h>

#include <graphics/light/LightSetup.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXTerrainShader : public DXShader
	{
		static const uint SUPPORTET_LIGHT_COUNT = 8;

		struct VS_LIGHT_BUFFER
		{
			uint LightCount;
		private:
			math::Vec3 padding;
		public:
			math::Vec4 Position[SUPPORTET_LIGHT_COUNT];
		};

		struct PS_LIGHT_BUFFER
		{
			uint LightCount;
		private:
			math::Vec3 padding;
		public:
			Color LightColor[SUPPORTET_LIGHT_COUNT];
		};
	protected:
		VS_MATRIX_BUFFER m_MatrixStruct;
		ID3D11Buffer *m_MatrixBuffer;
		void loadMatrixBuffer() const;

		VS_LIGHT_BUFFER m_VSLightStruct;
		ID3D11Buffer *m_VSLightBuffer;
		
		PS_LIGHT_BUFFER m_PSLightStruct;
		ID3D11Buffer *m_PSLightBuffer;
		void loadLightBuffers() const;

	public:
		DXTerrainShader();

		//matrix loader
		void loadTransformationMatrix(math::Mat4 matrix);
		void loadProjectionMatrix(math::Mat4 matrix);
		void loadViewMatrix(math::Mat4 matrix);

		//lightSetup loader
		void loadLightSetup(const LightSetup const *lightSetup);

		void start() const override;
		void cleanup() override;
	};
		
	
}}}
