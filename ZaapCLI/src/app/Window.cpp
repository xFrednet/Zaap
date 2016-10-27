#include "Window.h"

namespace ZaapCLI
{
	void Window::Create(char* title, uint width, uint height)
	{
		zaap::Window::Create(title, (int)width, (int)height);
	}

	uint Window::GetWidth()
	{
		return zaap::Window::GetWidth();
	}
	uint Window::GetHeight()
	{
		return zaap::Window::GetHeight();
	}
}