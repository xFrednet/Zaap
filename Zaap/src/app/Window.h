#pragma once

#include <common.h>
#include <types.h>

#include <windows.h>

namespace zaap
{

	class ZAAP_API Window
	{
	private:
		friend void windowResized(uint width, uint height);
		
		static HWND s_HWND;
		static uint s_Width;
		static uint s_Height;
	public:
		static void Create(String title, int width, int height);

		static HWND GetHWND();
		static uint GetWidth();
		static uint GetHeight();
	};
}