#include "Application.h"

//
// ApplicationRedirector
//
namespace ZaapCLI {

	ApplicationRedirector::ApplicationRedirector(ZaapCLI::Application^ owner, String title, uint width, uint height)
		: zaap::Application(title, width, height, nullptr),
		m_Owner(owner)
	{
	}

	void ApplicationRedirector::start()
	{
		zaap::Application::start();
	}
	/*void ApplicationRedirector::render()
	{
		m_Owner->render();
	}
	void ApplicationRedirector::update()
	{
		m_Owner->update();
	}*/

	void ApplicationRedirector::callDefaultRender()
	{
		zaap::Application::render();
	}
	void ApplicationRedirector::callDefaultUpdate()
	{
		zaap::Application::update();
	}

}

//
// Application
//
namespace ZaapCLI {
	Application::Application(System::String^ title, uint width, uint height)
		: ManagedClass(new ApplicationRedirector(this, to_CPP_String(title), width, height))
	{
	}

	void Application::start()
	{
		if (m_Instance)
		{
			m_Instance->start();
		}
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
		//m_Instance->callDefaultRender();
	}
	void Application::update()
	{
		//m_Instance->callDefaultUpdate();
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
