#pragma once

#include <common.h>
#include <types.h>

#include <graphics/Scene.h>

namespace ZaapCLI {
	class Application;
}

namespace zaap
{


	class ZAAP_API Application
	{
	private:
		bool m_Running = false;

		int m_UPS = 60;
		int m_FPS = 60;

		bool m_Paused = false;

		void startGameloop();
	protected:
		graphics::Scene *m_Scene;

		virtual void render();
		virtual void update();

	public:
		Application(char* title, uint width, uint height, graphics::Scene *scene);
		virtual ~Application(){}

		void start();
		void stop();

		void pause();
		void resume();

		void cleanup() const;
		/*
		This method pulls events from the window, like butten presses and mouse interactions.
		This method is implemented in the default gameloop, it can be used if a different gameloop is used.
		*/
		void pullEvents();
	};
}
