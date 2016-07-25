#pragma once

#include <common.h>
#include <types.h>

#include <app/Window.h>
#include <graphics/Scene.h>

namespace zaap
{
	class ZAAP_API Application
	{
	private:
		bool m_Running = false;
		Window m_Window;

		int m_UPS = 60;
		int m_FPS = 60;

		bool m_Paused = false;

		void startGameloop();
	protected:
		graphics::Scene *m_Scene;

		virtual void render();
		virtual void update();
	public:
		Application(char* title, int width, int height, graphics::Scene *scene);
		~Application(void);

		void start();
		void stop();

		void pause();
		void resume();

		void cleanup() const;
		/*
		This method pulls events from the window, like butten presses and mouse interactions.
		This method is implemented in the default gameloop, it can be used if a nother gameloop is used.
		*/
		void pullEvents();
	};
}
