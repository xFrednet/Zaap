#pragma once

#include <ZaapCLI.h>
#include <graphics\shader\Shader.h>

namespace ZaapCLI
{
	public enum ZA_SHADER_TYPE {
		ZA_SHADER_UNKNOWN			= zaap::graphics::ZA_SHADER_UNKNOWN,
		ZA_SHADER_TEXTURE_SHADER	= zaap::graphics::ZA_SHADER_TEXTURE_SHADER,
		ZA_SHADER_MATERIAL_SHADER	= zaap::graphics::ZA_SHADER_MATERIAL_SHADER,
		ZA_SHADER_TERRAIN_SHADER	= zaap::graphics::ZA_SHADER_TERRAIN_SHADER,
		ZA_SHADER_FONT_SHADER_2D	= zaap::graphics::ZA_SHADER_FONT_SHADER_2D
	};

	static zaap::graphics::ZA_SHADER_TYPE to_CPP_ZAShaderType(ZA_SHADER_TYPE shaderType)
	{
		return static_cast<zaap::graphics::ZA_SHADER_TYPE>(shaderType);
	}
	static ZA_SHADER_TYPE to_CLI_ZAShaderType(zaap::graphics::ZA_SHADER_TYPE shaderType)
	{
		return static_cast<ZA_SHADER_TYPE>(shaderType);
	}

	public ref class Shader : public ManagedClass<zaap::graphics::Shader> {
		////////////////////////////////////////////////////////////////////////////////
		// Constructor //
		////////////////////////////////////////////////////////////////////////////////
	public:
		// <Constructor>
		//      Shader
		//
		// <Description>
		//      This creates a new CLI class from the given
		//      pointer instance.
		//
		// <Note> 
		//      This is only used for ZaapCLI intern stuff.
		//      
		Shader(zaap::graphics::Shader* instance);

		// <Deconstructor>
		//      Shader
		//
		// <Description>
		//      This deconstructor calls the cleanup method from 
		//      the original shader class.
		//
		// <Note>
		//      Just ignore it.
		//
		~Shader();
		
		////////////////////////////////////////////////////////////////////////////////
		// Util //
		////////////////////////////////////////////////////////////////////////////////
		
		// <Function>
		//      start
		//
		// <Description>
		//      This method starts the shader instance.
		//      This method is overridden by the API shaders.
		//      
		void start();

		// <Function>
		//      stop
		//
		// <Description>
		//      This method stops the shader instance.
		//      This method is overridden by the API shaders.
		//      
		void stop();

		// <Function>
		//      getShaderType
		//
		// <Description>
		//      This returns the current shader type.
		//      
		ZA_SHADER_TYPE getShaderType();
	};

}
