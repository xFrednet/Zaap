#pragma once

#include <Common.h>
#include <Types.h>

#include <graphics/light/LightSetup.h>
#include <graphics/API/DX/DXCommon.h>
#include <graphics/shader/types/TerrainShader.h>
#include <graphics/API/DX/shader/DXShader.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXTerrainShader : public TerrainShader, public DXShader
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
		ID3D11Buffer *m_MatrixBuffer;
		void loadMatrixBuffer() const override;

		ID3D11Buffer *m_VSLightBuffer;
		ID3D11Buffer *m_PSLightBuffer;
		void loadLightBuffers() const override;

	public:
		DXTerrainShader();

		void start() const override;
		void stop() const override;
		void cleanup() override;
	};
		
	
}}}
