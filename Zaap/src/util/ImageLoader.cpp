#include "ImageLoader.h"

#include <util/Log.h>

#include <FreeImage.h>
#include <FreeImage/Utilities.h>
#include "system/FileSystem.h"

#pragma comment (lib, "FreeImage.lib")

namespace zaap
{
	bool ImageLoader::isFreeImageInit = false;

	void ImageLoader::Cleanup()
	{
		if (!isFreeImageInit)
			return;
		
		FreeImage_DeInitialise();
		isFreeImageInit = false;
		ZA_LOG_CLEANUP();
	}

	void ImageLoader::Init()
	{
		if (isFreeImageInit)
			return;
		
		FreeImage_Initialise();
		isFreeImageInit = true;
	}

	ZA_RESULT ImageLoader::Load(const char *filePath, uint *width, uint *height, uint *bits, byte** bytes, bool flipY)
	{
		if (!isFreeImageInit)
		{
			Init();
		}

		String filePathString = system::GetFilePath(filePath);
		filePath = filePathString.c_str();
		*width = 0;
		*height = 0;
		*bits = 0;

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *bitmap(0);
		byte *data = nullptr;

		//format
		fif = FreeImage_GetFileType(filePath, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filePath);
		if (fif == FIF_UNKNOWN)
			return ZA_ERROR_FILE_TYPE_UNKNOWN;
		

		//Loading Bitmap
		if (FreeImage_FIFSupportsReading(fif))
			bitmap = FreeImage_Load(fif, filePath);
		if (!bitmap)
			return ZA_ERROR_FILE_FAILED_TO_LOAD_CONTENT;
		

		//bitmap options
		FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_Unload(bitmap);
		if (flipY)
			FreeImage_FlipVertical(bitmap32);
		if (FreeImage_GetRedMask(bitmap32) == 0xff0000)
			SwapRedBlue32(bitmap32);

		data = FreeImage_GetBits(bitmap32);
		*width = FreeImage_GetWidth(bitmap32);
		*height = FreeImage_GetHeight(bitmap32);
		*bits = FreeImage_GetBPP(bitmap32);

		int32 size = *width * *height * (*bits / 8);
		*bytes = new byte[size];
		memcpy(*bytes, data, size);
		FreeImage_Unload(bitmap32);

		return ZA_RESULT_SUCCESS;
	}

	ZA_RESULT ImageLoader::Load(String &filePath, uint* width, uint* height, uint* bits, byte** bytes, bool flipY)
	{
		return Load(filePath.c_str(), width, height, bits, bytes, flipY);
	}

}
