#pragma once

#include <Common.h>
#include <Types.h>

#include <entity/light/LightSetup.h>
#include <graphics/API/DX/DXCommon.h>
#include <graphics/shader/TerrainShader.h>
#include <graphics/API/DX/shader/DXShader.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXTerrainShader : public TerrainShader, public DXShader
	{
		static const uint SUPPORTET_LIGHT_COUNT = 8;

		struct VS_LIGHT_BUFFER
		{
			uint LightCount;
		private:
			Vec3 padding;
		public:
			Vec4 Position[SUPPORTET_LIGHT_COUNT];
		};

		struct PS_LIGHT_BUFFER
		{
			uint LightCount;
		private:
			Vec3 padding;
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

		~DXTerrainShader();

		void start() const override;
		void stop() const override;
	};
		
	
}}}
