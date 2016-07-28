#include "util/ImageLoader.h"

#include "Application.h"

#include "util/Console.h"
#include "util/StringUtil.h"

#include "graphics/Renderer.h"
#include "graphics/API/Context.h"
#include "graphics/camera/ControllableCamera.h"
#include "graphics/TextureManager.h"

#include "events/Input.h"

#include <time.h>

namespace zaap {

	graphics::Camera* camera;

	Application::Application(char* title, int width, int height, graphics::Scene *scene)
		: m_Window(title, width, height),
		m_Scene(scene)
	{
		graphics::API::Context::Create(m_Window);
		graphics::Renderer::Init();

		camera = new graphics::ControllableCamera(math::Vec3(0.4f, 2.8f, 9.3f));
		graphics::Renderer::SetCamera(camera);
	}
	void Application::cleanup() const
	{
		ImageLoader::Cleanup();
		graphics::TextureManager::Cleanup();
		delete camera;
		delete m_Scene;
		graphics::Renderer::Cleanup();
		graphics::API::Context::Cleanup();

		ZAAP_CLEANUP_LOG("Application");
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
				if (events::Input::IsKeyPressed(ZAAP_VK_P))
				{
					ZAAP_ALERT("Application: PAUSE");
					m_Paused = !m_Paused;
				}

				if (!m_Paused)update();
				events::Input::Update();
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
				console::Println("Application: UPS: " + std::to_string(int(updates)) + ", FPS: " + std::to_string(int(frames)));

				if ((clock() - timer) >= 20000)
				{
					ZAAP_ALERT(String("Application: The Gameloop can't keep up: skipped ") + std::to_string(clock() - timer / 1000 * m_UPS) + " Updates.");
					timer = clock();
				}

				frames = 0;
				updates = 0;
			}
		}
	}

	void Application::render()
	{
		graphics::Renderer::Prepare();

		m_Scene->render();
	}
	void Application::update()
	{

		camera->update();

		/*std::cout << events::Input::IsButtonPressed(0) << " " <<
			events::Input::IsButtonPressed(1) << " " <<
			events::Input::IsButtonPressed(2) << std::endl;*/

		//std::cout << events::Input::GetMouseMotion().toString() << std::endl;;

		//model.addToRotation(math::Vec3(0.0f, 0.5f, 0.0f));
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
