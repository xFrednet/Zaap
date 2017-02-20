#pragma once

#include <Common.h>

#include <util/StringUtil.h>


#ifndef ZA_LOG_LEVEL
#	define ZA_LOG_LEVEL 0
#endif

#ifndef ZA_LOG_DEFAULT_FILE_NAME
#	define ZA_LOG_DEFAULT_FILE_NAME "log.txt"
#endif

#ifndef ZA_LOG_BUFFER_SIZE 
#	define ZA_LOG_BUFFER_SIZE (1024 * 8)
#endif

typedef ZAAP_API enum ZA_LOG_MESSAGE_TYPE_ {
	ZA_LOG_MESSAGE_INFO = 0,
	ZA_LOG_MESSAGE_CLEANUP = 1,
	ZA_LOG_MESSAGE_ALERT = 2,
	ZA_LOG_MESSAGE_ERROR = 3,
	ZA_LOG_MESSAGE_FATAL = 4,
} ZA_LOG_MESSAGE_TYPE;

/* //////////////////////////////////////////////////////////////////////////////// */
// // to_char_p //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace log {
	static char to_char_p_buffer_[ZA_LOG_BUFFER_SIZE + 1] = {'\0'}; // + 1 for the '\0'

	template<typename T>
	inline const char* to_char_p(const T& t)
	{
		String str = zaap::ToString<T>(t); 
		
		uint length = str.length();
		if (length > ZA_LOG_BUFFER_SIZE)
			length = ZA_LOG_BUFFER_SIZE;

		memcpy(to_char_p_buffer_, str.c_str(), length);
		to_char_p_buffer_[length] = '\0';

		return to_char_p_buffer_;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // char //
	/* //////////////////////////////////////////////////////////////////////////////// */
	template<>
	inline const char* to_char_p<char>(const char& t)
	{
		return &t;
	}
	template<>
	inline const char* to_char_p<unsigned char>(const unsigned char& t)
	{
		return (const char*)&t;
	}

	template<>
	inline const char* to_char_p<char*>(char* const& t)
	{
		return t;
	}
	template<>
	inline const char* to_char_p<unsigned char*>(unsigned char* const& t)
	{
		return (const char*)t;
	}

	template<>
	inline const char* to_char_p<char const*>(char const* const& t)
	{
		return t;
	}
	template<>
	inline const char* to_char_p<unsigned char const*>(unsigned char const* const& t)
	{
		return (const char*)t;
	}

	template<>
	inline const char* to_char_p<std::string>(std::string const& t)
	{
		return t.c_str();
	}
}}

namespace zaap { namespace log {
	
	/* //////////////////////////////////////////////////////////////////////////////// */
	// // File //
	/* //////////////////////////////////////////////////////////////////////////////// */
	static FILE* s_File = nullptr;
	static bool s_IsLogCloseFileSetAsAtExit = false;

	//TODO add descriptions
	
	ZAAP_API void LogOpenFile(String fileName);
	// <Function>
	//		LogCloseFile
	//
	// <Description>
	//		This closes the current file that is set as the log target.
	//
	// <Note>
	//	  - This also sets the log target file to null.
	//	  - This will do nothing if the current log target file is null.
	//	  - The file is saved automatically in the during shutdown.
	//
	ZAAP_API void LogCloseFile();

	// <Function>
	//		LogSetFile
	//
	// <Desciption>
	//		This sets the file that is targeted by the LogToFile
	//		function. The file that was used before is will be closed.
	//
	// <Note>
	//		A null pointer will do nothing the old file will remain 
	//		as the log target.
	//
	// <Input>
	//		file::
	//			A pointer to the FILE object of stdio.;;
	//
	ZAAP_API void LogSetFile(FILE* file);

	ZAAP_API FILE* LogGetFile();

	ZAAP_API bool LogHasFile();

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Functions //
	/* //////////////////////////////////////////////////////////////////////////////// */

	ZAAP_API String GetFileName(String str)
	{
		return str.substr(str.find_last_of("\\"), str.find_last_of("."));
	}

	// <Function>
	//		LogToBuffer
	//
	// <Description>
	//		This converts the "first" argument to a string using to_string and 
	//		adds them to the buffer.
	//
	// <Input>
	//		buffer::
	//			The buffer that is written to.;;
	//		bufferSize::
	//			The size of the maximum buffer.;;
	//		position::
	//			The current position in the buffer. The position
	//			will advance to the new buffer position;;
	//		first::
	//			The object that is converted to a string and
	//			added to the buffer;
	// 
	template<typename First>
	ZAAP_API void LogToBuffer(char* buffer, const uint& bufferSize, uint* position, First first)
	{
		const char* str = to_char_p<First>(first);
		uint length = strlen(str);
		if ((*position + length) >= bufferSize)
		{
			str = "[...]";
			length = 5;
			*position = bufferSize - 9; // (5) + ('\n') + ('\0') + (1 to convert from 0 to n) + ' '
		}

		memcpy(&buffer[*position], str, sizeof(char) * length);
		*position += length;
		buffer[*position++] = ' ';
	}

	// <Function>
	//		LogToBuffer
	//
	// <Description>
	//		This converts the arguments to a string using to_string and 
	//		adds them to the buffer.
	//
	// <Input>
	//		buffer::
	//			The buffer that is written to.;;
	//		bufferSize::
	//			The size of the maximum buffer.;;
	//		position::
	//			The current position in the buffer. The position
	//			will advance to the new buffer position;;
	//		first::
	//			The object that is converted to a string and
	//			added to the buffer;
	//		args::
	//			other arguments that are also added to the buffer by recalling this 
	//			function.;;
	// 
	template<typename First, typename... Args>
	ZAAP_API void LogToBuffer(char* buffer, const uint& bufferSize, uint* position, First&& first, Args&& ...args)
	{
		const char* str = to_char_p<First>(first);
		uint length = strlen(str);
		if ((*position + length) >= bufferSize)
		{
			str = "[...]";
			length = 5;
			*position = bufferSize - 8; // (5) + ('\n') + ('\0') + (1 to convert from 0 to n)
			memcpy(&buffer[*position], str, sizeof(char) * length);

			*position += length;
			return;
		}

		memcpy(&buffer[*position], str, sizeof(char) * length);
		*position += length;
		buffer[(*position)++] = ' ';

		LogToBuffer(buffer, ZA_LOG_BUFFER_SIZE, position, std::forward<Args>(args)...);
	}

	// <Function>
	//		PlatformLogConsole
	//
	// <Descritpion>
	//		This logs the message to the console.
	//
	// <Input>
	//		message::
	//			The message that should be logged.;;
	//		messageType::
	//			The message type.
	//			  - The types should change the color in the
	//				console.;;
	//
	ZAAP_API inline void PlatformLogConsole(const char* message, ZA_LOG_MESSAGE_TYPE messageType = ZA_LOG_MESSAGE_INFO);

	// <Function>
	//		LogToFile
	//
	// <Description>
	//		This logs the message to the current file.
	//
	// <Note>
	//	  - This function will do nothing if no file is set.
	//	  - messages with a value of ZA_CON_MESSAGE_ERROR or
	//		higher causes a new file to be created.
	//
	// <Input>
	//		message::
	//			The message that should be logged.;;
	//		messageType::
	//			The message type a new file will be created if 
	//			is value is ZA_CON_MESSAGE_ERROR or higher.;;
	//
	ZAAP_API inline void LogToFile(const char* message, ZA_LOG_MESSAGE_TYPE messageType = ZA_LOG_MESSAGE_INFO)
	{
		if (!LogHasFile())
		{
			// s_FileWrapper has no file
			if (messageType < ZA_LOG_MESSAGE_ERROR)
				return;

			LogOpenFile(ZA_LOG_DEFAULT_FILE_NAME);
			if (!LogHasFile())
			{
				PlatformLogConsole("zaap::log::LogToFile: couldn't create a log file. ", ZA_LOG_MESSAGE_ERROR);
				return;
			}
		}

		// s_FileWrapper has a file
		fprintf_s(LogGetFile(), "%s", message);
	}
	
	// <Function>
	//		LogCompleteMessage
	//
	// <Descritpion>
	//		This logs the complete message to the console and to a file
	//		if there is one set.
	//
	// <Note>
	//		This function will create a new file if there is non set and a 
	//		error is submitted.
	//
	// <Input>
	//		message::
	//			The message that should be logged.;;
	//		messageType::
	//			The message type.
	//			  - The types should change the color in the
	//				console.
	//			  - ZA_CON_MESSAGE_ERROR causes a new file to be
	//				created.;;
	//
	ZAAP_API inline void LogCompleteMessage(const char* message, ZA_LOG_MESSAGE_TYPE messageType = ZA_LOG_MESSAGE_INFO)
	{
		PlatformLogConsole(message, messageType);
		LogToFile(message, messageType);
	}

	// <Function>
	//		LogMessage
	//
	// <Descritpion>
	//		This logs the arguments to the console and to a file
	//		if there is one set.
	//
	// <Note>
	//		This function will create a new file if there is non set and a 
	//		error is submitted.
	//
	template<typename... Args>
	ZAAP_API inline void LogMessage(char* file, uint line, ZA_LOG_MESSAGE_TYPE messageType, Args... args)
	{
		//TODO add the file and the line
		//Values
		char buffer[ZA_LOG_BUFFER_SIZE];
		uint position = 0;

		//writing to buffer
		if (file)
			snprintf(buffer, ZA_LOG_BUFFER_SIZE, "ZAAP: %s[%i]: ", GetFileName(file).c_str(), line);
		
		LogToBuffer(buffer, ZA_LOG_BUFFER_SIZE, &position, std::forward<Args>(args)...);

		// adding the '\0'
		if (position + 2 >= ZA_LOG_BUFFER_SIZE)
			position = ZA_LOG_BUFFER_SIZE - 3;
		buffer[position++] = '\n';
		buffer[position] = '\0';

		//logging the actual message
		LogCompleteMessage(buffer, messageType);
	}

	ZAAP_API inline void LogCleanup(char* file)
	{
		LogMessage(nullptr, 0, ZA_LOG_MESSAGE_CLEANUP, "[INFO]  ZAAP: - ", GetFileName(file), "was cleaned up.");
	}
}}


#if (ZA_LOG_MESSAGE_INFO >= ZA_LOG_LEVEL)
#	define ZA_INFO(...) zaap::log::LogMessage(__FILE__, __LINE__, ZA_LOG_MESSAGE_INFO, __VA_ARGS__)
#else
#	define ZA_INFO(...)
#endif

#if (ZA_LOG_MESSAGE_CLEANUP >= ZA_LOG_LEVEL)
#	define ZA_LOG_CLEANUP() zaap::log::LogCleanup(__FILE__)
#else
#	define ZA_LOG_CLEANUP()
#endif

#if (ZA_LOG_MESSAGE_ALERT >= ZA_LOG_LEVEL)
#	define ZA_ALERT(...) zaap::log::LogMessage(__FILE__, __LINE__, ZA_LOG_MESSAGE_ALERT, __VA_ARGS__)
#else
#	define ZA_ALERT(...)
#endif

#if (ZA_LOG_MESSAGE_ERROR >= ZA_LOG_LEVEL)
#	define ZA_ERROR(...) zaap::log::LogMessage(__FILE__, __LINE__, ZA_LOG_MESSAGE_ERROR, __VA_ARGS__)
#else
#	define ZA_ERROR(...)
#endif

#if (ZA_LOG_MESSAGE_FATAL >= ZA_LOG_LEVEL)
#	define ZA_FATAL(...) zaap::log::LogMessage(__FILE__, __LINE__, ZA_LOG_MESSAGE_FATAL, __VA_ARGS__)
#	define ZA_FATAL_(...) zaap::log::LogMessage(nullptr, 0, ZA_LOG_MESSAGE_FATAL, __VA_ARGS__)
#else
#	define ZA_FATAL(...)
#	define ZA_FATAL_(...)
#endif

#ifndef ZA_ASSERT
#	define ZA_ASSERT(x, ...)                          \
		if (!(x)) {                                   \
			ZA_FATAL_("");                        \
			ZA_FATAL_("####################");    \
			ZA_FATAL_("# ZA_ASSERT FAILED #");    \
			ZA_FATAL_("####################");    \
			ZA_FATAL_("Assertion: ", (char*)#x);  \
			ZA_FATAL_("File: ",      __FILE__);   \
			ZA_FATAL_("Line: ",      __LINE__);   \
			ZA_FATAL_(__VA_ARGS__);               \
			__debugbreak();                           \
		}
#endif
