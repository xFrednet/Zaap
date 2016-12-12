#pragma once

#include <Common.h>
#include <maths/Maths.h>

#include "shader/types/FontShader2D.h"
#include "shader/types/MaterialShader.h"
#include "shader/types/TextureShader.h"
#include "shader/types/TerrainShader.h"
#include "API/Texture2D.h"
#include "camera/ViewFrustum.h"

namespace zaap { namespace graphics {
	class Scene;

	// I left out the "API" namespace because I'm too lazy to type it every time

	// <class>
	//      Renderer3D
	//
	// <Description>
	//      This class is an abstract class. It could/should be passed for rendering.
	//      
	//      The constructor is protected. Use @Init to create a 
	//      instance for the current API
	//      
	class ZAAP_API Renderer3D
	{
		//Static constructor
	public:
		// <Function>
		//      Init
		//
		// <Description>
		//      Creates a Renderer3D for the chosen API.
		//
		// <Return>
		//      The renderer for the chosen API or a nullptr in case of failure.
		//      
		Renderer3D* Init();

	protected:
		//Projection Matrix
		float m_FOV = 90.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		Mat4 m_ProjectionMatrix;

		//ViewFrustum
		ViewFrustum m_ViewFrustum; //TODO add a getter

		//Render target
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

		//////////////////
		// Shader stuff //
		//////////////////

		// <Function>
		//      loadTransformationMatrix
		//
		// <Description>
		//      This method loads the given TransformationMatrix into the 
		//      currently active shader (defined by @m_ActiveShaderType).
		// 
		//      In case that @m_ActiveShaderType points to a shader that does
		//      not support a TransformationMatrix it'll just return without
		//      any actions.
		//
		// <Input>
		//      A valid TransformationMatrix.
		//
		void loadTransformationMatrix(const Mat4& transformationMatrix) const;
		
		// <Function>
		//      loadLightSetup
		//
		// <Description>
		//      This methods loads the given @LightSetup into all valid shaders
		//      that support it.
		//
		// <Input>
		//      A valid LightSetup.
		//
		void loadLightSetup(const LightSetup& LightSetup);
		
		// <Function>
		//      loadScene
		//
		// <Description>
		//      This methods loads and saves some components from the @Scene class.
		//      Examples:
		//          - @Camera position
		//          - Current @ViewFrustum
		//
		// <Input>
		//      A Instance of the @Scene.
		//
		void loadScene(const Scene const* scene);

		// <Function>
		//      startShader
		//
		// <Description>
		//      Starts the shader specified by the input.
		//
		// <Input>
		//      @ZA_SHADER_TYPE the requested shader to start
		//
		void startShader(ZA_SHADER_TYPE shader);
		
		// <Function>
		//      getShader
		//
		// <Description>
		//      Returns the shader that is specified by the input.
		//      This does not create changes or starts any shaders by it self.0.
		//
		// <Input>
		//      @ZA_SHADER_TYPE the requested shader type
		//
		// <Returns>
		//      Returns the requested shader instance or a nullptr in case of failure.
		Shader* getShader(ZA_SHADER_TYPE shader);

		// <Function>
		//      setAlphaTestingState
		//
		// <Description> //TODO add desc
		virtual void setAlphaTestingState(bool enabled) = 0;
		//these two methods just access the "setAlphaTestingState(bool)" method
		inline void enableAlphaTesting();
		inline void disableAlphaTesting();
	};

}}
