#include "ImageLoader.h"

#include <util/Console.h>

#include <FreeImage.h>
#include <FreeImage/Utilities.h>

namespace zaap
{
	bool ImageLoader::isFreeImageInit = false;

	void ImageLoader::Cleanup()
	{
		if (!isFreeImageInit)
		{
			ZAAP_ALERT("ImageLoader: FreeImage isn't Initialised");
			return;
		}
		FreeImage_DeInitialise();
		isFreeImageInit = false;
		ZAAP_CLEANUP_LOG("ImageLoader");
	}

	void ImageLoader::Init()
	{
		if (isFreeImageInit)
		{
			ZAAP_ALERT("ImageLoader: FreeImage is already Initialised");
			return;
		}
		FreeImage_Initialise();
		isFreeImageInit = true;
	}

	byte* ImageLoader::Load(const char *filePath, uint *width, uint *height, uint *bits, bool flipY)
	{
		if (!isFreeImageInit)
		{
			Init();
		}

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *bitmap(0);
		byte *data = nullptr;

		//format
		fif = FreeImage_GetFileType(filePath, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filePath);
		if (fif == FIF_UNKNOWN)
		{
			ZAAP_ERROR("LoadImage: could not load image format for " + String(filePath));
			return nullptr;
		}

		//Loading Bitmap
		if (FreeImage_FIFSupportsReading(fif))
			bitmap = FreeImage_Load(fif, filePath);
		if (!bitmap)
		{
			ZAAP_ERROR("LoadImage: could not load bitmap for " + String(filePath));
			return nullptr;
		}

		//bitmap options
		FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_Unload(bitmap);
		if (flipY)
			FreeImage_FlipVertical(bitmap32);
		if (!(FreeImage_GetRedMask(bitmap32) == 0xff0000))
			SwapRedBlue32(bitmap32);
		

		data = FreeImage_GetBits(bitmap32);
		*width = FreeImage_GetWidth(bitmap32);
		*height = FreeImage_GetHeight(bitmap32);
		*bits = FreeImage_GetBPP(bitmap32);

		int32 size = *width * *height * (*bits / 8);
		byte* result = new byte[size];
		memcpy(result, data, size);
		FreeImage_Unload(bitmap32);
		return result;
	}

	byte* ImageLoader::Load(String &filePath, uint* width, uint* height, uint* bits, bool flipY)
	{
		return Load(filePath.c_str(), width, height, bits, flipY);
	}

}
