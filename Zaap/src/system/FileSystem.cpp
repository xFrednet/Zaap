#include "FileSystem.h"
#include "util/Log.h"

#ifdef ZA_OS_WINDOWS
#	include <windows.h>
#	include <sys/stat.h>  //works on Linux, UNIX and Windows
#endif

#define CHAR_BUFFER_SIZE 1024

using namespace std;

namespace zaap { namespace system {

	/* ********************************************************* */
	// * Directories *
	/* ********************************************************* */
	list<String> root_dir_list;
	const String exe_file_directory_ = GetExeDirectory();
	const String first_working_directory_ = GetWorkingDirectory();
	char char_buffer[CHAR_BUFFER_SIZE];

	/* ##################################### */
	// # Root directories #
	/* ##################################### */
	bool AddRootDir(String directory)
	{
		if (directory.at(directory.length() - 1) == '\\')
			directory = directory.substr(0, directory.length() - 1);

		if (IsPathRelativ(directory))
		{
			if (directory.find_first_of('\\') != 0)
				directory = "\\" + directory;
			if (DoesDirExists(first_working_directory_ + directory))
				directory = first_working_directory_ + directory;
			else if (DoesDirExists(exe_file_directory_ + directory))
				directory = exe_file_directory_ + directory;
			else if (DoesDirExists(GetWorkingDirectory() + directory))
				directory = GetWorkingDirectory() + directory;
			else
				return false;
		}

		root_dir_list.push_back(directory);
		ZA_INFO("AddRootDir: new root directory: \"", directory.c_str(), "\"");

		return true;
	}
	void RemoveRootDir(const String& directory)
	{
		list<String>::iterator it;
		for (it = root_dir_list.begin(); it != root_dir_list.end(); it++) {
			if (*it == directory) {
				root_dir_list.erase(it);
				return;
			}
		}
	}
	list<String> GetRootDirs()
	{
		return root_dir_list;
	}
#ifdef ZA_OS_WINDOWS
	String GetExeDirectory()
	{
		DWORD bufferSize = GetModuleFileName(NULL, char_buffer, CHAR_BUFFER_SIZE);
		ZA_ASSERT(bufferSize);

		String result(char_buffer);

		if (bufferSize > CHAR_BUFFER_SIZE)
		{
			char* buffer = new char[bufferSize];
			ZA_ASSERT(buffer);
			GetModuleFileName(NULL, buffer, bufferSize);
			result = buffer;
			delete[] buffer;
		}

		return result.substr(0, result.find_last_of("\\"));
	}

	/* ##################################### */
	// # Save directory #
	/* ##################################### */
	void SetWorkingDirectory(const String& directory)
	{
		if (DoesDirExists(directory))
			SetCurrentDirectory(directory.c_str());
	}
	String GetWorkingDirectory()
	{
		DWORD bufferSize = GetCurrentDirectory(CHAR_BUFFER_SIZE, char_buffer);
		ZA_ASSERT(bufferSize);

		if (bufferSize < CHAR_BUFFER_SIZE)
			return String(char_buffer);

		char* buffer = new char[bufferSize];
		ZA_ASSERT(buffer);

		GetCurrentDirectory(bufferSize, buffer);
		String result(buffer);
		delete[] buffer;

		return result;
	}
#else
	String GetExeDirectory()
	{
		ZA_ASSERT(false, "GetExeDirectory isn't implemented for this OS yet");
		return "";
	}
	void SetWorkingDirectory(const String& directory)
	{
		ZA_ASSERT(false, "SetWorkingDirectory isn't implemented for this OS yet");
		return "";
	}
	String GetWorkingDirectory()
	{
		#ZA_ASSERT(false, "GetWorkingDirectory isn't implemented for this OS yet");
		return "";
	}
#endif

	/* ##################################### */
	// # Directory util #
	/* ##################################### */
#ifdef ZA_OS_WINDOWS
	bool IsDirNameValid(const String& directory)
	{
		return (directory.length() < MAX_PATH) &&
			(directory.find("<") == directory.npos) &&
			(directory.find(">") == directory.npos) &&
			(directory.find(":") == directory.npos) &&
			(directory.find("\"") == directory.npos) &&
			(directory.find("?") == directory.npos) &&
			(directory.find("*") == directory.npos) &&
			(directory.find("|") == directory.npos) &&
			(directory.find(".") == directory.npos);
	}
	bool IsPathRelativ(const String& directory)
	{
		return directory.find(':') == directory.npos;
	}
	bool CreateDir(const String& directory)
	{
		//TODO maybe/surely add SECURITY_ATTRIBUTES attributes;
		if (IsDirNameValid(directory))
			return CreateDirectory(directory.c_str(), nullptr);

		return false;
	}
	bool DoesDirExists(const String& directory)
	{
		struct stat info;
		
		if (SUCCEEDED(stat(directory.c_str(), &info)))
			return (bool)(info.st_mode & S_IFDIR);

		return false;
	}
	bool DeleteDir(const String& directory)
	{
		cout << directory.c_str() << endl;
		if (!DoesDirExists(directory))
			return true;
		cin.get();
		WIN32_FIND_DATA ffd;
		HANDLE file;
		String subDir = directory + "\\";

		if ((file = FindFirstFile((directory + "\\*").c_str(), &ffd)) != INVALID_HANDLE_VALUE) {
			do {
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					if (ffd.cFileName[0] == '.' &&
						(ffd.cFileName[1] == '\0' || // "."
						(ffd.cFileName[1] == '.' && ffd.cFileName[2] == '\0'))) // ".."
						continue;
					if (!DeleteDir((subDir + ffd.cFileName).c_str()))
						return false;
				}
				else {
					DeleteFile((subDir + ffd.cFileName).c_str());
				}
			} while (FindNextFile(file, &ffd) != 0);
			FindClose(file);
		}

		return RemoveDirectory(directory.c_str());
	}
#else
	bool IsDirValid(const String& directory)
	{
		ZA_ASSERT(false, "Why would you call a Function that isn't implemented... Oh right I have to implement...");
		return false;
	}
	bool CreateDir(const String& directory)
	{
		ZA_ASSERT(false, "CreateDir isn't implemented for this OS yet");
		return false;
	}
	bool DoesDirExists(const String& directory)
	{
		ZA_ASSERT(false, "DoesDirExists isn't implemented for this OS yet");
		return false;
	}
	bool DeleteDir(const String& directory)
	{
		ZA_ASSERT(false, "DeleteDir isn't implemented for this OS yet");
		return false;
	}
#endif

	/* ********************************************************* */
	// * File stuff *
	/* ********************************************************* */

	/* ##################################### */
	// # File util #
	/* ##################################### */
#ifdef ZA_OS_WINDOWS
	bool IsFileNameValid(const String& file)
	{
		return (file.length() < MAX_PATH) &&
			(file.find("<") == file.npos) &&
			(file.find(">") == file.npos) &&
			(file.find(":") == file.npos) &&
			(file.find("\"") == file.npos) &&
			(file.find("?") == file.npos) &&
			(file.find("*") == file.npos) &&
			(file.find("|") == file.npos) &&
			(file.find("/") == file.npos) &&
			(file.find("\\") == file.npos);
	}
	bool DoesFileExists(const String& file)
	{
		struct stat info;
		return stat(file.c_str(), &info) == 0;
	}
	String GetFilePath(String file)
	{
		if (!IsPathRelativ(file))
			return file;
		if (file.find_first_of('\\'))
			file = "\\" + file;

		String location;
		if (DoesFileExists(location = GetWorkingDirectory() + file))
			return location;
		if (DoesFileExists(location = first_working_directory_ + file))
			return location;
		if (DoesFileExists(exe_file_directory_ + file))
			return exe_file_directory_ + file;
		for (const String& root : root_dir_list)
		{
			if (DoesFileExists(root + file))
				return root + file;
		}
		return "";
	}

	uint64 GetFileSize(const String& file)
	{
		struct stat info;

		if (SUCCEEDED(stat(GetFilePath(file).c_str(), &info)))
			return (uint64)info.st_size;

		return 0;
	}
#else
	bool IsFileNameValid(const String& name)
	{
		ZA_ASSERT(false, "IsFileNameValid isn't implemented for this OS yet");
		return false;
	}
	bool DoesFileExists(const String& file)
	{
		ZA_ASSERT(false, "DoesFileExists isn't implemented for this OS yet");
		return false;
	}
	String GetFilePath(String file)
	{
		ZA_ASSERT(false, "GetFilePath isn't implemented for this OS yet");
		return false;
	}
	uint GetFileSize(const String& file)
	{
		ZA_ASSERT(false, "GetFileSize isn't implemented for this OS yet");
		return 0;
	}
#endif

	/* ##################################### */
	// # File content #
	/* ##################################### */
	ifstream OpenFileInStream(const String& file)
	{
		return ifstream(GetFilePath(file), ios_base::in | ios_base::binary);
	}
	ofstream OpenFileOutStream(const String& file)
	{
		return ofstream(GetFilePath(file), ios_base::out | ios_base::binary);
	}
	fstream OpenFile(const String& file)
	{
		return fstream(GetFilePath(file), ios_base::in | ios_base::out | ios_base::binary);
	}

	za_ptr<byte> LoadFileContent(String file, uint32* bufferSize)
	{
		//error check
		ZA_ASSERT(bufferSize, "LoadFileContent: ", file);
		if (!bufferSize || (file = GetFilePath(file)).length() == 0) {
			*bufferSize = 0;
			return nullptr;
		}

		//Buffer and file size
		*bufferSize = (uint32)GetFileSize(file);

		byte* buffer = new byte[*bufferSize + 1];
		buffer[*bufferSize] = 0;

		//reading Data
		ifstream stream = ifstream(file, ios_base::in | ios_base::binary);
		if (stream.is_open())
		{
			stream.read((char*)buffer, *bufferSize);
			stream.close();
			return za_ptr<byte>(buffer);
		}
		delete[] buffer;
		return nullptr;
	}
}}
