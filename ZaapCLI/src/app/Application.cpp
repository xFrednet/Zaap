#include "Application.h"

//
// Application
//
namespace ZaapCLI {

	Application::Application(System::String^ title, uint width, uint height)
		: m_Instance(new SubApplication(to_CPP_String(title).c_str, width, height, this))
	{
	}

	void Application::start()
	{
		m_Instance->start();
	}
	void Application::stop()
	{
		m_Instance->stop();
	}

	void Application::pause()
	{
		m_Instance->pause();
	}
	void Application::resume()
	{
		m_Instance->resume();
	}

	void Application::render()
	{
		m_Instance->defaultRender();
	}
	void Application::update()
	{
		m_Instance->defaultUpdate();
	}

	void Application::cleanup()
	{
		m_Instance->cleanup();
	}

	void Application::pullEvents()
	{
		m_Instance->pullEvents();
	}

}
//
// SubApplication
//
namespace ZaapCLI {
	SubApplication::SubApplication(System::String^ title, uint width, uint height, void *cliApplication)
		: zaap::Application(to_CPP_String(title).c_str, width, height, nullptr),
		m_CLIApplication(cliApplication)
	{
	}

	void SubApplication::render()
	{
		((ZaapCLI::Application^)m_CLIApplication)->render();
	}
	void SubApplication::update()
	{
		((ZaapCLI::Application*)m_CLIApplication)->update();
	}

	void SubApplication::defaultRender()
	{
		zaap::Application::render();
	}
	void SubApplication::defaultUpdate()
	{
		zaap::Application::update();
	}
}