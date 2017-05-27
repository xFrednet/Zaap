#include "FileSystem.h"
#include "util/Log.h"

#ifdef ZA_OS_WINDOWS
#	include <windows.h>
#	include <Shlwapi.h>
#	include <sys/stat.h>  //works on Linux, UNIX and Windows
#endif

#define CHAR_BUFFER_SIZE 1024

using namespace std;

namespace zaap { namespace system {

	/* ********************************************************* */
	// * Directories *
	/* ********************************************************* */
	list<String> root_dir_list;
	char char_buffer[CHAR_BUFFER_SIZE];

	/* ##################################### */
	// # Root directories #
	/* ##################################### */
	void AddRootDir(String directory)
	{
		if (IsPathRelativ(directory))
		{
			//TODO do shit I don't know what
		}


		root_dir_list.push_back(directory);
	}
	void RemoveRootDir(String directory)
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

	/* ##################################### */
	// # Save directory #
	/* ##################################### */
	void SetWorkingDirectory(String directory)
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

	/* ##################################### */
	// # Directory util #
	/* ##################################### */
#ifdef ZA_OS_WINDOWS
	bool IsDirNameValid(String directory)
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
	bool IsPathRelativ(String directory)
	{
		return PathIsRelative(directory.c_str());
	}
	bool CreateDir(String directory)
	{
		//TODO maybe/surely add SECURITY_ATTRIBUTES attributes;
		if (IsDirNameValid(directory))
			return CreateDirectory(directory.c_str(), nullptr);

		return false;
	}
	bool DoesDirExists(String directory)
	{
		struct stat info;

		if (SUCCEEDED(stat(directory.c_str(), &info)))
			return (bool)(info.st_mode & S_IFDIR);

		return false;
	}
	bool DeleteDir(String directory)
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
	bool IsDirValid(String directory)
	{
		ZA_ASSERT("Why would you call a Function that isn't implemented... Oh right I have to implement...");
		return false;
	}
	bool CreateDir(String directory)
	{
		ZA_ASSERT("CreateDir isn't implemented for this OS yet");
		return false;
	}
	bool DoesDirExists(String directory)
	{
		ZA_ASSERT("DoesDirExists isn't implemented for this OS yet");
		return false;
	}
	bool DeleteDir(String directory)
	{
		ZA_ASSERT("DeleteDir isn't implemented for this OS yet");
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
	bool IsFileNameValid(String file)
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
	bool DoesFileExists(String file)
	{
		struct stat info;
		return stat(file.c_str(), &info) == 0;
	}
	String FindFile(String file)
	{
		//TODO find le File
	}
#else
	bool IsFileNameValid(String name)
	{
		ZA_ASSERT("IsFileNameValid isn't implemented for this OS yet");
		return false;
	}
	bool DoesFileExists(String file)
	{
		ZA_ASSERT("DoesFileExists isn't implemented for this OS yet");
		return false;
	}
	String FindFile(String file)
	{
		ZA_ASSERT("FindFile isn't implemented for this OS yet");
		return false;
	}
#endif
	ifstream OpenReadFile(String file)
	{
		
	}
	ofstream OpenWriteFile(String file)
	{
		
	}
	fstream OpenFile(String file)
	{
		return fstream(file.c_str(), ios_base::in | ios_base::out | ios_base::binary);
	}

}}
