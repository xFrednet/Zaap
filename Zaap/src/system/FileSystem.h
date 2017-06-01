#pragma once

#include <Common.h>

#ifndef ZA_LOADFILE_MAXSIZE
#	define	ZA_LOADFILE_MAXSIZE 1024
#endif

namespace zaap { namespace system {

	/* ********************************************************* */
	// * Directories *
	/* ********************************************************* */

	/* ##################################### */
	// # Root directories #
	/* ##################################### */
	ZAAP_API bool AddRootDir(String directory);
	ZAAP_API void RemoveRootDir(const String& directory);
	ZAAP_API std::list<String> GetRootDirs();

	/* ##################################### */
	// # Save directory #
	/* ##################################### */
	ZAAP_API void SetWorkingDirectory(const String& directory);
	ZAAP_API String GetWorkingDirectory();
	ZAAP_API String GetExeDirectory();

	/* ##################################### */
	// # Directory util #
	/* ##################################### */
	ZAAP_API inline bool IsDirNameValid(const String& directory);
	ZAAP_API inline bool IsPathRelativ(const String& directory);
	ZAAP_API inline bool CreateDir(const String& directory);
	ZAAP_API inline bool DoesDirExists(const String& directory);
	ZAAP_API bool DeleteDir(const String& directory);

	/* ********************************************************* */
	// * File stuff *
	/* ********************************************************* */

	/* ##################################### */
	// # File util #
	/* ##################################### */
	ZAAP_API inline bool IsFileNameValid(const String& name);
	ZAAP_API inline bool DoesFileExists(const String& file);
	ZAAP_API inline String GetFilePath(String fileName);
	
	ZAAP_API inline uint64 GetFileSize(const String& file);

	/* ##################################### */
	// # File content #
	/* ##################################### */
	ZAAP_API std::ifstream OpenFileInStream(const String& file);
	ZAAP_API std::ofstream OpenFileOutStream(const String& file);
	ZAAP_API std::fstream  OpenFile(const String& file);
	
	/**
	 * \brief 
	 * \param file The name of the file that should be loaded.
	 * \param bufferSize The size of the returned buffer(without the terminating 0).
	 * \return The loaded data with a added 0.
	 */
	ZAAP_API za_ptr<byte> LoadFileContent(String file, uint32* bufferSize);
}}
