#include "ZAError.h"

#include <util/Log.h>
#include "maths/Maths.h"

#define _and_ &
#define _or_  |
#define _xor_ ^

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_MULTI_RESULT //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap {
	ZA_MULTI_RESULT_::ZA_MULTI_RESULT_()
	{
		for (uint i = 0; i < ZA_MULTI_RESULT_SIZE; i++)
			Results[i] = ZA_OK;
	}

	ZA_MULTI_RESULT_::ZA_MULTI_RESULT_(ZA_RESULT result)
	{
		for (uint i = 0; i < ZA_MULTI_RESULT_SIZE; i++)
			Results[i] = ZA_OK;

		*this += result;
	}

	uint ZA_MULTI_RESULT_::size() const
	{
		for (uint i = ZA_MULTI_RESULT_SIZE - 1; i >= 0; i--)
		{
			if (Results[i] != ZA_OK)
				return i + 1;

			if (i == 0)
				return 0;
		}

		return 0;
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Operators // 
	/* //////////////////////////////////////////////////////////////////////////////// */

	ZA_RESULT& ZA_MULTI_RESULT_::operator[](int index)
	{
		if (index >= 0 || index < ZA_MULTI_RESULT_SIZE)
			return Results[index];

		if (index < 0)
			return Results[0];
		else
			return Results[ZA_MULTI_RESULT_SIZE - 1];
	}
	const ZA_RESULT& ZA_MULTI_RESULT_::operator[](const int index) const
	{
		if (index >= 0 || index < ZA_MULTI_RESULT_SIZE)
			return Results[index];

		if (index < 0)
			return Results[0];
		else
			return Results[ZA_MULTI_RESULT_SIZE - 1];
	}

	ZA_MULTI_RESULT_& ZA_MULTI_RESULT_::operator+=(const ZA_RESULT& other)
	{
		*this = zaap::AddZAResult(*this, other);
		return *this;
	}
	ZA_MULTI_RESULT_& ZA_MULTI_RESULT_::operator+=(const ZA_MULTI_RESULT_& other)
	{
		*this = zaap::CombineZAResults(*this, other);
		return *this;
	}

	ZA_MULTI_RESULT_ ZA_MULTI_RESULT_::operator+(const ZA_RESULT& other) const
	{
		return zaap::AddZAResult(*this, other);
	}
	ZA_MULTI_RESULT_ ZA_MULTI_RESULT_::operator+(const ZA_MULTI_RESULT_& other) const
	{
		return zaap::CombineZAResults(*this, other);
	}

	bool ZA_MULTI_RESULT_::operator==(const ZA_RESULT& other) const
	{
		return (this->Results[0] == other);
	}
	bool ZA_MULTI_RESULT_::operator!=(const ZA_RESULT& other) const
	{
		return (this->Results[0] != other);
	}
	bool ZA_MULTI_RESULT_::operator<(const ZA_RESULT& other) const
	{
		return (this->Results[0] < other);
	}
	bool ZA_MULTI_RESULT_::operator>(const ZA_RESULT& other) const
	{
		return (this->Results[0] > other);
	}
	bool ZA_MULTI_RESULT_::operator<=(const ZA_RESULT& other) const
	{
		return (this->Results[0] <= other);
	}
	bool ZA_MULTI_RESULT_::operator>=(const ZA_RESULT& other) const
	{
		return (this->Results[0] >= other);
	}
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT util //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap
{
	void SubmitZAResult(ZA_RESULT result)
	{
		ZA_ERROR(GetZAResultMessage(result));
	}

	void SubmitZAResult(const ZA_RESULT& result, char* file, const uint& line)
	{
		log::LogMessage(ZA_LOG_MESSAGE_ERROR, log::GetLogInfoHeader(ZA_LOG_MESSAGE_ERROR, file, line), GetZAResultMessage(result));
	}

	ZA_MULTI_RESULT CombineZAResults(std::initializer_list<ZA_RESULT> results)
	{
		uint index = 0;
		ZA_MULTI_RESULT result;
		
		if (results.size() == 0)
			return result;

		for (ZA_RESULT subResult : results)
		{
			//test if the index is still inside the bounds
			if (index < ZA_MULTI_RESULT_SIZE)
			{
				result[index++] = subResult;
			} else // add the information error and break
			{
				result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;
				break;
			}
		}

		return result;
	}

	ZA_MULTI_RESULT AddZAResult(ZA_MULTI_RESULT srcResult, ZA_RESULT addResult)
	{
		ZA_MULTI_RESULT result;
		bool enoughSpace = srcResult[ZA_MULTI_RESULT_SIZE - 1] == 0x0000;

		//moves all results one back (- 1 to stay inbounds)
		memcpy(&result[1], &srcResult[0], sizeof(ZA_RESULT) * (ZA_MULTI_RESULT_SIZE - 1));

		result[0] = addResult;

		if (!enoughSpace)
			result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;

		return result;
	}

	ZA_MULTI_RESULT AddZAResults(ZA_MULTI_RESULT srcResult, std::initializer_list<ZA_RESULT> list)
	{
		if (list.size() == 0)
			return srcResult;

		ZA_MULTI_RESULT result;
		bool enoughSpace;
		uint size = ZA_MIN(list.size(), ZA_MULTI_RESULT_SIZE);

		if (list.size() <= ZA_MULTI_RESULT_SIZE)
			enoughSpace = srcResult[ZA_MULTI_RESULT_SIZE - list.size()] == 0x0000;
		else
			enoughSpace = false;

		//move back
		if (size != ZA_MULTI_RESULT_SIZE)
			memcpy(&result[size], &srcResult[0], sizeof(ZA_RESULT) * (ZA_MULTI_RESULT_SIZE - size));

		//add new results
		uint i = 0;
		for (ZA_RESULT subResult : list)
		{
			if (i < size) //yes awesome for loop
				i++;
			else 
				break;

			result[i] = subResult;
		}

		if (!enoughSpace)
			result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;

		return result;
	}

	ZA_MULTI_RESULT CombineZAResults(ZA_MULTI_RESULT mResult1, ZA_MULTI_RESULT mResult2)
	{
		std::initializer_list<ZA_RESULT> list;
		ZA_MULTI_RESULT result;
		bool enoughSpace;
		
		//size
		uint size = 0;
		for (uint i = 0; i < ZA_MULTI_RESULT_SIZE; i++)
			if (mResult2[i] != 0x0000)
				size++;
			else
				break;

		if (size == 0)
			return mResult1;

		//enoughSpace
		enoughSpace = mResult1[ZA_MULTI_RESULT_SIZE - size] == 0x0000;
		
		//move back
		if (size != ZA_MULTI_RESULT_SIZE)
			memcpy(&result[size], &mResult1[0], sizeof(ZA_RESULT) * (ZA_MULTI_RESULT_SIZE - size));

		//add new results
		for (uint i = 0; i < size; i++)
		{
			result[i] = mResult2[i];
		}

		if (!enoughSpace)
			result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;

		return result;
	}
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT messages //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap
{
	ZA_RESULT GetResultSource(const ZA_RESULT& result)
	{
		// I use a bit and operator to remove all the extra info
		return (result _and_ ZA_RESULT_SOURCE_MASK);
	}

	String GetZAResultMessages(const ZA_MULTI_RESULT& result)
	{
		String resultMessage = GetZAResultMessage(result.Results[0]);

		uint size = result.size();
		for (uint i = 1; i < size; i++)
		{
			resultMessage += "\t" + GetZAResultMessage(result.Results[i]);
		}

		return resultMessage;
	}

	String GetZAResultMessage(const ZA_RESULT& result)
	{
		if (result == ZA_OK)
			return "Everything is a okay!";
		
		ZA_RESULT resultSource = GetResultSource(result);

		switch (resultSource)
		{
		case ZA_RESULT_SOURCE_NO_SOURCE:
		case ZA_RESULT_SOURCE_MATH:
		case ZA_RESULT_SOURCE_SYSTEM:
			return "Sorry no error message jet. Error " + std::to_string(result);
		case ZA_RESULT_SOURCE_GUI:
		{
			switch (result)
			{
			case ZA_ERROR_GUI_ERROR:
				return "A error accord somewhere within the GUI system.";
			case ZA_ERROR_GUIMANAGER_ERROR:
				return "A error accord somewhere within the GUI manager.";
			case ZA_ERROR_FONT_ERROR:
				return "A error accord somewhere within the font system.";
			case ZA_ERROR_FONT_FREETYPE_INIT_ERROR:
				return "The FreeType library failed to initialize.";
			case ZA_ERROR_FONT_UNSUPPROTED_FORMAT:
				return "The submitted file is not supported by the Font system.";
			default:
				return "A Error accord somewhere within the GUI system.";
			}
		}
		case ZA_RESULT_SOURCE_API:
		{
			switch (result)
			{
			case ZA_ERROR_API_ERROR:
				return "A error accord somewhere within the API construct.";
			case ZA_ERROR_API_UNAVALIlABLE_API:
				return "The chosen API is unavailable.";
			case ZA_ERROR_API_MISSES_THIS_FEATURE:
				return "This feature is missing from this API. (Sorry)";

				/* ********************************************************* */
				// * API Components *
				/* ********************************************************* */
				/* ##################################### */
				// # Shader #
				/* ##################################### */
			case ZA_ERROR_API_SHADER_ERROR:
				return "The shader threw a Error.";
			case ZA_ERROR_API_SHADER_VERTEX_SHADER_COMPILATION_ERROR:
				return "The vertex shader couldn't be compiled.";
			case ZA_ERROR_API_SHADER_GEOMETRY_SHADER_COMPILATION_ERROR:
				return "The geometry shader couldn't be compiled.";
			case ZA_ERROR_API_SHADER_PIXEL_SHADER_COMPILATION_ERROR:
				return "The pixel shader couldn't be compiled.";

				/* ##################################### */
				// # API Texture #
				/* ##################################### */

			case ZA_ERROR_API_TEXTURE_ERROR:
				return "A texture from the current API caused an error.";
			case ZA_ERROR_API_TEXTURE1D_CREATION_ERROR:
				return "Failed to create a texture1D object for the current API.";
			case ZA_ERROR_API_TEXTURE2D_CREATION_ERROR:
				return "Failed to create a texture2D object for the current API.";
			case ZA_ERROR_API_TEXTURE3D_CREATION_ERROR:
				return "Failed to create a texture3D object for the current API.";
			case ZA_ERROR_API_TEXTURE_FILE_ERROR:
				return "The file given texture file caused an error.";

				/* ##################################### */
				// # DEFAULT #
				/* ##################################### */
			default:
				return "A API error. The API says sorry. Error: " + std::to_string(result);
			}
		}
		case ZA_RESULT_SOURCE_DIRECTX:
		case ZA_RESULT_SOURCE_OPENGL:
		default:
			return "This result has no massage(scream at the developer xFrednet to make him add a message for this: " + std::to_string(result) + ")";
		}
	}
	
}
