#pragma once

#include <ZaapCLI.h>

#include <app/Application.h>

namespace ZaapCLI {

	class SubApplication;

	public ref class Application
	{
	private:
		SubApplication *m_Instance;
	public:
		Application(System::String^ title, uint width, uint height);
		~Application()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}
		!Application()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}

		void start();
		void stop();

		void pause();
		void resume();

		virtual void render();
		virtual void update();

		void cleanup();
		
		//This method pulls events from the window, like butten presses and mouse interactions.
		//This method is implemented in the default gameloop, it can be used if a different gameloop is used.
		void pullEvents();
	};

	//
	class SubApplication : public zaap::Application {
	private:
		void *m_CLIApplication;

		void render() override;
		void update() override;
	public:
		SubApplication(System::String^ title, uint width, uint height, void* cliApplication);

		void defaultRender();
		void defaultUpdate();
	};
}
