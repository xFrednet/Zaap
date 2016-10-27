#pragma once

#include <ZaapCLI.h>

#include <app/Window.h>

namespace ZaapCLI {
	
	public ref class Window 
	{
	public:
		static void Create(char* title, uint width, uint height);

		static uint GetWidth();
		static uint GetHeight();
	};
}
