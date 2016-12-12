#pragma once

#include <Common.h>
#include <maths/Maths.h>

#include "shader/types/FontShader2D.h"
#include "shader/types/MaterialShader.h"
#include "shader/types/TextureShader.h"
#include "shader/types/TerrainShader.h"
#include "API/Texture2D.h"

namespace zaap { namespace graphics {
	class Scene;

	// I left out the "API" namespace because i'm too lazy to type it every time

	class ZAAP_API Renderer3D
	{
		//Static constructor
	public:
		//
		//
		//
		//@return: The renderer for the chousen API
		Renderer3D* Init();

	protected:
		//Projection Matrix
		float m_FOV = 90.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		Mat4 m_ProjectionMatrix;

		//Rendertarget
		API::Texture2D* m_Rendertarget;
		uint m_Width;
		uint m_Height;

		//Shader
		ZA_SHADER_TYPE  m_ActiveShaderType;
		TextureShader*  m_TextureShader;
		MaterialShader* m_MaterialShader;
		TerrainShader*  m_TerrainShader;
		FontShader2D*   m_FontShader2D;

		//Constructor to init values
		Renderer3D();
	public:
		virtual ~Renderer3D() {}

		//
		// Shader stuff
		//

		//Shader loaders
		void loadTransformationMatrix(const Mat4& transformationMatrix) const;
		void loadLightSetup(const LightSetup& LightSetup) const;
		void loadScene(const Scene const* scene) const;

		//starting shaders
		void startShader(ZA_SHADER_TYPE shader);
		Shader* getShader(ZA_SHADER_TYPE shader);

		//
		// Alpha channel
		//
		virtual void setAlphaTestingState(bool enabled);
		//these two methods just acces the "setAlphaTestingState(bool)" method
		inline void enableAlphaTesting();
		inline void disableAlphaTesting();
	};

}}
