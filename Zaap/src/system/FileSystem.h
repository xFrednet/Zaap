#pragma once

#include <Common.h>

namespace zaap { namespace system {

	/* ********************************************************* */
	// * Directories *
	/* ********************************************************* */

	/* ##################################### */
	// # Root directories #
	/* ##################################### */
	ZAAP_API bool AddRootDir(String directory);
	ZAAP_API void RemoveRootDir(String directory);
	ZAAP_API std::list<String> GetRootDirs();

	/* ##################################### */
	// # Save directory #
	/* ##################################### */
	ZAAP_API void SetWorkingDirectory(String directory);
	ZAAP_API String GetWorkingDirectory();
	ZAAP_API String GetExeDirectory();

	/* ##################################### */
	// # Directory util #
	/* ##################################### */
	ZAAP_API inline bool IsDirNameValid(String directory);
	ZAAP_API inline bool IsPathRelativ(String directory);
	ZAAP_API inline bool CreateDir(String directory);
	ZAAP_API inline bool DoesDirExists(String directory);
	ZAAP_API bool DeleteDir(String directory);

	/* ********************************************************* */
	// * File stuff *
	/* ********************************************************* */

	/* ##################################### */
	// # File util #
	/* ##################################### */
	ZAAP_API inline bool IsFileNameValid(String name);
	ZAAP_API inline bool DoesFileExists(String file);
	ZAAP_API inline String FindFile(String file);
	
	ZAAP_API std::ifstream OpenReadFile(String file);
	ZAAP_API std::ofstream OpenWriteFile(String file);
	ZAAP_API std::fstream OpenFile(String file);

}}
