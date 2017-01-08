#include "Application.h"

//
// ApplicationRedirector
//
namespace ZaapCLI {

	ApplicationRedirector::ApplicationRedirector(ZaapCLI::Application^ owner, String title, uint width, uint height, zaap::graphics::Scene* scene)
		: zaap::Application(title, width, height, scene),
		m_Owner(owner)
	{
	}

	void ApplicationRedirector::render()
	{
		m_Owner->render();
	}
	void ApplicationRedirector::update()
	{
		m_Owner->update();
	}

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
	Application::Application(System::String^ title, uint width, uint height, Scene^ scene)
		: ManagedClass(new ApplicationRedirector(this, to_CPP_String(title), width, height, scene->getHandle()))
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
		m_Instance->callDefaultRender();
	}
	void Application::update()
	{
		m_Instance->callDefaultUpdate();
	}
	
	void Application::pullEvents()
	{
		m_Instance->pullEvents();
	}
}
