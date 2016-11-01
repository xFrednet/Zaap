#include "Window.h"

#include <util/Console.h>
#include <events/Input.h>
#include <graphics/API/Context.h>
#include <graphics/Renderer.h>

#include <windowsx.h>

//Event Method

namespace zaap {

	HWND Window::s_HWND;
	uint Window::s_Width = 0;
	uint Window::s_Height = 0;

	//
	// Creation
	//
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Window::Create(String title, int width, int height)
	{
		WNDCLASSEX wc;
		DWORD style = WS_OVERLAPPEDWINDOW;

		//sets all wc values to NULL
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		//properties
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpszClassName = "ZAAP_WINDOW";
		//Event Method
		wc.lpfnWndProc = WindowProc;

		//window size
		s_Width = width;
		s_Height = height;
		RECT size = { 0, 0, LONG(width), LONG(height) };
		AdjustWindowRect(&size, style, false);

		//register
		RegisterClassEx(&wc);

		s_HWND = CreateWindowEx(NULL,
			"ZAAP_WINDOW",
			title.c_str(),
			style,
			100,
			100,
			size.right - size.left,
			size.bottom - size.top,
			NULL, NULL, NULL, NULL);

		ShowWindow(s_HWND, SW_SHOWNORMAL);

		ZAAP_INFO("Window: Window was created");
	}

	//
	// Getters
	//
	HWND Window::GetHWND()
	{
		return s_HWND;
	}
	uint Window::GetWidth()
	{
		return s_Width;
	}
	uint Window::GetHeight()
	{
		return s_Height;
	}

	//
	// Events
	//
	void windowResized(uint width, uint height)
	{
		Window::s_Width = width;
		Window::s_Height = height;
		Input::WindowCallback(WindowResizeEvent(width, height));
	}
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			//
			// Focus
			//
		case WM_KILLFOCUS:
			Input::ClearButtons();
			Input::ClearKeys();
			break;

			//
			// Keyboard
			//
		case WM_KEYUP:
			Input::KeyEvent(wParam, false);
			break;
		case WM_KEYDOWN:
			Input::KeyEvent(wParam, true);
			break;
			//
			// Mouse
			//
		case WM_MOUSEMOVE:
			Input::MouseMotionEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

			//LButton
		case WM_LBUTTONDOWN:
			Input::MouseButtonEvent(ZAAP_MOUSE_LEFT, true);
			break;
		case WM_LBUTTONUP:
			Input::MouseButtonEvent(ZAAP_MOUSE_LEFT, false);
			break;

			//MButton
		case WM_MBUTTONDOWN:
			Input::MouseButtonEvent(ZAAP_MOUSE_MIDDLE, true);
			break;
		case WM_MBUTTONUP:
			Input::MouseButtonEvent(ZAAP_MOUSE_MIDDLE, false);
			break;

			//RButton
		case WM_RBUTTONDOWN:
			Input::MouseButtonEvent(ZAAP_MOUSE_RIGHT, true);
			break;
		case WM_RBUTTONUP:
			Input::MouseButtonEvent(ZAAP_MOUSE_RIGHT, false);
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