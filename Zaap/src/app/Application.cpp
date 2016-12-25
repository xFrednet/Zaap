#include "Application.h"

#include <util/ImageLoader.h>

#include <util/Console.h>
#include <util/StringUtil.h>

#include <graphics/API/Context.h>
#include <graphics/TextureManager.h>
#include <graphics/MaterialManager.h>
#include <graphics/mesh/MeshManager.h>

#include <events/Input.h>

#include <time.h>
#include "Window.h"

namespace zaap {

	Application::Application(String title, uint width, uint height, graphics::Scene *scene)
		: m_Scene(scene)
	{
		Window::Create(title, width, height);
		graphics::API::Context::Create();
	}
	void Application::cleanup() const
	{
		ImageLoader::Cleanup();
		graphics::MeshManager::Cleanup();
		graphics::MaterialManager::Cleanup();
		//TODO add auto (problem with CLI) delete m_Scene;
		graphics::API::Context::Cleanup();
		graphics::API::Texture::Cleanup();
		graphics::API::VertexBuffer::Cleanup();

		ZAAP_CLEANUP_INFO();
	}

	void Application::start()
	{
		m_Running = true;

		startGameloop();
	}
	void Application::stop()
	{
		m_Running = false;
	}

	void Application::pause()
	{
		m_Running = false;
	}
	void Application::resume()
	{
		m_Running = true;

		startGameloop();
	}

	void Application::startGameloop()
	{
		//clock() returns the time in ms since the app start
		long difference;
		clock_t lastTime = clock();
		clock_t timer = clock();

		float millis_update = 1000.0f / m_UPS;
		float update_prog = 0.0f;

		int updates = 0;
		int frames = 0;

		while (m_Running)
		{
			difference = clock() - lastTime;
			update_prog += difference / millis_update;
			lastTime += difference;

			//pulling Events
			pullEvents();
			
			//update stuff
			if (update_prog >= 1.0f)
			{
				if (Input::IsKeyPressed(ZA_VK_P))
				{
					ZAAP_ALERT("PAUSE");
					m_Paused = !m_Paused;
				}

				if (!m_Paused)update();
				Input::Update();
				update_prog--;
				updates++;
				
				//render stuff
				if (!m_Paused)render();
				frames++;
			}

			if ((clock() - timer) >= 1000)
			{
				timer += 1000;
				
				if (!m_Paused)
				ZAAP_INFO(String("UPS: " + std::to_string(int(updates)) + ", FPS: " + std::to_string(int(frames))));

				if ((clock() - timer) >= 20000)
				{
					ZAAP_ALERT(String("The Gameloop can't keep up: skipped ") + std::to_string(clock() - timer / 1000 * m_UPS) + " Updates.");
					timer = clock();
				}

				frames = 0;
				updates = 0;
			}
		}
	}

	void Application::render()
	{
		if (m_Scene) 
			m_Scene->render();
	}
	void Application::update()
	{
		if (m_Scene) 
			m_Scene->update();
	}

	MSG msg_;
	void Application::pullEvents()
	{
		
		if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg_);
			DispatchMessage(&msg_);

			if (msg_.message == WM_QUIT)
				stop();
		}
	}
}
