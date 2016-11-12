#include "Console.h"

#include <Common.h>

#include <windows.h>

namespace zaap { namespace console {

	void Println(String message, ZA_CON_MESSAGE_TYPE messageType)
	{
		switch (messageType)
		{
		case ZA_CON_MESSAGE_ERROR:
			SetColor(0x0C);
			std::cout << "[ERROR] ";
			break;
		case ZA_CON_MESSAGE_ALERT:
			SetColor(0x0E);
			std::cout << "[ALERT] ";
			break;
		case ZA_CON_MESSAGE_INFO:
			SetColor(0x08);
			std::cout << "[INFO]  ";
			break;
		case ZA_CON_MESSAGE_CLEANUP:
			SetColor(0x02);
			std::cout << "[INFO]  ZAAP: - " << message << " - was cleaned up." << std::endl;
			return;
		}

		std::cout << "ZAAP: " << message << std::endl;
	}

	void Println(String fileName, int line, ZA_CON_MESSAGE_TYPE type, String message)
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
		case ZA_CON_MESSAGE_ERROR:
			SetColor(0x0C);
			std::cout << "[ERROR] ";
			break;
		case ZA_CON_MESSAGE_ALERT:
			SetColor(0x0E);
			std::cout << "[ALERT] ";
			break;
		case ZA_CON_MESSAGE_INFO:
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

