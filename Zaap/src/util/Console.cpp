#include "Console.h"

#include <windows.h>

#include "Common.h"

using namespace zaap;

void console::Println_(void* hr, String message, int messageType)
{
	//nullptr == false 
	if (!hr)
	{
		Println(message, messageType);
	}
}

void console::Println(String message, int messageType)
{
	switch (messageType)
	{
	case ZAAP_LOG_ERROR:
		SetColor(0x0C);
		std::cout << "[ERROR] ";
		break;
	case ZAAP_LOG_ALERT:
		SetColor(0x0E);
		std::cout << "[ALERT] ";
		break;
	case ZAAP_LOG_INFO:
		SetColor(0x08);
		std::cout << "[INFO]  ";
		break;
	case ZAAP_LOG_CLEANUP:
		SetColor(0x02);
		std::cout << "[INFO] ZAAP: - " << message << " - was cleaned up." << std::endl;
		return;
	}

	std::cout << "ZAAP: " << message << std::endl;
}

void console::PrintLastError(String message)
{
	SetColor(0x0C);
	std::cout << "[ERROR] ZAAP: " << message << std::endl;
	std::cout << "  | ZAAP: " << GetLastError << std::endl;
}

void console::SetColor(int color)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	SetConsoleTextAttribute(hstdout, color);

}
