#pragma once

#include <ZaapCLI.h>

#include <app/Application.h>
#include "../graphics/Scene.h"

namespace ZaapCLI {

	ref class Application;

	class ApplicationRedirector : public zaap::Application
	{
	private:
		gcroot<ZaapCLI::Application^> m_Owner;
	public:
		ApplicationRedirector(ZaapCLI::Application^ owner, String title, uint width, uint height, zaap::graphics::Scene* scene);
	protected:
		void render() override;
		void update() override;

	public:
		void callDefaultRender();
		void callDefaultUpdate();
	};

	public ref class Application : ManagedClass<ApplicationRedirector>
	{
	protected:
	public:
		Application(System::String^ title, uint width, uint height, Scene^ scene);
		virtual ~Application() {}

		void start();
		void stop();

		void pause();
		void resume();

		virtual void render();
		virtual void update();

		void cleanup();
		/*
		This method pulls events from the window, like button presses and mouse interactions.
		This method is implemented in the default gameloop, it can be used if a different gameloop is used.
		*/
		void pullEvents();
	};
}
