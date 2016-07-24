#include "Window.h"

#include "util/Console.h"
#include <events/Input.h>
#include <graphics/API/Context.h>
#include <graphics/Renderer.h>

//Event Method

namespace zaap {
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Window::Window(char* title, int width, int height)
	{

		resolution_ = SIZE(width, height);
		WNDCLASSEX wc;
		DWORD style = WS_OVERLAPPEDWINDOW;

		//setes als wc values to NULL
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		//properties
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpszClassName = "ZAAP_WINDOW";
		//Event Method
		wc.lpfnWndProc = WindowProc;

		//window size
		RECT size = { 0, 0, LONG(width), LONG(height) };
		AdjustWindowRect(&size, style, false);

		//register
		RegisterClassEx(&wc);

		hWnd_ = CreateWindowEx(NULL,
			"ZAAP_WINDOW",
			title,
			style,
			100,
			100,
			size.right - size.left,
			size.bottom - size.top,
			NULL, NULL, NULL, NULL);

		ShowWindow(hWnd_, SW_SHOWNORMAL);

		ZAAP_INFO("Window: Window was created");
	}

	HWND Window::getHWND()
	{
		return hWnd_;
	}
	zaap::SIZE* Window::getSize()
	{
		return &resolution_;
	}

	void windowResized(uint width, uint height)
	{
		graphics::API::Context::Resize(width, height);
		graphics::Renderer::Resize(width, height);
	}

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		//std::cout << wParam << " " << lParam << std::endl;
		switch (message)
		{
			//
			// Focus
			//
		case WM_KILLFOCUS:
			events::Input::ClearButtons();
			events::Input::ClearKeys();
			break;

			//
			// Keyboard
			//
		case WM_KEYUP:
			events::Input::KeyEvent(wParam, false);
			break;
		case WM_KEYDOWN:
			events::Input::KeyEvent(wParam, true);
			break;
			//
			// Mouse
			//
		case WM_MOUSEMOVE:
			events::Input::MouseMotionEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

			//LButton
		case WM_LBUTTONDOWN:
			events::Input::MouseButtonEvent(ZAAP_MOUSE_LEFT, true);
			break;
		case WM_LBUTTONUP:
			events::Input::MouseButtonEvent(ZAAP_MOUSE_LEFT, false);
			break;

			//MButton
		case WM_MBUTTONDOWN:
			events::Input::MouseButtonEvent(ZAAP_MOUSE_MIDDLE, true);
			break;
		case WM_MBUTTONUP:
			events::Input::MouseButtonEvent(ZAAP_MOUSE_MIDDLE, false);
			break;

			//RButton
		case WM_RBUTTONDOWN:
			events::Input::MouseButtonEvent(ZAAP_MOUSE_RIGHT, true);
			break;
		case WM_RBUTTONUP:
			events::Input::MouseButtonEvent(ZAAP_MOUSE_RIGHT, false);
			break;

			//
			// Resize
			//
		case WM_SIZE:
			windowResized(LOWORD(lParam), HIWORD(lParam));
			break;

			//
			// Else
			//
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}