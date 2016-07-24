#pragma once

#include "Common.h"
#include "Types.h"

#include <windows.h>
#include <windowsx.h>

namespace zaap
{
	struct ZAAP_API SIZE
		{
			uint Width;
			uint Height;

			SIZE(uint width, uint height)
			{
				Width = width;
				Height = height;
			}
			SIZE()
			{
				Width = 0; 
				Height = 0;
			}
		};

	class ZAAP_API Window
	{

	private:
		HWND hWnd_;
		SIZE resolution_;
	public:
		Window(char* title, int width, int height);

		HWND getHWND();
		SIZE* getSize();
	};
}