#include "Log.h"

/* //////////////////////////////////////////////////////////////////////////////// */
// // FileWrapper //
/* //////////////////////////////////////////////////////////////////////////////// */

namespace zaap { namespace log {

	void LogOpenFile(String fileName)
	{
		FILE* file;
		fopen_s(&file, fileName.c_str(), "w");
		LogSetFile(file);
	}
	void LogCloseFile()
	{
		if (s_File)
		{
			FILE* oldFile = s_File;
			s_File = nullptr; //to block the other functions from using the file
			fclose(oldFile);
		}
	}

	void LogSetFile(FILE* file)
	{
		if (!file)
			return;

		if (s_File)
			LogCloseFile();

		s_File = file;
		
		if (!s_IsLogCloseFileSetAsAtExit)
		{
			atexit(LogCloseFile);
			s_IsLogCloseFileSetAsAtExit = true;
		}
	}

	FILE* LogGetFile()
	{
		return s_File;
	}

	bool LogHasFile()
	{
		return (s_File) ? true : false;
	}
}}

#ifdef ZAAP_OS_WIN 
#include <windows.h>

// util function
void SetConsoleColor(int color)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	SetConsoleTextAttribute(hstdout, color);
}

void zaap::log::PlatformLogConsole(const char* message, ZA_LOG_MESSAGE_TYPE messageType)
{
	switch (messageType)
	{
	case ZA_LOG_MESSAGE_INFO:
		SetConsoleColor(0x08);
		break;
	case ZA_LOG_MESSAGE_CLEANUP:
		SetConsoleColor(0x02);
		break;
	case ZA_LOG_MESSAGE_ALERT:
		SetConsoleColor(0x0E);
		break;
	case ZA_LOG_MESSAGE_FATAL:
	case ZA_LOG_MESSAGE_ERROR:
		SetConsoleColor(0x0C);
		break;
	default:
		SetConsoleColor(0x08);
		break;
	}
	printf("%s", message);
}

#else // not ZAAP_OS_WIN
//TODO add other Platform log types;
void zaap::log::PlatformLogConsole(const char* message, ZA_CON_MESSAGE_TYPE messageType)
{
}
#endif // ZAAP_OS_WIN
