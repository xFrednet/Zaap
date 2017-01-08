#pragma once

#include <ZaapCLI.h>

#include <graphics\Renderer3D.h>
#include "Scene.h"
#include "shader\Shader.h"

namespace ZaapCLI
{
	public ref class Renderer3D : public ManagedClass<zaap::graphics::Renderer3D> 
	{
	public:
		////////////////////////////////////////////////////////////////////////////////
		// Constructor //
		////////////////////////////////////////////////////////////////////////////////

		// <Constructor>
		//      Renderer3D
		//
		// <Description>
		//      This creates a new Renderer3D for the current
		//      graphics API
		//
		Renderer3D();
		
		// <Constructor>
		//      Renderer3D
		//
		// <Description>
		//      This creates a new CLI class from the given
		//      pointer instance.
		//
		// <Note> 
		//      This is only used for ZaapCLI intern stuff.
		//      
		Renderer3D(zaap::graphics::Renderer3D* instance);

		////////////////////////////////////////////////////////////////////////////////
		// Shader stuff //
		////////////////////////////////////////////////////////////////////////////////

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
		void loadTransformationMatrix(Matrix4^ transformationMatrix);

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
		void loadLightSetup(LightSetup^ LightSetup);

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
		//      A valid instance of the @Scene please.
		//
		void loadScene(Scene^ scene);

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
		//      This does not create changes or starts any shaders by it self.
		//
		// <Input>
		//      shader : The @ZA_SHADER_TYPE of the requested shader.
		//
		// <Returns>
		//      Returns the requested shader instance or a nullptr in case of failure.
		//
		Shader^ getShader(ZA_SHADER_TYPE shader);

		////////////////////////////////////////////////////////////////////////////////
		// Frame related // 
		////////////////////////////////////////////////////////////////////////////////
	};

}