#include "Console.h"

#include <Common.h>

#include <windows.h>

namespace zaap { namespace console {

	void PrintCleanup(String fileName)
	{
		uint nameStart = fileName.find_last_of("\\") + 1; //+1 so that the '\' is not included
		fileName = fileName.substr(nameStart, fileName.find_last_of(".") - nameStart);

		SetColor(0x02);
		std::cout << "[INFO]  ZAAP: - " << fileName << " - was cleaned up." << std::endl;
	}

	void Println(String fileName, int line, ZA_LOG_MESSAGE_TYPE type, String message)
	{
		//File info string
		uint nameStart = fileName.find_last_of("\\") + 1; //+1 so that the '\' is not included
		String infoString = fileName.substr(nameStart, fileName.find_last_of(".") - nameStart);
		infoString += "[" + std::to_string(line) + "]";
		for (uint i = infoString.size(); i < 20; i++)
		{
			infoString.append(" ");
		}

		switch (type)
		{
		case ZA_LOG_MESSAGE_ERROR:
			SetColor(0x0C);
			std::cout << "[ERROR] ";
			break;
		case ZA_LOG_MESSAGE_ALERT:
			SetColor(0x0E);
			std::cout << "[ALERT] ";
			break;
		case ZA_LOG_MESSAGE_INFO:
		default:
			SetColor(0x08);
			std::cout << "[INFO]  ";
			break;
		}

		printf("ZAAP: %s: %s \n", infoString.c_str(), message.c_str());
		
	}

	void PrintLastError(String message)
	{
		SetColor(0x0C);
		std::cout << "[ERROR] ZAAP: " << message << std::endl;
		std::cout << "  | ZAAP: " << GetLastError << std::endl;
	}

	void SetColor(int color)
	{
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		SetConsoleTextAttribute(hstdout, color);

	}
	
}}

