#include "Shader.h"

namespace ZaapCLI
{
	////////////////////////////////////////////////////////////////////////////////
	// Constructor //
	////////////////////////////////////////////////////////////////////////////////
	Shader::Shader(zaap::graphics::Shader* instance)
		: ManagedClass(instance)
	{
		
	}

	Shader::~Shader()
	{
		m_Instance->cleanup();
	}

	////////////////////////////////////////////////////////////////////////////////
	// Util //
	////////////////////////////////////////////////////////////////////////////////

	void Shader::start()
	{
		m_Instance->start();
	}

	void Shader::stop()
	{
		m_Instance->stop();
	}

	ZA_SHADER_TYPE Shader::getShaderType()
	{
		return to_CLI_ZAShaderType(m_Instance->getShaderType());
	}
}
